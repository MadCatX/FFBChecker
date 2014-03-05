#ifndef RUMBLEEFFECTSETTINGS_H
#define RUMBLEEFFECTSETTINGS_H

#include "effectsettings.h"
#include "envelopesettings.h"
#include "ffbrumbleeffectparameters.h"

namespace Ui {
class RumbleEffectSettings;
}

class RumbleEffectSettings : public EffectSettings
{
  Q_OBJECT

public:
  explicit RumbleEffectSettings(QWidget* parent = nullptr);
  ~RumbleEffectSettings();
  bool fillFromParameters(const std::shared_ptr<FFBEffectParameters> params);
  QString strongMagnitude() const;
  QString weakMagnitude() const;

private:
    Ui::RumbleEffectSettings *ui;
};

#endif // RUMBLEEFFECTSETTINGS_H
