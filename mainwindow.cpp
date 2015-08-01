#include "globalsettings.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets/QMessageBox>
#include <QDebug>

#include "linuxdeviceprober.h"
#ifdef FFBC_HAVE_SDL2
#include "sdl2deviceprober.h"
#endif

const QString MainWindow::res_deviceErrorCap("Device error");
const QString MainWindow::res_effectNotLoaded("Not loaded");
const QString MainWindow::res_effectPlaying("Playing");
const QString MainWindow::res_effectUploaded("Uploaded");
const QString MainWindow::res_inputFormatErrCap("Invalid input format.");

MainWindow::MainWindow(const QString& title, QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this->setWindowTitle(title);

  m_constantEffSet = new ConstantEffectSettings();
  m_periodicEffSet = new PeriodicEffectSettings();
  m_conditionEffSet = new ConditionEffectSettings();
  m_rampEffSet = new RampEffectSettings();
  m_rumbleEffSet = new RumbleEffectSettings();
  ui->qstw_effectSpecifics->addWidget(m_conditionEffSet);
  ui->qstw_effectSpecifics->addWidget(m_constantEffSet);
  ui->qstw_effectSpecifics->addWidget(m_periodicEffSet);
  ui->qstw_effectSpecifics->addWidget(m_rampEffSet);
  ui->qstw_effectSpecifics->addWidget(m_rumbleEffSet);

  if (GlobalSettings::GS()->doSanityChecks)
    ui->ql_noChecksWarning->setHidden(true);

  /* Fill the list of available interfaces */
  ui->cbox_interfaces->addItem("Linux API", static_cast<std::underlying_type<DeviceProber::DeviceInterfaces>::type>(DeviceProber::DeviceInterfaces::LINUX));
#ifdef FFBC_HAVE_SDL2
  if (SDL2DeviceProber::initializeSDL())
    ui->cbox_interfaces->addItem("SDL2", static_cast<std::underlying_type<DeviceProber::DeviceInterfaces>::type>(DeviceProber::DeviceInterfaces::SDL2));
#endif

  ui->cbox_interfaces->setCurrentIndex(0);
  createDeviceProber(DeviceProber::DeviceInterfaces::LINUX);
  fillDeviceList();

  connect(ui->cbox_devices, SIGNAL(activated(const int)), this, SLOT(onDeviceSelected(const int)));
  connect(ui->cbox_effectSlots, SIGNAL(activated(const int)), this, SLOT(onEffectSlotSelected(const int)));
  connect(ui->cbox_effectTypes, SIGNAL(activated(const int)), this, SLOT(onEffectTypeSelected(const int)));
  connect(ui->cbox_interfaces, SIGNAL(activated(int)), this, SLOT(onInterfaceSelected(const int)));
  connect(ui->qpb_refreshDevices, SIGNAL(clicked()), this, SLOT(onRefreshDevicesClicked()));
  connect(ui->qpb_remove, SIGNAL(clicked()), this, SLOT(onRemoveEffectClicked()));
  connect(ui->qpb_start, SIGNAL(clicked()), this, SLOT(onStartEffectClicked()));
  connect(ui->qpb_stop, SIGNAL(clicked()), this, SLOT(onStopEffectClicked()));
  connect(ui->qpb_upload, SIGNAL(clicked()), this, SLOT(onUploadEffectClicked()));
}

bool MainWindow::createDeviceProber(const DeviceProber::DeviceInterfaces iface)
{
  std::shared_ptr<DeviceProber> prober;

  if (m_prober != nullptr) {
    if (m_prober->type == iface)
      return false;

    m_prober->closeAllDevices();
  }

  switch (iface) {
  case DeviceProber::DeviceInterfaces::LINUX:
    prober = std::make_shared<LinuxDeviceProber>();
    break;
#ifdef FFBC_HAVE_SDL2
  case DeviceProber::DeviceInterfaces::SDL2:
    prober = std::make_shared<SDL2DeviceProber>();
    break;
#endif
  default:
    QMessageBox::critical(this, "Cannot probe devices", "Selected interface is not supported yet.");
    break;
  }

  m_prober = prober;
  return true;
}

EffectSettings* MainWindow::effectSettingsByType(FFBEffectTypes type)
{
  switch (type) {
    case FFBEffectTypes::CONSTANT:
      return m_constantEffSet;
    case FFBEffectTypes::PERIODIC:
      return m_periodicEffSet;
    case FFBEffectTypes::CONDITION:
      return m_conditionEffSet;
    case FFBEffectTypes::RAMP:
      return m_rampEffSet;
    case FFBEffectTypes::RUMBLE:
      return m_rumbleEffSet;
    default:
      abort();
  }
}

