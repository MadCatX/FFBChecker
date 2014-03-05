#ifndef EFFECTSETTINGS_H
#define EFFECTSETTINGS_H

#include "ffbeffectparameters.h"
#include <QtWidgets/QWidget>

class EffectSettings : public QWidget
{
  Q_OBJECT
public:
  explicit EffectSettings(QWidget* parent = nullptr);
  virtual bool fillFromParameters(const std::shared_ptr<FFBEffectParameters> params) = 0;

signals:

public slots:

};

#endif // EFFECTSETTINGS_H
