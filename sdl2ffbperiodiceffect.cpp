#include "sdl2ffbperiodiceffect.h"
#include "globalsettings.h"

SDL2FFBPeriodicEffect::SDL2FFBPeriodicEffect() :
  SDL2FFBEffect(FFBEffectTypes::PERIODIC)
{}

SDL_HapticEffect* SDL2FFBPeriodicEffect::createFFstruct()
{
  SDL_HapticEffect* effect = initFFstruct();

  if (effect == nullptr)
    return nullptr;

  switch (m_params->waveform) {
    case PeriodicWaveforms::SINE:
      effect->type = SDL_HAPTIC_SINE;
      break;
    case PeriodicWaveforms::TRIANGLE:
      effect->type = SDL_HAPTIC_TRIANGLE;
      break;
    case PeriodicWaveforms::SAW_UP:
      effect->type = SDL_HAPTIC_SAWTOOTHUP;
      break;
    case PeriodicWaveforms::SAW_DOWN:
      effect->type = SDL_HAPTIC_SAWTOOTHDOWN;
    default:
      delete effect;
      return nullptr;
  }

  effect->periodic.direction.type = SDL_HAPTIC_POLAR;
  effect->periodic.direction.dir[0] = m_params->direction;

  if (m_params->replayLength == 0)
    effect->periodic.length = SDL_HAPTIC_INFINITY;
  else
    effect->periodic.length = m_params->replayLength;

  effect->periodic.delay = m_params->replayDelay;

  effect->periodic.attack_length = m_params->attackLength;
  effect->periodic.attack_level = m_params->attackLevel;
  effect->periodic.fade_length = m_params->fadeLength;
  effect->periodic.fade_level = m_params->fadeLevel;

  effect->periodic.period = m_params->period;
  effect->periodic.magnitude = m_params->magnitude;
  effect->periodic.offset = m_params->offset;
  effect->periodic.phase = m_params->phase;

  return effect;
}

bool SDL2FFBPeriodicEffect::setParameters(const std::shared_ptr<FFBEffectParameters> params)
{
  try {
    const std::shared_ptr<FFBPeriodicEffectParameters> iParams = std::dynamic_pointer_cast<FFBPeriodicEffectParameters>(params);
    return setParameters(iParams);
  } catch (std::bad_cast& ) {
    return false;
  }
}

bool SDL2FFBPeriodicEffect::setParameters(const std::shared_ptr<FFBPeriodicEffectParameters> params)
{
  if (!GlobalSettings::GS()->doSanityChecks)
    return true;

  if (!checkGenericParameters(params))
    return false;

  if (!checkEnvelopeParameters(params->attackLength, params->attackLevel, params->fadeLength, params->fadeLevel))
    return false;

  if (!checkBoundsInclusive(params->period, 0, 36000)) {
    reportError("Period must be within <0; 36000>");
    return false;
  }

  if (!checkBoundsInclusive(params->magnitude, -0x7FFF, 0x7FFF)) {
    reportError("Magnitude must be within <-32767; 32767>");
    return false;
  }

  if (!checkBoundsInclusive(params->offset, -0x7FFF, 0x7FFF)) {
    reportError("Offset must be within <-32767; 32767>");
    return false;
  }

  if (!checkBoundsInclusive(params->phase, 0, 36000)) {
    reportError("Phase must be withing <0; 36000>");
    return false;
  }

  if (params->waveform == PeriodicWaveforms::NONE ||
      params->waveform == PeriodicWaveforms::SQUARE) {
    reportError("Invalid or unsupported waveform");
    return false;
  }

  m_params = params;
  return true;
}

bool SDL2FFBPeriodicEffect::operator==(const FFBEffect& other) const
{
  if (this->type() != other.type())
    return false;
  else {
    try {
      const SDL2FFBPeriodicEffect& eff = dynamic_cast<const SDL2FFBPeriodicEffect&>(other);
      return this->m_params->waveform == eff.m_params->waveform;
    } catch(std::bad_cast&) {
      return false;
    }
  }
}