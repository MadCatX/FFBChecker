#include "ffbrampeffectparameters.h"

FFBRampEffectParameters::FFBRampEffectParameters() :
  FFBEffectParameters(), FFBEnvelopeParameters(),
  endLevel(0),
  startLevel(0)
{
}

bool FFBRampEffectParameters::endLevelFromString(const QString& endLevel)
{
  bool ok;
  this->endLevel = endLevel.toInt(&ok);
  return ok;
}

bool FFBRampEffectParameters::startLevelFromString(const QString& startLevel)
{
  bool ok;
  this->startLevel = startLevel.toInt(&ok);
  return ok;
}

