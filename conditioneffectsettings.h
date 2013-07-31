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
  void fillAvailableSubtypesList(const QStringList& list);
  bool fillFromParameters(const std::shared_ptr<FFBEffectParameters> params);
  bool fillFromParameters(const std::shared_ptr<FFBConditionEffectParameters> cdParams);
  QString center() const;
  QString deadband() const;
  QString leftCoeff() const;
  QString rightCoeff() const;
  QString leftSat() const;
  QString rightSat() const;
  int subtypeIdx() const;

private:
  Ui::ConditionEffectSettings* ui;
};

#endif // CONDITIONEFFECTSETTINGS_H
