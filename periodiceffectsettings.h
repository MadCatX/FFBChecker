#ifndef PERIODICEFFECTSETTINGS_H
#define PERIODICEFFECTSETTINGS_H

#include "effectsettings.h"
#include "envelopesettings.h"
#include "ffbperiodiceffectparameters.h"

namespace Ui {
  class PeriodicEffectSettings;
}

class PeriodicEffectSettings : public EffectSettings
{
  Q_OBJECT

public:
  explicit PeriodicEffectSettings(QWidget* parent = 0);
  ~PeriodicEffectSettings();
  const EnvelopeSettings* envelopeSettings() const;
  void fillAvailableWaveformsList(const std::vector<PeriodicWaveforms>& list);
  bool fillFromParameters(const std::shared_ptr<FFBEffectParameters> params);
  QString magnitude() const;
  QString offset() const;
  QString period() const;
  QString phase() const;
  QString waveformTypeToWaveformName(const PeriodicWaveforms waveform) const;
  int waveformIdx() const;

private:
  Ui::PeriodicEffectSettings* ui;
};

#endif // PERIODICEFFECTSETTINGS_H
