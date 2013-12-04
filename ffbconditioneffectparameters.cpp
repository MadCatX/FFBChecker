#include "ffbconditioneffectparameters.h"

FFBConditionEffectParameters::FFBConditionEffectParameters() :
  FFBEffectParameters()
{}

bool FFBConditionEffectParameters::centerFromString(const QString& center, Axis a)
{
  bool ok = false;
  int val = center.toInt(&ok);
  if (!ok) return false;

  this->center[a] = val;
  return true;
}

bool FFBConditionEffectParameters::deadbandFromString(const QString& deadband, Axis a)
{
  bool ok = false;
  int val = deadband.toInt(&ok);
  if (!ok) return false;

  this->deadband[a] = val;
  return true;
}

bool FFBConditionEffectParameters::leftCoeffFromString(const QString& leftCoeff, Axis a)
{
  bool ok = false;
  int val = leftCoeff.toInt(&ok);
  if (!ok) return false;

  this->leftCoeff[a] = val;
  return true;
}

bool FFBConditionEffectParameters::rightCoeffFromString(const QString& rightCoeff, Axis a)
{
  bool ok = false;
  int val = rightCoeff.toInt(&ok);
  if (!ok) return false;

  this->rightCoeff[a] = val;
  return true;
}

bool FFBConditionEffectParameters::leftSatFromString(const QString& leftSat, Axis a)
{
  bool ok = false;
  int val = leftSat.toInt(&ok);
  if (!ok) return false;

  this->leftSat[a] = val;
  return true;
}

bool FFBConditionEffectParameters::rightSatFromString(const QString& rightSat, Axis a)
{
  bool ok = false;
  int val = rightSat.toInt(&ok);
  if (!ok) return false;

  this->rightSat[a] = val;
  return true;
}


