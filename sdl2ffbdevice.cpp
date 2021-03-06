#include "sdl2ffbdevice.h"
#include "sdl2ffbeffectfactory.h"
#include <QtWidgets/QMessageBox>

#define CHECK_EFFECT_IDX(idx) if (idx < 0 || idx > c_maxEffectCount) return false

const QString SDL2FFBDevice::SDL2DEV_ERR_CAPTION("SDL2 device error");

SDL2FFBDevice::SDL2FFBDevice(SDL_Haptic* haptic, const int maxEffectCount) :
    FFBDevice(maxEffectCount),
    c_haptic(haptic)
{
  for (int i = 0; i < maxEffectCount; i++)
    m_effects.push_back(SDL2FFBEffectFactory::createEffect(FFBEffectTypes::NONE));
}

void SDL2FFBDevice::close()
{
  for (int idx = 0; idx < c_maxEffectCount; idx++)
    removeAndEraseEffect(idx);

  SDL_HapticClose(c_haptic);
}

bool SDL2FFBDevice::queryDeviceCapabilities()
{
  unsigned int caps;
  bool hasPeriodic = false;
  bool hasCondition = false;

  caps = SDL_HapticQuery(c_haptic);
  if (caps == 0)
    return false;

  if (caps & SDL_HAPTIC_CONSTANT)
    m_availableEffects.push_back(FFBEffectTypes::CONSTANT);

  if (caps & SDL_HAPTIC_SINE) {
    hasPeriodic = true;
    m_availablePeriodicWaveforms.push_back(PeriodicWaveforms::SINE);
  }
  if (caps & SDL_HAPTIC_TRIANGLE) {
    hasPeriodic = true;
    m_availablePeriodicWaveforms.push_back(PeriodicWaveforms::TRIANGLE);
  }
  if (caps & SDL_HAPTIC_SAWTOOTHUP) {
    hasPeriodic = true;
    m_availablePeriodicWaveforms.push_back(PeriodicWaveforms::SAW_UP);
  }
  if (caps & SDL_HAPTIC_SAWTOOTHDOWN) {
    hasPeriodic = true;
    m_availablePeriodicWaveforms.push_back(PeriodicWaveforms::SAW_DOWN);
  }
  if (hasPeriodic)
    m_availableEffects.push_back(FFBEffectTypes::PERIODIC);

  if (caps & SDL_HAPTIC_RAMP)
    m_availableEffects.push_back(FFBEffectTypes::RAMP);

  if (caps & SDL_HAPTIC_SPRING) {
    hasCondition = true;
    m_availableConditionSubtypes.push_back(ConditionSubtypes::SPRING);
  }
  if (caps & SDL_HAPTIC_DAMPER) {
    hasCondition = true;
    m_availableConditionSubtypes.push_back(ConditionSubtypes::DAMPER);
  }
  if (caps & SDL_HAPTIC_INERTIA) {
    hasCondition = true;
    m_availableConditionSubtypes.push_back(ConditionSubtypes::INERTIA);
  }
  if (caps & SDL_HAPTIC_FRICTION) {
    hasCondition = true;
    m_availableConditionSubtypes.push_back(ConditionSubtypes::FRICTION);
  }

  if (hasCondition)
    m_availableEffects.push_back(FFBEffectTypes::CONDITION);

  if (caps & SDL_HAPTIC_GAIN)
    m_adjustableGain = true;

  if (caps & SDL_HAPTIC_AUTOCENTER)
    m_adjustableAC = true;

  return true;
}

bool SDL2FFBDevice::removeEffect(const int idx)
{
  std::shared_ptr<SDL2FFBEffect> sdlEff;
  CHECK_EFFECT_IDX(idx);

  if (!stopEffect(idx))
    return false;

  if (m_effects[idx]->type() == FFBEffectTypes::NONE)
    return true;

  sdlEff = std::static_pointer_cast<SDL2FFBEffect>(m_effects[idx]);

  SDL_HapticDestroyEffect(c_haptic, sdlEff->internalIdx());

  return true;
}


bool SDL2FFBDevice::removeAndEraseEffect(const int idx)
{
  CHECK_EFFECT_IDX(idx);

  if (m_effects[idx]->status() == FFBEffect::FFBEffectStatus::NOT_LOADED)
    return true;

  if (removeEffect(idx)) {
    m_effects[idx] = SDL2FFBEffectFactory::createEffect(FFBEffectTypes::NONE);
    if (m_effects[idx]->type() != FFBEffectTypes::NONE) {
      qCritical("Unable to empty the effect slot.");
      return false;
    }
  } else {
    qCritical("Unable to stop the effect.");
    return false;
  }

  m_effects[idx]->setStatus(FFBEffect::FFBEffectStatus::NOT_LOADED);
  return true;
}

bool SDL2FFBDevice::setAutocentering(const int strength)
{
  if (!m_adjustableAC) {
    QMessageBox::warning(nullptr, SDL2DEV_ERR_CAPTION, "Device does not have adjustable autocentering");
    return false;
  }

  if (strength < 0 || strength > 100) {
    QMessageBox::warning(nullptr, SDL2DEV_ERR_CAPTION, "Autocentering strength must be within <0; 100>");
    return false;
  }

  if (SDL_HapticSetAutocenter(c_haptic, strength) < 0) {
    QMessageBox::warning(nullptr, SDL2DEV_ERR_CAPTION, QString("Unable to set autocentering:\n%1").arg(SDL_GetError()));
    return false;
  }

  return true;
}


