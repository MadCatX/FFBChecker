#include "constanteffectsettings.h"
#include "ui_constanteffectsettings.h"

ConstantEffectSettings::ConstantEffectSettings(QWidget* parent) :
  EffectSettings(parent),
  ui(new Ui::ConstantEffectSettings)
{
  ui->setupUi(this);
}

const EnvelopeSettings* ConstantEffectSettings::envelopeSettings() const
{
  return ui->qwid_envelope;
}

QString ConstantEffectSettings::level() const
{
  return ui->qle_level->text();
}

bool ConstantEffectSettings::fillFromParameters(const std::shared_ptr<FFBEffectParameters> params)
{
  try {
    const std::shared_ptr<FFBConstantEffectParameters> cfParams = std::dynamic_pointer_cast<FFBConstantEffectParameters>(params);

    ui->qle_level->setText(QString::number(cfParams->level));
    return ui->qwid_envelope->fillFromParameters(params);
  } catch (std::bad_cast& ex) {
    qCritical(ex.what());
    return false;
  }
  return false;
}


ConstantEffectSettings::~ConstantEffectSettings()
{
  delete ui;
}
