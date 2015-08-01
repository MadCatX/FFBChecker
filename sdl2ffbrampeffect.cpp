#include "sdl2ffbrampeffect.h"
#include "globalsettings.h"

SDL2FFBRampEffect::SDL2FFBRampEffect() :
  SDL2FFBEffect(FFBEffectTypes::RAMP)
{}

SDL_HapticEffect* SDL2FFBRampEffect::createFFstruct()
{
  SDL_HapticEffect* effect = initFFstruct();

  if (effect == nullptr)
    return nullptr;

  effect->type = SDL_HAPTIC_RAMP;

  effect->ramp.direction.type = SDL_HAPTIC_POLAR;
  effect->ramp.direction.dir[0] = m_params->direction;

  if (m_params->replayLength == 0)
    effect->ramp.length = SDL_HAPTIC_INFINITY;
  else
    effect->ramp.length = m_params->replayLength;

  effect->ramp.delay = m_params->replayDelay;

  effect->ramp.attack_length = m_params->attackLength;
  effect->ramp.attack_level = m_params->attackLevel;
  effect->ramp.fade_length = m_params->fadeLength;
  effect->ramp.fade_level = m_params->fadeLevel;

  effect->ramp.start = m_params->startLevel;
  effect->ramp.end = m_params->endLevel;

  return effect;
}

bool SDL2FFBRampEffect::setParameters(const std::shared_ptr<FFBEffectParameters>  params)
{
  try {
    const std::shared_ptr<FFBRampEffectParameters> iParams = std::dynamic_pointer_cast<FFBRampEffectParameters>(params);
    return setParameters(iParams);
  } catch (std::bad_cast& ) {
    return false;
  }
}

bool SDL2FFBRampEffect::setParameters(const std::shared_ptr<FFBRampEffectParameters> params)
{
  if (!GlobalSettings::GS()->doSanityChecks)
    return true;

  if (!checkGenericParameters(params))
    return false;

  if (!checkEnvelopeParameters(params->attackLength, params->attackLevel, params->fadeLength, params->fadeLevel))
    return false;

  if (checkBoundsInclusive(params->startLevel, -0x7FFF, 0x7FFF)) {
    reportError("Start level must be within <-32767; 32767>");
    return false;
  }

  if (!checkBoundsInclusive(params->endLevel, -0x7FFF, 0x7FFF)) {
    reportError("End level must be within <-32767; 32767>");
    return false;
  }

  m_params = params;
  return true;
}


