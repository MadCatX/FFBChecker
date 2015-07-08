#ifndef CONDITIONEFFECTSETTINGS_H
#define CONDITIONEFFECTSETTINGS_H

#include "effectsettings.h"
#include "ffbconditioneffectparameters.h"

namespace Ui {
  class ConditionEffectSettings;
}

class ConditionEffectSettings : public EffectSettings
{
  Q_OBJECT
public:
  explicit ConditionEffectSettings(QWidget* parent = nullptr);
  ~ConditionEffectSettings();
  QString conditionSubtypeToConditionName(const ConditionSubtypes subtype) const;
  void fillAvailableSubtypesList(const std::vector<ConditionSubtypes>& list);
  bool fillFromParameters(const std::shared_ptr<FFBEffectParameters> params);
  bool fillFromParameters(const std::shared_ptr<FFBConditionEffectParameters> cdParams);
  FFBConditionEffectParameters::Axis axis() const;
  QString centerX() const;
  QString centerY() const;
  QString deadbandX() const;
  QString deadbandY() const;
  QString leftCoeffX() const;
  QString leftCoeffY() const;
  QString rightCoeffX() const;
  QString rightCoeffY() const;
  QString leftSatX() const;
  QString leftSatY() const;
  QString rightSatX() const;
  QString rightSatY() const;
  ConditionSubtypes subtype() const;

private:
  Ui::ConditionEffectSettings* ui;

private slots:
  void axisChanged(const int);
};

#endif // CONDITIONEFFECTSETTINGS_H
