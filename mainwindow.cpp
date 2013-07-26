#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets/QMessageBox>
#include <QDebug>

const QString MainWindow::res_effectNotLoaded("Not loaded");
const QString MainWindow::res_effectPlaying("Playing");
const QString MainWindow::res_effectStopped("Stopped");
const QString MainWindow::res_inputFormatErrCap("Invalid input format.");

MainWindow::MainWindow(std::shared_ptr<DeviceProber> prober, QWidget* parent) :
  QMainWindow(parent),
  m_prober(prober),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  /* HACK: Remove all default widgets from the stack */
  for (int i = 0; i < ui->qstw_effectSpecifics->count(); i++)
    ui->qstw_effectSpecifics->removeWidget(ui->qstw_effectSpecifics->widget(i));

  m_constantEffSet = new ConstantEffectSettings();
  m_periodicEffSet = new PeriodicEffectSettings();
  ui->qstw_effectSpecifics->addWidget(m_constantEffSet);
  ui->qstw_effectSpecifics->addWidget(m_periodicEffSet);

  fillDeviceList();
  connect(ui->cbox_devices, SIGNAL(activated(const QString&)), this, SLOT(onDeviceSelected(const QString&)));
  connect(ui->cbox_effectSlots, SIGNAL(activated(const int)), this, SLOT(onEffectSlotSelected(const int)));
  connect(ui->cbox_effectTypes, SIGNAL(activated(const int)), this, SLOT(onEffectTypeSelected(const int)));
  connect(ui->qpb_refreshDevices, SIGNAL(clicked()), this, SLOT(onRefreshDevicesClicked()));
  connect(ui->qpb_start, SIGNAL(clicked()), this, SLOT(onStartEffectClicked()));
  connect(ui->qpb_stop, SIGNAL(clicked()), this, SLOT(onStopEffectClicked()));
}

EffectSettings* MainWindow::effectSettingsByType(FFBEffectTypes type)
{
  switch (type) {
    case FFBEffectTypes::CONSTANT:
      return m_constantEffSet;
    case FFBEffectTypes::PERIODIC:
      return m_periodicEffSet;
    default:
      abort();
  }
}

void MainWindow::fillDeviceList()
{
  ui->cbox_devices->clear();
  ui->cbox_devices->addItems(m_prober->listDevicesByID());
}
void MainWindow::fillEffectSlotsList(const int idx)
{
  ui->cbox_effectSlots->clear();
  for (int i = 1; i <= idx; i++)
    ui->cbox_effectSlots->addItem(QString::number(i));
}

void MainWindow::fillEffectTypesList(const QStringList& list)
{
  ui->cbox_effectTypes->clear();
  ui->cbox_effectTypes->addItems(list);
}

void MainWindow::onDeviceSelected(const QString& id)
{
  ui->cbox_effectSlots->clear();
  m_activeDevice = m_prober->openDeviceByID(id);

  if (m_activeDevice == nullptr)
    return;

  fillEffectSlotsList(m_activeDevice->maxEffectCount());
  fillEffectTypesList(m_activeDevice->availableEffectsList());
  m_periodicEffSet->fillAvailableWaveformsList(m_activeDevice->availableWaveformsList());
}

void MainWindow::onEffectSlotSelected(const int idx)
{
  if (idx < 0)
    return;
  if (m_activeDevice == nullptr)
    return;

  FFBEffectTypes type = m_activeDevice->effectTypeByEffectIdx(idx);
  qDebug() << static_cast<int>(type);
  if (type == FFBEffectTypes::NONE) {
    qDebug() << "Empty effect";
    ui->cbox_effectTypes->setCurrentIndex(0);
    ui->qstw_effectSpecifics->setCurrentWidget(effectSettingsByType(m_activeDevice->effectTypeFromSelectionIdx(0)));
    setEffectStatusText(FFBEffect::FFBEffectStatus::NOT_LOADED);
    return;
  }

  const std::shared_ptr<FFBEffectParameters> params = m_activeDevice->effectParameters(idx);
  /* Set global parameters */
  ui->qle_direction->setText(QString::number(params->direction));
  ui->qle_replayDelay->setText(QString::number(params->replayDelay));
  ui->qle_replayLength->setText(QString::number(params->replayLength));

  EffectSettings* efs = effectSettingsByType(type);
  if (!efs->fillFromParameters(params))
    QMessageBox::warning(this, "UI error", "Unable to read effect parameters.");
  ui->cbox_effectTypes->setCurrentIndex(m_activeDevice->effectTypeToIdx(type));
  ui->qstw_effectSpecifics->setCurrentWidget(efs);
  setEffectStatusText(m_activeDevice->effectStatusByIdx(idx));
}

