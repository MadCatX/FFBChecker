#include "ffbconditioneffect.h"

FFBConditionEffect::FFBConditionEffect() :
  FFBEffect(FFBEffectTypes::CONDITION)
{}

struct ff_effect* FFBConditionEffect::createFFStruct()
{
  struct ff_effect* eff = FFBEffect::createFFStruct(m_params);

  eff->u.condition[0].center = m_params->center;
  eff->u.condition[0].deadband = m_params->deadband;
  eff->u.condition[0].left_coeff = m_params->leftCoeff;
  eff->u.condition[0].right_coeff = m_params->rightCoeff;
  eff->u.condition[0].left_saturation = m_params->leftSat;
  eff->u.condition[0].right_saturation = m_params->rightSat;

  switch (m_params->subtype) {
    case ConditionSubtypes::DAMPER:
      eff->type = FF_DAMPER;
      break;
    case ConditionSubtypes::FRICTION:
      eff->type = FF_FRICTION;
      break;
    case ConditionSubtypes::INERTIA:
      eff->type = FF_INERTIA;
      break;
    case ConditionSubtypes::SPRING:
      eff->type = FF_SPRING;
      break;
    default:
      qCritical("Unknown subtype");
      delete eff;
      return nullptr;
  }

  return eff;
}

bool FFBConditionEffect::setParameters(const std::shared_ptr<FFBEffectParameters> params)
{
  try {
    const std::shared_ptr<FFBConditionEffectParameters> cdParams = std::dynamic_pointer_cast<FFBConditionEffectParameters>(params);
    return setParameters(cdParams);
  } catch (std::bad_cast& ex) {
    qCritical(ex.what());
    return false;
  }
  return false;
}

bool FFBConditionEffect::setParameters(const std::shared_ptr<FFBConditionEffectParameters> params)
{
  if (!checkGenericParameters(params))
    return false;

  if (!checkBoundsInclusive(m_params->center, -0x7FFF, 0x7FFF)) {
    reportError("Center out of bounds,");
    return false;
  }

  if (!checkBoundsInclusive(params->deadband, 0, 0xFFFF)) {
    reportError("Deadband out of bounds.");
    return false;
  }

  if (!checkBoundsInclusive(params->leftCoeff, -0x7FFF, 0x7FFF)) {
    reportError("Left coefficient out of bounds.");
    return false;
  }

  if (!checkBoundsInclusive(params->rightCoeff, -0x7FFF, 0x7FFF)) {
    reportError("Right coefficient out of bounds.");
    return false;
  }

  if (!checkBoundsInclusive(params->leftSat, 0, 0xFFFF)) {
    reportError("Left saturation out of bounds.");
    return false;
  }

  if (!checkBoundsInclusive(params->rightSat, 0, 0xFFFF)) {
    reportError("Right saturation out of bounds.");
    return false;
  }

  if (params->subtype == ConditionSubtypes::NONE) {
    reportError("Invalid subtype");
    return false;
  }

  m_params = params;
  return true;
}
