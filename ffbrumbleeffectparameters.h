#ifndef FFBRUMBLEEFFECTPARAMETERS_H
#define FFBRUMBLEEFFECTPARAMETERS_H

#include "ffbeffectparameters.h"

class FFBRumbleEffectParameters : public FFBEffectParameters
{
public:
  FFBRumbleEffectParameters();
  bool strongMagnitudeFromString(const QString& strong);
  bool weakMagnitudeFromString(const QString& weak);

  quint16 strongMagnitude;
  quint16 weakMagnitude;

private:
  bool magnitudeFromString(const QString& str, quint16& val);
};

#endif // FFBRUMBLEEFFECTPARAMETERS_H
