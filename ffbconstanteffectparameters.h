#ifndef FFBCONSTANTEFFECTPARAMETERS_H
#define FFBCONSTANTEFFECTPARAMETERS_H

#include "ffbeffectparameters.h"
#include "ffbenvelopeparameters.h"

class FFBConstantEffectParameters : public FFBEffectParameters, public FFBEnvelopeParameters
{
public:
  FFBConstantEffectParameters();
  ~FFBConstantEffectParameters();

  bool levelFromString(const QString& level);

  int level;
};

#endif // FFBCONSTANTEFFECTPARAMETERS_H