void MainWindow::onEffectTypeSelected(const int idx)
{
  if (idx < 0)
    return;
  if (m_activeDevice == nullptr)
    return;

  ui->qstw_effectSpecifics->setCurrentWidget(effectSettingsByType(m_activeDevice->effectTypeFromSelectionIdx(idx)));
}

void MainWindow::onRefreshDevicesClicked()
{
  fillDeviceList();
}

void MainWindow::onStartEffectClicked()
{
  if (m_activeDevice == nullptr)
    return;

  FFBEffectTypes type = m_activeDevice->effectTypeFromSelectionIdx(ui->cbox_effectTypes->currentIndex());
  std::shared_ptr<FFBEffectParameters> params;
  int effectSlot = ui->cbox_effectSlots->currentIndex();
  if (!readEffectParameters(params, type)) {
    qDebug() << "Cannot read effect params.";
    return;
  }
  bool ret = m_activeDevice->startEffect(effectSlot, type, params);
  if (ret)
    setEffectStatusText(m_activeDevice->effectStatusByIdx(effectSlot));
}

void MainWindow::onStopEffectClicked()
{
  if (m_activeDevice == nullptr)
    return;

  int effectSlot = ui->cbox_effectSlots->currentIndex();
  m_activeDevice->stopEffect(effectSlot);
  setEffectStatusText(m_activeDevice->effectStatusByIdx(effectSlot));
}

bool MainWindow::readEnvelopeParameters(std::shared_ptr<FFBEnvelopeParameters> params, const EnvelopeSettings* es)
{
  if (!params->attackLengthFromString(es->attackLength())) {
      QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Attack length\"");
      return false;
  }
  if (!params->attackLevelFromString(es->attackLevel())) {
    QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Attack level\"");
    return false;
  }
  if (!params->fadeLengthFromString(es->fadeLength())) {
    QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Fade length\"");
    return false;
  }
  if (!params->fadeLevelFromString(es->fadeLevel())) {
    QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Fade level\"");
    return false;
  }

  return true;
}

bool MainWindow::readEffectParameters(std::shared_ptr<FFBEffectParameters>& params, FFBEffectTypes type)
{
  switch (type) {
    case FFBEffectTypes::CONSTANT:
    {
      std::shared_ptr<FFBConstantEffectParameters> iparams(new FFBConstantEffectParameters);
      if (!readGeneralEffectParameters(iparams)) {
        return false;
      }
      if (!readEnvelopeParameters(iparams, m_constantEffSet->envelopeSettings())) {
        return false;
      }
      if (!iparams->levelFromString(m_constantEffSet->level())) {
        QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"level\"");
        return false;
      }

      params = iparams;
      break;
    }
    case FFBEffectTypes::PERIODIC:
    {
      std::shared_ptr<FFBPeriodicEffectParameters> iparams(new FFBPeriodicEffectParameters);
      if (!readGeneralEffectParameters(iparams)) {
        return false;
      }
      if (!readEnvelopeParameters(iparams, m_periodicEffSet->envelopeSettings())) {
        return false;
      }
      if (!iparams->magnitudeFromString(m_periodicEffSet->magnitude())) {
          QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Magnitude\"");
          return false ;
      }
      if (!iparams->offsetFromString(m_periodicEffSet->offset())) {
        QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Offset\"");
        return false;
      }
     if (!iparams->periodFromString(m_periodicEffSet->period())) {
        QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Period\"");
        return false;
      }
      if (!iparams->phaseFromString(m_periodicEffSet->phase())) {
        QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Phase\"");
        return false;
      }

      PeriodicWaveforms waveform = m_activeDevice->waveformByIdx(m_periodicEffSet->waveformIdx());
      iparams->waveformFromIdx(waveform);

      params = iparams;
      break;
    }
    default:
      qDebug() << "Unhandled type of effect";
      return false;
  }

  return true;
}

bool MainWindow::readGeneralEffectParameters(std::shared_ptr<FFBEffectParameters> params)
{
  if (!params->directionFromString(ui->qle_direction->text())) {
    QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"direction\"");
    return false;
  }
  if (!params->replayDelayFromString(ui->qle_replayDelay->text())) {
    QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Replay delay\"");
    return false;
  }
  if (!params->replayLengthFromString(ui->qle_replayLength->text())) {
    QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Replay length\"");
    return false;
  }

  return true;
}

void MainWindow::setEffectStatusText(const FFBEffect::FFBEffectStatus status)
{
  switch (status) {
    case FFBEffect::FFBEffectStatus::NOT_LOADED:
      ui->ql_effectStatus->setText(res_effectNotLoaded);
      break;
    case FFBEffect::FFBEffectStatus::PLAYING:
      ui->ql_effectStatus->setText(res_effectPlaying);
      break;
    case FFBEffect::FFBEffectStatus::STOPPED:
      ui->ql_effectStatus->setText(res_effectStopped);
      break;
    }
}

MainWindow::~MainWindow()
{
  delete ui;
}
