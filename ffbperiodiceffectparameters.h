#ifndef FFBPERIODICEFFECTPARAMETERS_H
#define FFBPERIODICEFFECTPARAMETERS_H

#include "ffbeffectparameters.h"
#include "ffbenvelopeparameters.h"

class FFBPeriodicEffectParameters : public FFBEffectParameters, public FFBEnvelopeParameters
{
public:
  FFBPeriodicEffectParameters();

  bool magnitudeFromString(const QString& magnitude);
  bool offsetFromString(const QString& offset);
  bool periodFromString(const QString& period);
  bool phaseFromString(const QString& phase);
  void waveformFromIdx(PeriodicWaveforms waveform);

  int magnitude;
  int offset;
  int period;
  int phase;
  PeriodicWaveforms waveform;
};

#endif // FFBPERIODICEFFECTPARAMETERS_H
