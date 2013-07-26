#ifndef FFBENVELOPEPARAMETERS_H
#define FFBENVELOPEPARAMETERS_H

#include <QtCore/QString>

class FFBEnvelopeParameters
{
public:
  FFBEnvelopeParameters();
  bool attackLengthFromString(const QString& attackLength);
  bool attackLevelFromString(const QString& attackLevel);
  bool fadeLengthFromString(const QString& fadeLength);
  bool fadeLevelFromString(const QString& fadeLevel);

  int attackLength;
  int attackLevel;
  int fadeLength;
  int fadeLevel;
};

#endif // FFBENVELOPEPARAMETERS_H
