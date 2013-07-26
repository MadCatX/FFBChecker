#include "ffbenvelopeparameters.h"

FFBEnvelopeParameters::FFBEnvelopeParameters()
{}

bool FFBEnvelopeParameters::attackLengthFromString(const QString& attackLength)
{
  bool ok;
  this->attackLength = attackLength.toInt(&ok);
  return ok;
}

bool FFBEnvelopeParameters::attackLevelFromString(const QString& attackLevel)
{
  bool ok;
  this->attackLevel = attackLevel.toInt(&ok);
  return ok;
}

bool FFBEnvelopeParameters::fadeLengthFromString(const QString& fadeLength)
{
  bool ok;
  this->fadeLength = fadeLength.toInt(&ok);
  return ok;
}


bool FFBEnvelopeParameters::fadeLevelFromString(const QString& fadeLevel)
{
  bool ok;
  this->fadeLevel = fadeLevel.toInt(&ok);
  return ok;
}
