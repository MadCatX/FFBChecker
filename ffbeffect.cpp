#include "ffbeffect.h"
#include "globalsettings.h"

const QString FFBEffect::PRERR_CAPTION("Invalid FFB parameter");

FFBEffect::FFBEffect(FFBEffectTypes type)
{
  m_status = FFBEffectStatus::NOT_LOADED;
  m_type = type;
}

bool FFBEffect::operator==(const FFBEffect& other) const
{
  return this->type() == other.type();
}

bool FFBEffect::operator!=(const FFBEffect& other) const
{
  return !(*this == other);
}
