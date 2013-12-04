#ifndef FFBCONDITIONEFFECTPARAMETERS_H
#define FFBCONDITIONEFFECTPARAMETERS_H

#include "ffbeffectparameters.h"
#include <map>

class FFBConditionEffectParameters : public FFBEffectParameters
{
public:
  enum class Axis : quint8 { NONE = 0, X = 1, Y = 2 };
  struct Axis_less {
    bool operator()(Axis a, Axis b) const { return quint8(a) == quint8(b); }
  };

  FFBConditionEffectParameters();
  bool centerFromString(const QString& center, Axis a);
  bool deadbandFromString(const QString& deadband, Axis a);
  bool leftCoeffFromString(const QString& leftCoeff, Axis a);
  bool rightCoeffFromString(const QString& rightCoeff, Axis a);
  bool leftSatFromString(const QString& leftSat, Axis a);
  bool rightSatFromString(const QString& rightSat, Axis a);
  inline void subtypeFromIdx(const ConditionSubtypes subtype) { this->subtype = subtype; }

  std::map<Axis, int, Axis_less> center;
  std::map<Axis, int, Axis_less> deadband;
  std::map<Axis, int, Axis_less> leftCoeff;
  std::map<Axis, int, Axis_less> rightCoeff;
  std::map<Axis, int, Axis_less> leftSat;
  std::map<Axis, int, Axis_less> rightSat;
  ConditionSubtypes subtype;
private:
  inline bool qstringToInt(int& val, const QString& str) {
    bool ok = false;
    val = str.toInt(&ok);
    return ok;
  }
};

#endif // FFBCONDITIONEFFECTPARAMETERS_H
