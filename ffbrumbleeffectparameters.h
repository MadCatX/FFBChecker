#ifndef FFBRUMBLEEFFECTPARAMETERS_H
#define FFBRUMBLEEFFECTPARAMETERS_H

#include "ffbeffectparameters.h"

class FFBRumbleEffectParameters : public FFBEffectParameters
{
public:
  FFBRumbleEffectParameters();
  bool strongMagnitudeFromString(const QString& strong);
  bool weakMagnitudeFromString(const QString& weak);

  int strongMagnitude;
  int weakMagnitude;

private:
  bool magnitudeFromString(const QString& str, int& val);
};

#endif // FFBRUMBLEEFFECTPARAMETERS_H
