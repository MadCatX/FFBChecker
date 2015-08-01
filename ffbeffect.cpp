#include "ffbeffect.h"
#include "globalsettings.h"
#include <QtWidgets/QMessageBox>

const QString FFBEffect::PRERR_CAPTION("Invalid FFB parameter");

FFBEffect::FFBEffect(FFBEffectTypes type)
{
  m_status = FFBEffectStatus::NOT_LOADED;
  m_type = type;
}

void FFBEffect::reportError(const QString& errorMsg) const
{
  QMessageBox::warning(nullptr, PRERR_CAPTION, errorMsg);
}

bool FFBEffect::operator==(const FFBEffect& other) const
{
  return this->type() == other.type();
}

bool FFBEffect::operator!=(const FFBEffect& other) const
{
  return !(*this == other);
}
