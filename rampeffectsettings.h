#ifndef RAMPEFFECTSETTINGS_H
#define RAMPEFFECTSETTINGS_H

#include "effectsettings.h"
#include "envelopesettings.h"
#include"ffbrampeffectparameters.h"

namespace Ui {
  class RampEffectSettings;
}

class RampEffectSettings : public EffectSettings
{
  Q_OBJECT

public:
  explicit RampEffectSettings(QWidget* parent = nullptr);
  ~RampEffectSettings();
  const EnvelopeSettings* envelopeSettings() const;
  bool fillFromParameters(const std::shared_ptr<FFBEffectParameters> params);
  QString endLevel() const;
  QString startLevel() const;

private:
  Ui::RampEffectSettings *ui;
};

#endif // RAMPEFFECTSETTINGS_H
