#include "linuxffbeffect.h"
#include "globalsettings.h"
#include <QtWidgets/QMessageBox>

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

void LinuxFFBEffect::reportError(const QString& errorMsg) const
{
  QMessageBox::warning(nullptr, "FFB effect error", errorMsg);
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
    reportError("Direction out of bounds.");
    return false;
  }

  if (!checkBoundsInclusive(params->replayDelay, 0, 0x7FFF)) {
    reportError("Replay delay out of bounds.");
    return false;
  }

  if (!checkBoundsInclusive(params->replayLength, 0, 0x7FFF)) {
    reportError("Replay length out of bounds.");
    return false;
  }

  return true;
}