QString MainWindow::effectTypeToEffectName(const FFBEffectTypes etype) const
{
  switch (etype) {
    case FFBEffectTypes::CONSTANT:
      return "Constant force";
    case FFBEffectTypes::PERIODIC:
      return "Periodic force";
    case FFBEffectTypes::RAMP:
      return "Ramp";
    case FFBEffectTypes::CONDITION:
      return "Condition";
    case FFBEffectTypes::RUMBLE:
      return "Rumble";
    default:
      return "Unknown effect";
  }
}

void MainWindow::fillDeviceList()
{
  ui->cbox_devices->clear();

  if (m_prober == nullptr)
    return;

  for (const DeviceProber::DeviceInfo& dinfo : m_prober->listDevices()) {
    QString name;
    if (dinfo.name.length() == 0)
      name = "(no name)";
    else
      name = dinfo.name;

    QString tag = QString("%1 [%2]").arg(name).arg(dinfo.id.toString());
    ui->cbox_devices->addItem(tag, dinfo.id.toString());
  }
}

void MainWindow::fillEffectSlotsList(const int effectCount)
{
  ui->cbox_effectSlots->clear();
  for (int i = 1; i <= effectCount; i++)
    ui->cbox_effectSlots->addItem(QString::number(i), i-1);
}

void MainWindow::fillEffectTypesList(const std::vector<FFBEffectTypes>& list)
{
  ui->cbox_effectTypes->clear();
  for (const FFBEffectTypes etype : list)
    ui->cbox_effectTypes->addItem(effectTypeToEffectName(etype), static_cast<std::underlying_type<FFBEffectTypes>::type>(etype));
}

void MainWindow::onDeviceSelected(const int cboxIdx)
{
  Q_UNUSED(cboxIdx);

  QString path = ui->cbox_devices->currentData(Qt::UserRole).toString();
  ui->cbox_effectSlots->clear();
  m_activeDevice = m_prober->openDevice(path);

  if (m_activeDevice == nullptr)
    return;

  fillEffectSlotsList(m_activeDevice->maxEffectCount());
  fillEffectTypesList(m_activeDevice->availableEffectsList());
  m_conditionEffSet->fillAvailableSubtypesList(m_activeDevice->availableConditionSubtypesList());
  m_periodicEffSet->fillAvailableWaveformsList(m_activeDevice->availableWaveformsList());
  ui->cbox_effectSlots->setCurrentIndex(0);
  onEffectSlotSelected(0);
}

void MainWindow::onEffectSlotSelected(const int cboxIdx)
{
  int effectIdx;
  bool ok;

  Q_UNUSED(cboxIdx);

  if (m_activeDevice == nullptr)
    return;

  effectIdx = ui->cbox_effectSlots->currentData(Qt::UserRole).toInt(&ok);
  if (!ok) {
    showErrorMsgBox(ErrorMessages::BAD_EFFECT_SLOT);
    return;
  }
  FFBEffectTypes etype = m_activeDevice->effectTypeByEffectIdx(effectIdx);
  qDebug() << static_cast<int>(etype);
  if (etype == FFBEffectTypes::NONE) {
    qDebug() << "Empty effect";
    setEffectTypeIndexByType(etype);
    ui->qstw_effectSpecifics->setCurrentWidget(effectSettingsByType(FFBEffectTypes::CONSTANT));
    setEffectStatusText(FFBEffect::FFBEffectStatus::NOT_LOADED);
    return;
  }

  const std::shared_ptr<FFBEffectParameters> params = m_activeDevice->effectParameters(effectIdx);
  /* Set global parameters */
  ui->qle_direction->setText(QString::number(params->direction));
  ui->qle_replayDelay->setText(QString::number(params->replayDelay));
  ui->qle_replayLength->setText(QString::number(params->replayLength));

  EffectSettings* efs = effectSettingsByType(etype);
  if (!efs->fillFromParameters(params))
    QMessageBox::warning(this, "UI error", "Unable to read effect parameters.");
  setEffectTypeIndexByType(etype);
  ui->qstw_effectSpecifics->setCurrentWidget(efs);
  setEffectStatusText(m_activeDevice->effectStatusByIdx(effectIdx));
}

void MainWindow::onEffectTypeSelected(const int cboxIdx)
{
  Q_UNUSED(cboxIdx);

  if (m_activeDevice == nullptr)
    return;

  FFBEffectTypes etype = *static_cast<FFBEffectTypes*>(ui->cbox_effectTypes->currentData(Qt::UserRole).data());
  ui->qstw_effectSpecifics->setCurrentWidget(effectSettingsByType(etype));
}

