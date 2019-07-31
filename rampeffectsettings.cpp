#include "rampeffectsettings.h"
#include "ui_rampeffectsettings.h"

RampEffectSettings::RampEffectSettings(QWidget* parent) :
  EffectSettings(parent),
  ui(new Ui::RampEffectSettings)
{
  ui->setupUi(this);
}

const EnvelopeSettings* RampEffectSettings::envelopeSettings() const
{
  return ui->qwid_envelope;
}

QString RampEffectSettings::endLevel() const
{
  return ui->qle_endLevel->text();
}

QString RampEffectSettings::startLevel() const
{
  return ui->qle_startLevel->text();
}

bool RampEffectSettings::fillFromParameters(const std::shared_ptr<FFBEffectParameters> params)
{
  try {
    const std::shared_ptr<FFBRampEffectParameters> rfParams = std::dynamic_pointer_cast<FFBRampEffectParameters>(params);

    ui->qle_endLevel->setText(QString::number(rfParams->endLevel));
    ui->qle_startLevel->setText(QString::number(rfParams->startLevel));
    return ui->qwid_envelope->fillFromParameters(params);
  } catch (std::bad_cast& ex) {
    qCritical("%s\n", ex.what());
    return false;
  }
  return false;
}

RampEffectSettings::~RampEffectSettings()
{
  delete ui;
}
