#ifndef CONSTANTEFFECTSETTINGS_H
#define CONSTANTEFFECTSETTINGS_H

#include "effectsettings.h"
#include "envelopesettings.h"
#include "ffbconstanteffectparameters.h"

namespace Ui {
  class ConstantEffectSettings;
}

class ConstantEffectSettings : public EffectSettings
{
  Q_OBJECT

public:
  explicit ConstantEffectSettings(QWidget* parent = nullptr);
  ~ConstantEffectSettings();
  const EnvelopeSettings* envelopeSettings() const;
  bool fillFromParameters(const std::shared_ptr<FFBEffectParameters> params);
  QString level() const;

private:
  Ui::ConstantEffectSettings* ui;

};

#endif // CONSTANTEFFECTSETTINGS_H