bool SDL2FFBDevice::setGain(const int gain)
{
  if (!m_adjustableGain) {
    QMessageBox::warning(nullptr, SDL2DEV_ERR_CAPTION, "Device does not have adjustable gain");
    return false;
  }

  if (gain < 0 || gain > 100) {
    QMessageBox::warning(nullptr, SDL2DEV_ERR_CAPTION, "Gain must be within <0; 100>");
    return false;
  }

  if (SDL_HapticSetGain(c_haptic, gain) < 0) {
    QMessageBox::warning(nullptr, SDL2DEV_ERR_CAPTION, QString("Unable to set gain:\n%1").arg(SDL_GetError()));
    return false;
  }

  return true;
}

bool SDL2FFBDevice::startEffect(const int idx, const FFBEffectTypes type, std::shared_ptr<FFBEffectParameters> parameters)
{
  std::shared_ptr<SDL2FFBEffect> sdlEff;
  Uint32 repeat;

  CHECK_EFFECT_IDX(idx);

  if (m_effects[idx]->status() == FFBEffect::FFBEffectStatus::NOT_LOADED) {
    if (!uploadEffect(idx, type, parameters))
      return false;
  }
  if (m_effects[idx]->status() == FFBEffect::FFBEffectStatus::PLAYING)
    return true;

  sdlEff = std::static_pointer_cast<SDL2FFBEffect>(m_effects[idx]);
  if (sdlEff->parameters()->repeat == 0) {
    if (sdlEff->parameters()->replayLength > 0)
      repeat = SDL_HAPTIC_INFINITY;
    else
      repeat = 1;
  } else
    repeat = sdlEff->parameters()->repeat;

  if (SDL_HapticRunEffect(c_haptic, sdlEff->internalIdx(), repeat) < 0) {
    QMessageBox::warning(nullptr, SDL2DEV_ERR_CAPTION, QString("Unable to start the effect:\n%1").arg(SDL_GetError()));
    return false;
  }

  sdlEff->setStatus(FFBEffect::FFBEffectStatus::PLAYING);
  return true;
}

bool SDL2FFBDevice::stopEffect(const int idx)
{
  std::shared_ptr<SDL2FFBEffect> sdlEff;
  CHECK_EFFECT_IDX(idx);

  if (m_effects[idx] == nullptr)
    return true;

  if (m_effects[idx]->status() != FFBEffect::FFBEffectStatus::PLAYING)
    return true;

  sdlEff = std::static_pointer_cast<SDL2FFBEffect>(m_effects[idx]);
  if (SDL_HapticStopEffect(c_haptic, sdlEff->internalIdx()) < 0) {
    QMessageBox::critical(nullptr, SDL2DEV_ERR_CAPTION, QString("Unable to stop the effect:\n%1").arg(SDL_GetError()));
    return false;
  }

  sdlEff->setStatus(FFBEffect::FFBEffectStatus::UPLOADED);
  return true;
}

bool SDL2FFBDevice::uploadEffect(const int idx, const FFBEffectTypes type, std::shared_ptr<FFBEffectParameters> parameters)
{
  SDL_HapticEffect* underlEff;
  int intIdx;
  std::shared_ptr<FFBEffect> effect = SDL2FFBEffectFactory::createEffect(type);
  std::shared_ptr<SDL2FFBEffect> sdlEff;

  CHECK_EFFECT_IDX(idx);

  if (type != FFBEffectTypes::NONE)
    sdlEff = std::static_pointer_cast<SDL2FFBEffect>(effect);
  else
    return false;

  if (sdlEff == nullptr)
    return false;

  if (!sdlEff->setParameters(parameters))
    return false;

  /* There is no effect in the selected slot */
  if (m_effects[idx]->type() != FFBEffectTypes::NONE) {
    /* Effects are not of the same type, delete the previous effect and create a new one */
    if (*m_effects[idx] != *sdlEff) {
      if (!removeEffect(idx)) {
        return false;
      }
    } else {
      /* Effects are of the same type, update it */

      underlEff = sdlEff->createFFstruct();
      if (underlEff == nullptr)
        return false;

      intIdx = SDL_HapticUpdateEffect(c_haptic, std::static_pointer_cast<SDL2FFBEffect>(m_effects[idx])->internalIdx(), underlEff);
      if (intIdx < 0) {
        QMessageBox::critical(nullptr, SDL2DEV_ERR_CAPTION, QString("Unable to update the effect:\n%1").arg(SDL_GetError()));
        m_effects[idx]->setStatus(FFBEffect::FFBEffectStatus::UPLOADED);
        return true;
      }
      sdlEff->setStatus(m_effects[idx]->status());

      goto out;
    }
  }

  underlEff = sdlEff->createFFstruct();
  if (underlEff == nullptr)
    return false;

  intIdx = SDL_HapticNewEffect(c_haptic, underlEff);
  if (intIdx < 0) {
    QMessageBox::critical(nullptr, SDL2DEV_ERR_CAPTION, QString("Unable to create effect:\n%1").arg(SDL_GetError()));
    return false;
  }
  sdlEff->setStatus(FFBEffect::FFBEffectStatus::UPLOADED);

out:
  sdlEff->setInternalIdx(intIdx);
  delete underlEff;
  m_effects[idx] = sdlEff;

  return true;
}

