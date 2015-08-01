#include "sdl2ffbeffect.h"
#include "globalsettings.h"

SDL_HapticEffect* SDL2FFBEffect::createFFstruct()
{
  SDL_HapticEffect* effect = new SDL_HapticEffect;
  if (effect == nullptr)
    return nullptr;

  memset(effect, 0, sizeof(SDL_HapticEffect));

  return effect;
}

bool SDL2FFBEffect::checkEnvelopeParameters(const int attackLength, const int attackLevel, const int fadeLength, const int fadeLevel)
{
  if (!GlobalSettings::GS()->doSanityChecks)
    return true;

  if (!checkBoundsInclusive(attackLength, 0, 0x7FFF)) {
    reportError("Attack length must be within <0; 32767>");
    return false;
  }

  if (!checkBoundsInclusive(attackLevel, 0, 0x7FFF)) {
    reportError("Attack level must be within <0; 32767>");
    return false;
  }

  if (!checkBoundsInclusive(fadeLength, 0, 0x7FFF)) {
    reportError("Fade length must be within <0; 32767>");
    return false;
  }

  if (!checkBoundsInclusive(fadeLevel, 0, 0x7FFF)) {
    reportError("Fade level must be within <0; 32767>");
    return false;
  }

  return true;
}

bool SDL2FFBEffect::checkGenericParameters(const std::shared_ptr<FFBEffectParameters> params)
{
  if (!GlobalSettings::GS()->doSanityChecks)
    return true;

  if (!checkBoundsInclusive(params->direction, 0, 36000)) {
    reportError("Direction must be within <0; 36000)");
    return false;
  }

  if (!checkBoundsInclusive(params->replayLength, static_cast<int64_t>(0), static_cast<int64_t>(0x7FFF))) {
    reportError("Replay length must be within <0; 32767>");
    return false;
  }

  if (!checkBoundsInclusive(params->replayDelay, 0, 0xFFFF)) {
    reportError("Replay delay must be within <0; 65535>");
    return false;
  }

  return true;
}


