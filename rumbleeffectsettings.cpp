#include "rumbleeffectsettings.h"
#include "ui_rumbleeffectsettings.h"

RumbleEffectSettings::RumbleEffectSettings(QWidget* parent) :
    EffectSettings(parent),
    ui(new Ui::RumbleEffectSettings)
{
    ui->setupUi(this);
}

bool RumbleEffectSettings::fillFromParameters(const std::shared_ptr<FFBEffectParameters> params)
{
  try {
    const std::shared_ptr<FFBRumbleEffectParameters> ruParams = std::dynamic_pointer_cast<FFBRumbleEffectParameters>(params);

    ui->qle_strongMag->setText(QString::number(ruParams->strongMagnitude));
    ui->qle_weakMag->setText(QString::number(ruParams->weakMagnitude));
    return true;
  } catch (std::bad_cast& ex) {
    qCritical(ex.what());
    return false;
  }
  return false;
}

QString RumbleEffectSettings::strongMagnitude() const
{
  return ui->qle_strongMag->text();
}

QString RumbleEffectSettings::weakMagnitude() const
{
  return ui->qle_weakMag->text();
}

RumbleEffectSettings::~RumbleEffectSettings()
{
    delete ui;
}
