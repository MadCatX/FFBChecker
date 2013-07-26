#ifndef FFBEFFECTPARAMETERS_H
#define FFBEFFECTPARAMETERS_H

#include "globals.h"
#include <memory>
#include <QtCore/QObject>

class FFBEffectParameters
{
public:
  FFBEffectParameters();
  virtual ~FFBEffectParameters();

  bool directionFromString(const QString& direction);
  bool replayDelayFromString(const QString& replayDelay);
  bool replayLengthFromString(const QString& replayLength);

  int direction;
  int replayDelay;
  int replayLength;
};

#endif // FFBEFFECTPARAMETERS_H
