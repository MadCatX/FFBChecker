#include "ffbperiodiceffectparameters.h"

FFBPeriodicEffectParameters::FFBPeriodicEffectParameters() :
  FFBEffectParameters(), FFBEnvelopeParameters(),
  magnitude(0),
  offset(0),
  period(0),
  phase(0),
  waveform(PeriodicWaveforms::NONE)
{
}

bool FFBPeriodicEffectParameters::magnitudeFromString(const QString& magnitude)
{
  bool ok;
  this->magnitude = magnitude.toInt(&ok);
  return ok;
}

bool FFBPeriodicEffectParameters::offsetFromString(const QString& offset)
{
  bool ok;
  this->offset = offset.toInt(&ok);
  return ok;
}

bool FFBPeriodicEffectParameters::periodFromString(const QString& period)
{
  bool ok;
  this->period = period.toInt(&ok);
  return ok;
}

bool FFBPeriodicEffectParameters::phaseFromString(const QString& phase)
{
  bool ok;
  this->phase = phase.toInt(&ok);
  return ok;
}

void FFBPeriodicEffectParameters::waveformFromIdx(PeriodicWaveforms waveform)
{
  this->waveform = waveform;
}

