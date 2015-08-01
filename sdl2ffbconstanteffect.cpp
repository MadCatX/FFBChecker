#include "sdl2ffbconstanteffect.h"
#include "globalsettings.h"

SDL2FFBConstantEffect::SDL2FFBConstantEffect() :
  SDL2FFBEffect(FFBEffectTypes::CONSTANT)
{}

SDL_HapticEffect* SDL2FFBConstantEffect::createFFstruct()
{
  SDL_HapticEffect* effect = initFFstruct();
  if (effect == nullptr)
    return nullptr;

  effect->type = SDL_HAPTIC_CONSTANT;
  effect->constant.direction.type = SDL_HAPTIC_POLAR;
  effect->constant.direction.dir[0] = m_params->direction;

  if (m_params->replayLength == 0)
    effect->constant.length = SDL_HAPTIC_INFINITY;
  else
    effect->constant.length = m_params->replayLength;
  effect->constant.delay = m_params->replayDelay;

  effect->constant.attack_length = m_params->attackLength;
  effect->constant.attack_level = m_params->attackLevel;
  effect->constant.fade_length = m_params->fadeLength;
  effect->constant.fade_level = m_params->fadeLevel;

  effect->constant.level = m_params->level;

  return effect;
}

bool SDL2FFBConstantEffect::setParameters(const std::shared_ptr<FFBEffectParameters> params)
{
  try {
    const std::shared_ptr<FFBConstantEffectParameters> iParams = std::dynamic_pointer_cast<FFBConstantEffectParameters>(params);
    return setParameters(iParams);
  } catch (std::bad_cast& ) {
    return false;
  }
}


bool SDL2FFBConstantEffect::setParameters(const std::shared_ptr<FFBConstantEffectParameters> params)
{
  if (!GlobalSettings::GS()->doSanityChecks)
    return true;

  if (!checkGenericParameters(params))
    return false;

  if (!checkEnvelopeParameters(params->attackLength, params->attackLevel, params->fadeLength, params->fadeLevel))
    return false;

  if (!checkBoundsInclusive(params->level, -0x7FFF, 0x7FFF)) {
    reportError("Level parameters must be within <-32767; 32767>");
    return false;
  }

  m_params = params;
  return true;
}

