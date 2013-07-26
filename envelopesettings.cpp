#include "envelopesettings.h"
#include "ui_envelopesettings.h"
#include <QDebug>

EnvelopeSettings::EnvelopeSettings(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::EnvelopeSettings)
{
  ui->setupUi(this);
}

QString EnvelopeSettings::attackLength() const
{
  return ui->qle_attackLength->text();
}

QString EnvelopeSettings::attackLevel() const
{
  return ui->qle_attackLevel->text();
}

QString EnvelopeSettings::fadeLength() const
{
  return ui->qle_fadeLength->text();
}

QString EnvelopeSettings::fadeLevel() const
{
  return ui->qle_fadeLevel->text();
}

bool EnvelopeSettings::fillFromParameters(const std::shared_ptr<FFBEffectParameters> params)
{
  try {
    const std::shared_ptr<FFBEnvelopeParameters> envParams = std::dynamic_pointer_cast<FFBEnvelopeParameters>(params);

    ui->qle_attackLength->setText(QString::number(envParams->attackLength));
    ui->qle_attackLevel->setText(QString::number(envParams->attackLevel));
    ui->qle_fadeLength->setText(QString::number(envParams->fadeLength));
    ui->qle_fadeLevel->setText(QString::number(envParams->fadeLevel));
    return true;
  } catch (std::bad_cast& ex) {
    qCritical(ex.what());
    return false;
  }
  return false;
}

EnvelopeSettings::~EnvelopeSettings()
{
  delete ui;
}
