#include "ffbconditioneffectparameters.h"

FFBConditionEffectParameters::FFBConditionEffectParameters() :
  FFBEffectParameters(),
  center(0),
  deadband(0),
  leftCoeff(0),
  rightCoeff(0),
  leftSat(0),
  rightSat(0)
{}

bool FFBConditionEffectParameters::centerFromString(const QString& center)
{
  return qstringToInt(this->center, center);
}

bool FFBConditionEffectParameters::deadbandFromString(const QString& deadband)
{
  return qstringToInt(this->deadband, deadband);
}

bool FFBConditionEffectParameters::leftCoeffFromString(const QString& leftCoeff)
{
  return qstringToInt(this->leftCoeff, leftCoeff);
}

bool FFBConditionEffectParameters::rightCoeffFromString(const QString& rightCoeff)
{
  return qstringToInt(this->rightCoeff, rightCoeff);
}

bool FFBConditionEffectParameters::leftSatFromString(const QString& leftSat)
{
  return qstringToInt(this->leftSat, leftSat);
}

bool FFBConditionEffectParameters::rightSatFromString(const QString& rightSat)
{
  return qstringToInt(this->rightSat, rightSat);
}


