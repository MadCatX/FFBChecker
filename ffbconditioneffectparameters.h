#ifndef FFBCONDITIONEFFECTPARAMETERS_H
#define FFBCONDITIONEFFECTPARAMETERS_H

#include "ffbeffectparameters.h"

class FFBConditionEffectParameters : public FFBEffectParameters
{
public:
  FFBConditionEffectParameters();
  bool centerFromString(const QString& center);
  bool deadbandFromString(const QString& deadband);
  bool leftCoeffFromString(const QString& leftCoeff);
  bool rightCoeffFromString(const QString& rightCoeff);
  bool leftSatFromString(const QString& leftSat);
  bool rightSatFromString(const QString& rightSat);
  inline void subtypeFromIdx(const ConditionSubtypes subtype) { this->subtype = subtype; }

  int center;
  int deadband;
  int leftCoeff;
  int rightCoeff;
  int leftSat;
  int rightSat;
  ConditionSubtypes subtype;
private:
  inline bool qstringToInt(int& val, const QString& str) {
    bool ok = false;
    val = str.toInt(&ok);
    return ok;
  }
};

#endif // FFBCONDITIONEFFECTPARAMETERS_H
