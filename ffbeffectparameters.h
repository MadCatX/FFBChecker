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
  bool repeatFromString(const QString& repeat);
  bool replayDelayFromString(const QString& replayDelay);
  bool replayLengthFromString(const QString& replayLength);

  int direction;
  int repeat;
  int replayDelay;
  int64_t replayLength;
};

#endif // FFBEFFECTPARAMETERS_H
