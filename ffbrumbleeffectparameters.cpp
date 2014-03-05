#include "ffbrumbleeffectparameters.h"

FFBRumbleEffectParameters::FFBRumbleEffectParameters()
{
}

bool FFBRumbleEffectParameters::strongMagnitudeFromString(const QString& strong)
{
  return magnitudeFromString(strong, strongMagnitude);
}

bool FFBRumbleEffectParameters::weakMagnitudeFromString(const QString& weak)
{
  return magnitudeFromString(weak, weakMagnitude);
}

bool FFBRumbleEffectParameters::magnitudeFromString(const QString& str, quint16& val)
{
  bool ok;
  val = str.toInt(&ok);

  return ok;
}
