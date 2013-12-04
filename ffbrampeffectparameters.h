#ifndef FFBRAMPEFFECTPARAMETERS_H
#define FFBRAMPEFFECTPARAMETERS_H

#include "ffbeffectparameters.h"
#include "ffbenvelopeparameters.h"

class FFBRampEffectParameters : public FFBEffectParameters, public FFBEnvelopeParameters
{
public:
  FFBRampEffectParameters();
  bool endLevelFromString(const QString& endLevel);
  bool startLevelFromString(const QString& startLevel);

  int endLevel;
  int startLevel;
};

#endif // FFBRAMPEFFECTPARAMETERS_H
