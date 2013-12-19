#include "ffbeffect.h"
#include "globalsettings.h"
#include <QtWidgets/QMessageBox>

FFBEffect::FFBEffect(FFBEffectTypes type)
{
  m_internalIdx = -1;
  m_status = FFBEffectStatus::NOT_LOADED;
  m_type = type;
}

struct ff_effect* FFBEffect::createFFStruct(const std::shared_ptr<FFBEffectParameters> params)
{
  struct ff_effect* eff = new struct ff_effect;
  memset(eff, 0, sizeof(struct ff_effect));

  eff->id = m_internalIdx;
  eff->direction = params->direction;
  eff->replay.delay = params->replayDelay;
  eff->replay.length = params->replayLength;

  return eff;
}

void FFBEffect::reportError(const QString& errorMsg) const
{
  QMessageBox::warning(nullptr, "FFB effect error", errorMsg);
}

bool FFBEffect::checkGenericParameters(const std::shared_ptr<FFBEffectParameters> params)
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

bool FFBEffect::operator==(const FFBEffect& other) const
{
  return this->type() == other.type();
}

bool FFBEffect::operator!=(const FFBEffect& other) const
{
  return !(*this == other);
}
