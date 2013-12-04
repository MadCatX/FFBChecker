#include "conditioneffectsettings.h"
#include "ui_conditioneffectsettings.h"
#include <QDebug>

ConditionEffectSettings::ConditionEffectSettings(QWidget* parent) :
  EffectSettings(parent),
  ui(new Ui::ConditionEffectSettings)
{
  ui->setupUi(this);
  connect(ui->cbox_axis, SIGNAL(currentIndexChanged(int)), this, SLOT(axisChanged(const int)));
}

void ConditionEffectSettings::axisChanged(const int idx)
{
  ui->qstw_center->setCurrentIndex(idx);
  ui->qstw_deadband->setCurrentIndex(idx);
  ui->qstw_leftCoeff->setCurrentIndex(idx);
  ui->qstw_leftSat->setCurrentIndex(idx);
  ui->qstw_rightCoeff->setCurrentIndex(idx);
  ui->qstw_rightSat->setCurrentIndex(idx);
  qDebug() << "Axis changed" << idx;
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
  ui->qle_centerX->setText(QString::number(cdParams->center[FFBConditionEffectParameters::Axis::X]));
  ui->qle_deadbandX->setText(QString::number(cdParams->deadband[FFBConditionEffectParameters::Axis::X]));
  ui->qle_leftCoeffX->setText(QString::number(cdParams->leftCoeff[FFBConditionEffectParameters::Axis::X]));
  ui->qle_rightCoeffX->setText(QString::number(cdParams->rightCoeff[FFBConditionEffectParameters::Axis::X]));
  ui->qle_leftSatX->setText(QString::number(cdParams->leftSat[FFBConditionEffectParameters::Axis::X]));
  ui->qle_rightSatX->setText(QString::number(cdParams->rightCoeff[FFBConditionEffectParameters::Axis::X]));
  ui->qle_centerY->setText(QString::number(cdParams->center[FFBConditionEffectParameters::Axis::Y]));
  ui->qle_deadbandY->setText(QString::number(cdParams->deadband[FFBConditionEffectParameters::Axis::Y]));
  ui->qle_leftCoeffY->setText(QString::number(cdParams->leftCoeff[FFBConditionEffectParameters::Axis::Y]));
  ui->qle_rightCoeffY->setText(QString::number(cdParams->rightCoeff[FFBConditionEffectParameters::Axis::Y]));
  ui->qle_leftSatY->setText(QString::number(cdParams->leftSat[FFBConditionEffectParameters::Axis::Y]));
  ui->qle_rightSatY->setText(QString::number(cdParams->rightCoeff[FFBConditionEffectParameters::Axis::Y]));
  return true;
}

FFBConditionEffectParameters::Axis ConditionEffectSettings::axis() const
{
  switch (ui->cbox_axis->currentIndex()) {
    case 0:
      return FFBConditionEffectParameters::Axis::X;
    case 1:
      return FFBConditionEffectParameters::Axis::Y;
    default:
      return FFBConditionEffectParameters::Axis::NONE;
  }
}

QString ConditionEffectSettings::centerX() const
{
  return ui->qle_centerX->text();
}

QString ConditionEffectSettings::centerY() const
{
  return ui->qle_centerY->text();
}

QString ConditionEffectSettings::deadbandX() const
{
  return ui->qle_deadbandX->text();
}

QString ConditionEffectSettings::deadbandY() const
{
  return ui->qle_deadbandY->text();
}

QString ConditionEffectSettings::leftCoeffX() const
{
  return ui->qle_leftCoeffX->text();
}

QString ConditionEffectSettings::leftCoeffY() const
{
  return ui->qle_leftCoeffY->text();
}

QString ConditionEffectSettings::rightCoeffX() const
{
  return ui->qle_rightCoeffX->text();
}

QString ConditionEffectSettings::rightCoeffY() const
{
  return ui->qle_rightCoeffY->text();
}

QString ConditionEffectSettings::leftSatX() const
{
  return ui->qle_leftSatX->text();
}

QString ConditionEffectSettings::leftSatY() const
{
  return ui->qle_leftSatY->text();
}

QString ConditionEffectSettings::rightSatX() const
{
  return ui->qle_rightSatX->text();
}

QString ConditionEffectSettings::rightSatY() const
{
  return ui->qle_rightSatY->text();
}

int ConditionEffectSettings::subtypeIdx() const
{
  return ui->cbox_subtype->currentIndex();
}

ConditionEffectSettings::~ConditionEffectSettings()
{
  delete ui;
}