void MainWindow::onInterfaceSelected(const int cboxIdx)
{
  Q_UNUSED(cboxIdx);
  bool ok;
  unsigned int rawIface;
  DeviceProber::DeviceInterfaces iface;

  rawIface = ui->cbox_interfaces->currentData().toUInt(&ok);
  if (!ok) {
    QMessageBox::critical(this, "Invalid data", "Invalid data passed as interface type.");
    return;
  }


  iface = static_cast<DeviceProber::DeviceInterfaces>(rawIface);
  if (!createDeviceProber(iface))
    return;

  ui->cbox_effectSlots->clear();
  fillDeviceList();
}

void MainWindow::onRefreshDevicesClicked()
{
  fillDeviceList();
}

void MainWindow::onRemoveEffectClicked()
{
  int effectIdx;
  bool ok;

  if (m_activeDevice == nullptr)
    return;

  effectIdx = ui->cbox_effectSlots->currentData(Qt::UserRole).toInt(&ok);
  if (!ok) {
    showErrorMsgBox(ErrorMessages::BAD_EFFECT_SLOT);
    return;
  }

  if (!m_activeDevice->removeAndEraseEffect(effectIdx))
    showErrorMsgBox(ErrorMessages::CANT_REMOVE_EFFECT);
  else
    setEffectStatusText(m_activeDevice->effectStatusByIdx(effectIdx));
}

void MainWindow::onStartEffectClicked()
{
  bool ok;
  int effectSlot;

  if (m_activeDevice == nullptr)
    return;

  FFBEffectTypes etype = *static_cast<FFBEffectTypes*>(ui->cbox_effectTypes->currentData(Qt::UserRole).data());
  std::shared_ptr<FFBEffectParameters> params;
  effectSlot = ui->cbox_effectSlots->currentData().toInt(&ok);
  if (!ok) {
    showErrorMsgBox(ErrorMessages::BAD_EFFECT_SLOT);
    return;
  }

  if (!readEffectParameters(params, etype)) {
    qDebug() << "Cannot read effect params.";
    return;
  }
  bool ret = m_activeDevice->startEffect(effectSlot, etype, params);
  if (ret)
    setEffectStatusText(m_activeDevice->effectStatusByIdx(effectSlot));
  else
    showErrorMsgBox(ErrorMessages::CANT_START_EFFECT);
}

void MainWindow::onStopEffectClicked()
{
  int effectSlot;
  bool ok;

  if (m_activeDevice == nullptr)
    return;

  effectSlot = ui->cbox_effectSlots->currentData().toInt(&ok);
  if (!ok) {
    showErrorMsgBox(ErrorMessages::BAD_EFFECT_SLOT);
    return;
  }
  m_activeDevice->stopEffect(effectSlot);
  setEffectStatusText(m_activeDevice->effectStatusByIdx(effectSlot));
}

