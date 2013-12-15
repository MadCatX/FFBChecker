#include "ffbconditioneffect.h"
#include "globalsettings.h"

FFBConditionEffect::FFBConditionEffect() :
  FFBEffect(FFBEffectTypes::CONDITION)
{}

struct ff_effect* FFBConditionEffect::createFFStruct()
{
  struct ff_effect* eff = FFBEffect::createFFStruct(m_params);

  eff->u.condition[0].center = m_params->center[FFBConditionEffectParameters::Axis::X];
  eff->u.condition[0].deadband = m_params->deadband[FFBConditionEffectParameters::Axis::X];
  eff->u.condition[0].left_coeff = m_params->leftCoeff[FFBConditionEffectParameters::Axis::X];
  eff->u.condition[0].right_coeff = m_params->rightCoeff[FFBConditionEffectParameters::Axis::X];
  eff->u.condition[0].left_saturation = m_params->leftSat[FFBConditionEffectParameters::Axis::X];
  eff->u.condition[0].right_saturation = m_params->rightSat[FFBConditionEffectParameters::Axis::X];

  eff->u.condition[1].center = m_params->center[FFBConditionEffectParameters::Axis::Y];
  eff->u.condition[1].deadband = m_params->deadband[FFBConditionEffectParameters::Axis::Y];
  eff->u.condition[1].left_coeff = m_params->leftCoeff[FFBConditionEffectParameters::Axis::Y];
  eff->u.condition[1].right_coeff = m_params->rightCoeff[FFBConditionEffectParameters::Axis::Y];
  eff->u.condition[1].left_saturation = m_params->leftSat[FFBConditionEffectParameters::Axis::Y];
  eff->u.condition[1].right_saturation = m_params->rightSat[FFBConditionEffectParameters::Axis::Y];

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
    return setParameters(std::dynamic_pointer_cast<FFBConditionEffectParameters>(params));
  } catch (const std::bad_cast& ex) {
    qCritical(ex.what());
    return false;
  }
  return false;
}

bool FFBConditionEffect::setParameters(const std::shared_ptr<FFBConditionEffectParameters> params)
{
  if (!checkGenericParameters(params))
    return false;

  if (GlobalSettings::GS()->doSanityChecks) {
    if (!checkBoundsInclusive(params->center[FFBConditionEffectParameters::Axis::X], -0x7FFF, 0x7FFF)) {
      reportError("Center X out of bounds,");
      return false;
    }
    if (!checkBoundsInclusive(params->center[FFBConditionEffectParameters::Axis::Y], -0x7FFF, 0x7FFF)) {
      reportError("Center Y out of bounds,");
      return false;
    }

    if (!checkBoundsInclusive(params->deadband[FFBConditionEffectParameters::Axis::X], 0, 0xFFFF)) {
      reportError("Deadband X out of bounds.");
      return false;
    }
    if (!checkBoundsInclusive(params->deadband[FFBConditionEffectParameters::Axis::Y], 0, 0xFFFF)) {
      reportError("Deadband Y out of bounds.");
      return false;
    }

    if (!checkBoundsInclusive(params->leftCoeff[FFBConditionEffectParameters::Axis::X], -0x7FFF, 0x7FFF)) {
      reportError("Left coefficient X out of bounds.");
      return false;
    }
    if (!checkBoundsInclusive(params->leftCoeff[FFBConditionEffectParameters::Axis::Y], -0x7FFF, 0x7FFF)) {
      reportError("Left coefficient Y out of bounds.");
      return false;
    }

    if (!checkBoundsInclusive(params->rightCoeff[FFBConditionEffectParameters::Axis::X], -0x7FFF, 0x7FFF)) {
      reportError("Right coefficient X out of bounds.");
      return false;
    }
    if (!checkBoundsInclusive(params->rightCoeff[FFBConditionEffectParameters::Axis::Y], -0x7FFF, 0x7FFF)) {
      reportError("Right coefficient Y out of bounds.");
      return false;
    }

    if (!checkBoundsInclusive(params->leftSat[FFBConditionEffectParameters::Axis::X], 0, 0xFFFF)) {
      reportError("Left saturation X out of bounds.");
      return false;
    }
    if (!checkBoundsInclusive(params->leftSat[FFBConditionEffectParameters::Axis::Y], 0, 0xFFFF)) {
      reportError("Left saturation Y out of bounds.");
      return false;
    }

    if (!checkBoundsInclusive(params->rightSat[FFBConditionEffectParameters::Axis::X], 0, 0xFFFF)) {
      reportError("Right saturation X out of bounds.");
      return false;
    }
    if (!checkBoundsInclusive(params->rightSat[FFBConditionEffectParameters::Axis::Y], 0, 0xFFFF)) {
      reportError("Right saturation Y out of bounds.");
      return false;
    }

    if (params->subtype == ConditionSubtypes::NONE) {
      reportError("Invalid subtype");
      return false;
    }
  }

  m_params = params;
  return true;
}

bool FFBConditionEffect::operator==(const FFBEffect& other) const
{
  if (this->type() != other.type())
    return false;
  else {
    try {
      const FFBConditionEffect& cother = dynamic_cast<const FFBConditionEffect&>(other);
      return this->m_params->subtype == cother.m_params->subtype;
    } catch (std::bad_cast&) {
      return false;
    }
  }
}
