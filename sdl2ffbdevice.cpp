#include "sdl2ffbdevice.h"
#include "sdl2ffbeffectfactory.h"

SDL2FFBDevice::SDL2FFBDevice(SDL_Haptic* haptic, const int maxEffectCount) :
    FFBDevice(maxEffectCount),
    c_haptic(haptic)
{
  for (int i = 0; i < maxEffectCount; i++)
    m_effects.push_back(SDL2FFBEffectFactory::createEffect(FFBEffectTypes::NONE));
}

void SDL2FFBDevice::close()
{
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

  return true;
}

bool SDL2FFBDevice::removeAndEraseEffect(const int idx)
{
  return false;
}

bool SDL2FFBDevice::startEffect(const int idx, const FFBEffectTypes type, std::shared_ptr< FFBEffectParameters > parameters)
{
  return false;
}

bool SDL2FFBDevice::stopEffect(const int idx)
{
  return false;
}

bool SDL2FFBDevice::uploadEffect(const int idx, const FFBEffectTypes type, std::shared_ptr< FFBEffectParameters > parameters)
{
  return false;
}

