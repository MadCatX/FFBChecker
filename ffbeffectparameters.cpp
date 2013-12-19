#include "ffbeffectparameters.h"

FFBEffectParameters::FFBEffectParameters() :
  direction(0),
  repeat(1),
  replayDelay(0),
  replayLength(0)
{
}

bool FFBEffectParameters::directionFromString(const QString& direction)
{
  bool ok;
  this->direction = direction.toInt(&ok);

  return ok;
}

bool FFBEffectParameters::repeatFromString(const QString& repeat)
{
  bool ok;
  this->repeat = repeat.toInt(&ok);

  return ok;
}

bool FFBEffectParameters::replayDelayFromString(const QString& replayDelay)
{
  bool ok;
  this->replayDelay = replayDelay.toInt(&ok);

  return ok;
}

bool FFBEffectParameters::replayLengthFromString(const QString& replayLength)
{
  bool ok;
  this->replayLength = replayLength.toInt(&ok);

  return ok;
}

FFBEffectParameters::~FFBEffectParameters()
{
}
