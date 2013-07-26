#include "ffbconstanteffectparameters.h"

FFBConstantEffectParameters::FFBConstantEffectParameters() :
  FFBEffectParameters(), FFBEnvelopeParameters(),
  level(0)
{}

bool FFBConstantEffectParameters::levelFromString(const QString& level)
{
  bool ok;
  this->level = level.toInt(&ok);

  return ok;
}

FFBConstantEffectParameters::~FFBConstantEffectParameters()
{
}
