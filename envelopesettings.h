#ifndef ENVELOPESETTINGS_H
#define ENVELOPESETTINGS_H

#include "ffbeffectparameters.h"
#include "ffbenvelopeparameters.h"
#include <QtWidgets/QWidget>

namespace Ui {
  class EnvelopeSettings;
}

class EnvelopeSettings : public QWidget
{
  Q_OBJECT

public:
  explicit EnvelopeSettings(QWidget *parent = 0);
  ~EnvelopeSettings();
  bool fillFromParameters(const std::shared_ptr<FFBEffectParameters> params);

  QString attackLength() const;
  QString attackLevel() const;
  QString fadeLength() const;
  QString fadeLevel() const;

private:
  Ui::EnvelopeSettings* ui;
};

#endif // ENVELOPESETTINGS_H
