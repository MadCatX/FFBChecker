#ifndef FFBCONDITIONEFFECTPARAMETERS_H
#define FFBCONDITIONEFFECTPARAMETERS_H

#include "ffbeffectparameters.h"
#include <map>

class FFBConditionEffectParameters : public FFBEffectParameters
{
public:
  enum class Axis : quint8 { NONE, X, Y };

  FFBConditionEffectParameters();
  bool centerFromString(const QString& center, Axis a);
  bool deadbandFromString(const QString& deadband, Axis a);
  bool leftCoeffFromString(const QString& leftCoeff, Axis a);
  bool rightCoeffFromString(const QString& rightCoeff, Axis a);
  bool leftSatFromString(const QString& leftSat, Axis a);
  bool rightSatFromString(const QString& rightSat, Axis a);
  inline void subtypeFromIdx(const ConditionSubtypes subtype) { this->subtype = subtype; }

  std::map<Axis, int> center;
  std::map<Axis, int> deadband;
  std::map<Axis, int> leftCoeff;
  std::map<Axis, int> rightCoeff;
  std::map<Axis, int> leftSat;
  std::map<Axis, int> rightSat;
  ConditionSubtypes subtype;
private:
};

#endif // FFBCONDITIONEFFECTPARAMETERS_H
