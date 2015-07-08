#include "periodiceffectsettings.h"
#include "ui_periodiceffectsettings.h"

PeriodicEffectSettings::PeriodicEffectSettings(QWidget* parent) :
  EffectSettings(parent),
  ui(new Ui::PeriodicEffectSettings)
{
  ui->setupUi(this);
}

const EnvelopeSettings* PeriodicEffectSettings::envelopeSettings() const
{
  return ui->qwid_envelope;
}

void PeriodicEffectSettings::fillAvailableWaveformsList(const std::vector<PeriodicWaveforms>& list)
{
  ui->cbox_waveform->clear();
  for (const PeriodicWaveforms waveform : list)
    ui->cbox_waveform->addItem(waveformTypeToWaveformName(waveform), static_cast<std::underlying_type<PeriodicWaveforms>::type>(waveform));
}

bool PeriodicEffectSettings::fillFromParameters(const std::shared_ptr<FFBEffectParameters> params)
{
  try {
    const std::shared_ptr<FFBPeriodicEffectParameters> pParams = std::dynamic_pointer_cast<FFBPeriodicEffectParameters>(params);

    ui->qle_magnitude->setText(QString::number(pParams->magnitude));
    ui->qle_offset->setText(QString::number(pParams->offset));
    ui->qle_period->setText(QString::number(pParams->period));
    ui->qle_phase->setText(QString::number(pParams->phase));
    return ui->qwid_envelope->fillFromParameters(pParams);
  } catch (std::bad_cast& ex) {
    qCritical(ex.what());
    return false;
  }
  return false;
}

QString PeriodicEffectSettings::magnitude() const
{
  return ui->qle_magnitude->text();
}

QString PeriodicEffectSettings::offset() const
{
  return ui->qle_offset->text();
}

QString PeriodicEffectSettings::period() const
{
  return ui->qle_period->text();
}

QString PeriodicEffectSettings::phase() const
{
  return ui->qle_phase->text();
}

QString PeriodicEffectSettings::waveformTypeToWaveformName(const PeriodicWaveforms waveform) const
{
  switch (waveform) {
    case PeriodicWaveforms::SQUARE:
      return "Square";
    case PeriodicWaveforms::TRIANGLE:
      return "Triangle";
    case PeriodicWaveforms::SINE:
      return "Sine";
    case PeriodicWaveforms::SAW_UP:
      return "Saw up";
    case PeriodicWaveforms::SAW_DOWN:
      return "Saw down";
    default:
      return "Unknown waveform";
  }
}

int PeriodicEffectSettings::waveformIdx() const
{
  return ui->cbox_waveform->currentIndex();
}

PeriodicEffectSettings::~PeriodicEffectSettings()
{
  delete ui;
}
