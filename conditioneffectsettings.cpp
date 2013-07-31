#include "conditioneffectsettings.h"
#include "ui_conditioneffectsettings.h"

ConditionEffectSettings::ConditionEffectSettings(QWidget* parent) :
  EffectSettings(parent),
  ui(new Ui::ConditionEffectSettings)
{
  ui->setupUi(this);
}

void ConditionEffectSettings::fillAvailableSubtypesList(const QStringList& list)
{
  ui->cbox_subtype->clear();
  ui->cbox_subtype->addItems(list);
}

bool ConditionEffectSettings::fillFromParameters(const std::shared_ptr<FFBEffectParameters> params)
{
  try {
    const std::shared_ptr<FFBConditionEffectParameters> cdParams = std::dynamic_pointer_cast<FFBConditionEffectParameters>(params);
    return fillFromParameters(cdParams);
  } catch (std::bad_cast& ex) {
    qCritical(ex.what());
    return false;
  }
}

bool ConditionEffectSettings::fillFromParameters(const std::shared_ptr<FFBConditionEffectParameters> cdParams)
{
  ui->qle_center->setText(QString::number(cdParams->center));
  ui->qle_deadband->setText(QString::number(cdParams->deadband));
  ui->qle_leftCoeff->setText(QString::number(cdParams->leftCoeff));
  ui->qle_rightCoeff->setText(QString::number(cdParams->rightCoeff));
  ui->qle_leftSat->setText(QString::number(cdParams->leftSat));
  ui->qle_rightSat->setText(QString::number(cdParams->rightCoeff));
  return true;
}

QString ConditionEffectSettings::center() const
{
  return ui->qle_center->text();
}

QString ConditionEffectSettings::deadband() const
{
  return ui->qle_deadband->text();
}

QString ConditionEffectSettings::leftCoeff() const
{
  return ui->qle_leftCoeff->text();
}

QString ConditionEffectSettings::rightCoeff() const
{
  return ui->qle_rightCoeff->text();
}

QString ConditionEffectSettings::leftSat() const
{
  return ui->qle_leftSat->text();
}

QString ConditionEffectSettings::rightSat() const
{
  return ui->qle_rightSat->text();
}

int ConditionEffectSettings::subtypeIdx() const
{
  return ui->cbox_subtype->currentIndex();
}

ConditionEffectSettings::~ConditionEffectSettings()
{
  delete ui;
}