void MainWindow::onUploadEffectClicked()
{
  bool ok;
  int effectSlot;

  if (m_activeDevice == nullptr)
    return;

  FFBEffectTypes etype = *static_cast<FFBEffectTypes*>(ui->cbox_effectTypes->currentData(Qt::UserRole).data());
  std::shared_ptr<FFBEffectParameters> params;
  effectSlot = ui->cbox_effectSlots->currentData().toInt(&ok);
  if (!ok) {
    showErrorMsgBox(ErrorMessages::BAD_EFFECT_SLOT);
    return;
  }

  if (!readEffectParameters(params, etype)) {
    qDebug() << "Cannot read effect params.";
    return;
  }
  bool ret = m_activeDevice->uploadEffect(effectSlot, etype, params);
  if (ret)
    setEffectStatusText(m_activeDevice->effectStatusByIdx(effectSlot));
  else
    showErrorMsgBox(ErrorMessages::CANT_UPLOAD_EFFECT);
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
    case FFBEffectTypes::CONDITION:
    {
      std::shared_ptr<FFBConditionEffectParameters> iParams = std::shared_ptr<FFBConditionEffectParameters>(new FFBConditionEffectParameters);
      if (!readGeneralEffectParameters(iParams))
        return false;

      if (!iParams->centerFromString(m_conditionEffSet->centerX(), FFBConditionEffectParameters::Axis::X)) {
        QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Center\"");
        return false;
      }
      if (!iParams->centerFromString(m_conditionEffSet->centerY(), FFBConditionEffectParameters::Axis::Y)) {
        QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Center\"");
        return false;
      }
      if (!iParams->deadbandFromString(m_conditionEffSet->deadbandX(), FFBConditionEffectParameters::Axis::X)) {
        QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Deadband\"");
        return false;
      }
      if (!iParams->deadbandFromString(m_conditionEffSet->deadbandY(), FFBConditionEffectParameters::Axis::Y)) {
        QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Deadband\"");
        return false;
      }
      if (!iParams->leftCoeffFromString(m_conditionEffSet->leftCoeffX(), FFBConditionEffectParameters::Axis::X)) {
        QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Left coefficient\"");
        return false;
      }
      if (!iParams->leftCoeffFromString(m_conditionEffSet->leftCoeffY(), FFBConditionEffectParameters::Axis::Y)) {
        QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Left coefficient\"");
        return false;
      }
      if (!iParams->rightCoeffFromString(m_conditionEffSet->rightCoeffX(), FFBConditionEffectParameters::Axis::X)) {
        QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Right coefficient\"");
        return false;
      }
      if (!iParams->rightCoeffFromString(m_conditionEffSet->rightCoeffY(), FFBConditionEffectParameters::Axis::Y)) {
        QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Right coefficient\"");
        return false;
      }
      if (!iParams->leftSatFromString(m_conditionEffSet->leftSatX(), FFBConditionEffectParameters::Axis::X)) {
        QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Left saturation\"");
        return false;
      }
      if (!iParams->leftSatFromString(m_conditionEffSet->leftSatY(), FFBConditionEffectParameters::Axis::Y)) {
        QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Left saturation\"");
        return false;
      }
      if (!iParams->rightSatFromString(m_conditionEffSet->rightSatX(), FFBConditionEffectParameters::Axis::X)) {
        QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Right saturation\"");
        return false;
      }
      if (!iParams->rightSatFromString(m_conditionEffSet->rightSatY(), FFBConditionEffectParameters::Axis::Y)) {
        QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Right saturation\"");
        return false;
      }

      ConditionSubtypes subtype = m_conditionEffSet->subtype();
      iParams->subtype = subtype;

      params = iParams;
      break;
    }
    case FFBEffectTypes::RAMP: {
      std::shared_ptr<FFBRampEffectParameters> iParams = std::shared_ptr<FFBRampEffectParameters>(new FFBRampEffectParameters);
      if (!readGeneralEffectParameters(iParams))
        return false;
      if (!readEnvelopeParameters(iParams, m_rampEffSet->envelopeSettings()))
        return false;

      if (!iParams->endLevelFromString(m_rampEffSet->endLevel())) {
        QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"End level\"");
        return false;
      }
      if (!iParams->startLevelFromString(m_rampEffSet->startLevel())) {
        QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Start level\"");
        return false;
      }

      params = iParams;
      break;
    }
    case FFBEffectTypes::RUMBLE: {
      std::shared_ptr<FFBRumbleEffectParameters> iParams(new FFBRumbleEffectParameters());
      if (!readGeneralEffectParameters(iParams))
        return false;

      if (!iParams->strongMagnitudeFromString(m_rumbleEffSet->strongMagnitude())) {
        QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Strong magnitude\"");
        return false;
      }
      if (!iParams->weakMagnitudeFromString(m_rumbleEffSet->weakMagnitude())) {
        QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Weak magnitude\"");
        return false;
      }

      params = iParams;
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
  if (!params->repeatFromString(ui->qle_repeat->text())) {
    QMessageBox::warning(this, res_inputFormatErrCap, "Invalid data in field \"Replay\"");
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
    case FFBEffect::FFBEffectStatus::UPLOADED:
      ui->ql_effectStatus->setText(res_effectUploaded);
      break;
    }
}

void MainWindow::setEffectTypeIndexByType(const FFBEffectTypes etype)
{
  for (int idx = 0; idx < ui->cbox_effectTypes->count(); idx++) {
    FFBEffectTypes ietype = *static_cast<FFBEffectTypes*>(ui->cbox_effectTypes->itemData(idx, Qt::UserRole).data());
    if (ietype == etype) {
      ui->cbox_effectTypes->setCurrentIndex(idx);
      return;
    }
  }
}

void MainWindow::showErrorMsgBox(const ErrorMessages msgCode)
{
  switch (msgCode) {
  case ErrorMessages::BAD_EFFECT_SLOT:
    QMessageBox::critical(this, "Runtime error", "Nonsensical data passed as effect slot index.");
    break;
  case ErrorMessages::CANT_REMOVE_EFFECT:
    QMessageBox::warning(this, res_deviceErrorCap, "Unable to remove the effect.");
    break;
  case ErrorMessages::CANT_START_EFFECT:
    QMessageBox::warning(this, res_deviceErrorCap, "Unable to start the effect.");
    break;
  case ErrorMessages::CANT_UPLOAD_EFFECT:
    QMessageBox::warning(this, res_deviceErrorCap, "Unable to upload effect.");
    break;
  }
}


MainWindow::~MainWindow()
{
  delete ui;
}
