#include "conditioneffectsettings.h"
#include "ui_conditioneffectsettings.h"
#include <QDebug>

ConditionEffectSettings::ConditionEffectSettings(QWidget* parent) :
  EffectSettings(parent),
  ui(new Ui::ConditionEffectSettings)
{
  ui->setupUi(this);

  ui->cbox_axis->setItemData(0, static_cast<std::underlying_type<FFBConditionEffectParameters::Axis>::type>(FFBConditionEffectParameters::Axis::X));
  ui->cbox_axis->setItemData(1, static_cast<std::underlying_type<FFBConditionEffectParameters::Axis>::type>(FFBConditionEffectParameters::Axis::Y));
  connect(ui->cbox_axis, SIGNAL(currentIndexChanged(int)), this, SLOT(axisChanged(const int)));
  axisChanged(ui->cbox_axis->currentIndex());
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

QString ConditionEffectSettings::conditionSubtypeToConditionName(const ConditionSubtypes subtype) const
{
  switch (subtype) {
    case ConditionSubtypes::DAMPER:
      return "Damper";
    case ConditionSubtypes::FRICTION:
      return "Friction";
    case ConditionSubtypes::INERTIA:
      return "Inertia";
    case ConditionSubtypes::SPRING:
      return "Spring";
    default:
      return "Unknown subtype";
  }
}

void ConditionEffectSettings::fillAvailableSubtypesList(const std::vector<ConditionSubtypes>& list)
{
  ui->cbox_subtype->clear();
  for (const ConditionSubtypes subtype : list)
    ui->cbox_subtype->addItem(conditionSubtypeToConditionName(subtype), static_cast<std::underlying_type<ConditionSubtypes>::type>(subtype));
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
  ui->qle_rightSatX->setText(QString::number(cdParams->rightSat[FFBConditionEffectParameters::Axis::X]));

  ui->qle_centerY->setText(QString::number(cdParams->center[FFBConditionEffectParameters::Axis::Y]));
  ui->qle_deadbandY->setText(QString::number(cdParams->deadband[FFBConditionEffectParameters::Axis::Y]));
  ui->qle_leftCoeffY->setText(QString::number(cdParams->leftCoeff[FFBConditionEffectParameters::Axis::Y]));
  ui->qle_rightCoeffY->setText(QString::number(cdParams->rightCoeff[FFBConditionEffectParameters::Axis::Y]));
  ui->qle_leftSatY->setText(QString::number(cdParams->leftSat[FFBConditionEffectParameters::Axis::Y]));
  ui->qle_rightSatY->setText(QString::number(cdParams->rightSat[FFBConditionEffectParameters::Axis::Y]));
  return true;
}

FFBConditionEffectParameters::Axis ConditionEffectSettings::axis() const
{
  FFBConditionEffectParameters::Axis a = *static_cast<FFBConditionEffectParameters::Axis*>(ui->cbox_axis->currentData(Qt::UserRole).data());
  return a;
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

ConditionSubtypes ConditionEffectSettings::subtype() const
{
  ConditionSubtypes subtype = *static_cast<ConditionSubtypes*>(ui->cbox_subtype->currentData(Qt::UserRole).data());
  return subtype;
}

ConditionEffectSettings::~ConditionEffectSettings()
{
  delete ui;
}
