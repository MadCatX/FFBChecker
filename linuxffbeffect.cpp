#include "linuxffbeffect.h"
#include "globalsettings.h"

LinuxFFBEffect::LinuxFFBEffect(FFBEffectTypes type) :
  FFBEffect(type)
{
  m_internalIdx = -1;
}

struct ff_effect* LinuxFFBEffect::createFFStruct(const std::shared_ptr<FFBEffectParameters> params)
{
  struct ff_effect* eff = new struct ff_effect;
  memset(eff, 0, sizeof(struct ff_effect));

  eff->id = m_internalIdx;
  eff->direction = params->direction;
  eff->replay.delay = params->replayDelay;
  eff->replay.length = params->replayLength;

  return eff;
}

bool LinuxFFBEffect::checkEnvelopeParameters(const int attackLength, const int attackLevel, const int fadeLength, const int fadeLevel)
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

bool LinuxFFBEffect::checkGenericParameters(const std::shared_ptr<FFBEffectParameters> params)
{
  if (!GlobalSettings::GS()->doSanityChecks)
    return true;

  if (params->repeat < 1) {
    reportError("Effect must be played back at least once.");
    return false;
  }

  if (!checkBoundsInclusive(params->direction, 0, 0xFFFF)) {
    reportError("Direction must be within <0; 65535>");
    return false;
  }

  if (!checkBoundsInclusive(params->replayDelay, 0, 0x7FFF)) {
    reportError("Replay delay must be within <0; 65535>");
    return false;
  }

  if (!checkBoundsInclusive(params->replayLength, static_cast<int64_t>(0), static_cast<int64_t>(0x7FFF))) {
    reportError("Replay length must be within <0; 32767>");
    return false;
  }

  return true;
}