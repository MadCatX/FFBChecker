#include "sdl2ffbconditioneffect.h"
#include "globalsettings.h"
#include <QtWidgets/QMessageBox>

SDL2FFBConditionEffect::SDL2FFBConditionEffect() :
  SDL2FFBEffect(FFBEffectTypes::CONDITION)
{}

SDL_HapticEffect* SDL2FFBConditionEffect::createFFstruct()
{
  SDL_HapticEffect* effect = SDL2FFBEffect::createFFstruct();
  if (effect == nullptr)
    return nullptr;

  switch (m_params->subtype) {
    case ConditionSubtypes::DAMPER:
      effect->type = SDL_HAPTIC_DAMPER;
      break;
    case ConditionSubtypes::FRICTION:
      effect->type = SDL_HAPTIC_FRICTION;
      break;
    case ConditionSubtypes::INERTIA:
      effect->type = SDL_HAPTIC_INERTIA;
      break;
    case ConditionSubtypes::SPRING:
      effect->type = SDL_HAPTIC_SPRING;
      break;
    default:
      delete effect;
      return nullptr;
  }

  effect->condition.delay = m_params->replayDelay;
  if (m_params->replayLength == 0)
    effect->condition.length = SDL_HAPTIC_INFINITY;
  else
    effect->condition.length = m_params->replayLength;

  effect->condition.center[0] = m_params->center.at(FFBConditionEffectParameters::Axis::X);
  effect->condition.deadband[0] = m_params->deadband.at(FFBConditionEffectParameters::Axis::X);
  effect->condition.center[1] = m_params->center.at(FFBConditionEffectParameters::Axis::Y);
  effect->condition.deadband[1] = m_params->deadband.at(FFBConditionEffectParameters::Axis::Y);

  effect->condition.left_sat[0] = m_params->leftSat.at(FFBConditionEffectParameters::Axis::X);
  effect->condition.right_sat[0] = m_params->rightSat.at(FFBConditionEffectParameters::Axis::X);
  effect->condition.left_coeff[0] = m_params->leftCoeff.at(FFBConditionEffectParameters::Axis::X);;
  effect->condition.right_coeff[0] = m_params->rightCoeff.at(FFBConditionEffectParameters::Axis::X);;

  effect->condition.left_sat[1] = m_params->leftSat.at(FFBConditionEffectParameters::Axis::Y);
  effect->condition.right_sat[1] = m_params->rightSat.at(FFBConditionEffectParameters::Axis::Y);
  effect->condition.left_coeff[1] = m_params->leftCoeff.at(FFBConditionEffectParameters::Axis::Y);;
  effect->condition.right_coeff[1] = m_params->rightCoeff.at(FFBConditionEffectParameters::Axis::Y);;

  return effect;
}

bool SDL2FFBConditionEffect::setParameters(std::shared_ptr<FFBEffectParameters> params)
{
  try {
    const std::shared_ptr<FFBConditionEffectParameters> iParams = std::dynamic_pointer_cast<FFBConditionEffectParameters>(params);
    return setParameters(iParams);
  } catch (std::bad_cast& ) {
    return false;
  }
}

bool SDL2FFBConditionEffect::setParameters(std::shared_ptr<FFBConditionEffectParameters> params)
{
  if (!GlobalSettings::GS()->doSanityChecks)
    return true;

  if (!checkGenericParameters(params))
    return false;

  if (!checkBoundsInclusive(params->leftSat.at(FFBConditionEffectParameters::Axis::X), 0, 0xFFFF)) {
    QMessageBox::warning(nullptr, CAPTION, "Left X saturation must be within <0; 65535>");
    return false;
  }

  if (!checkBoundsInclusive(params->leftSat.at(FFBConditionEffectParameters::Axis::Y), 0, 0xFFFF)) {
    QMessageBox::warning(nullptr, CAPTION, "Left Y saturation must be within <0; 65535>");
    return false;
  }

  if (!checkBoundsInclusive(params->rightSat.at(FFBConditionEffectParameters::Axis::X), 0, 0xFFFF)) {
    QMessageBox::warning(nullptr, CAPTION, "Right X saturation must be within <0; 65535>");
    return false;
  }

  if (!checkBoundsInclusive(params->rightSat.at(FFBConditionEffectParameters::Axis::Y), 0, 0xFFFF)) {
    QMessageBox::warning(nullptr, CAPTION, "Right Y saturation must be within <0; 65535>");
    return false;
  }

  if (!checkBoundsInclusive(params->leftCoeff.at(FFBConditionEffectParameters::Axis::X), -0x7FFF, 0x7FFF)) {
    QMessageBox::warning(nullptr, CAPTION, "Left X coefficient must be within <-32767; 32767>");
    return false;
  }

  if (!checkBoundsInclusive(params->leftCoeff.at(FFBConditionEffectParameters::Axis::Y), -0x7FFF, 0x7FFF)) {
    QMessageBox::warning(nullptr, CAPTION, "Left Y coefficient must be within <-32767; 32767>");
    return false;
  }

  if (!checkBoundsInclusive(params->rightCoeff.at(FFBConditionEffectParameters::Axis::X), -0x7FFF, 0x7FFF)) {
    QMessageBox::warning(nullptr, CAPTION, "Right X coefficient must be within <-32767; 32767>");
    return false;
  }

  if (!checkBoundsInclusive(params->rightCoeff.at(FFBConditionEffectParameters::Axis::Y), -0x7FFF, 0x7FFF)) {
    QMessageBox::warning(nullptr, CAPTION, "Right Y coefficient must be within <-32767; 32767>");
    return false;
  }

  if (!checkBoundsInclusive(params->deadband.at(FFBConditionEffectParameters::Axis::X), 0, 0xFFFF)) {
    QMessageBox::warning(nullptr, CAPTION, "Deadband X must be within <0; 65535>");
    return false;
  }

  if (!checkBoundsInclusive(params->deadband.at(FFBConditionEffectParameters::Axis::Y), 0, 0xFFFF)) {
    QMessageBox::warning(nullptr, CAPTION, "Deadband Y must be within <0; 65535>");
    return false;
  }

  if (!checkBoundsInclusive(params->center.at(FFBConditionEffectParameters::Axis::X), -0x7FFF, 0x7FFF)) {
    QMessageBox::warning(nullptr, CAPTION, "Center X must be within <-32767; 32767>");
    return false;
  }

  if (!checkBoundsInclusive(params->center.at(FFBConditionEffectParameters::Axis::Y), -0x7FFF, 0x7FFF)) {
    QMessageBox::warning(nullptr, CAPTION, "Center Y must be within <-32767; 32767>");
    return false;
  }

  m_params = params;
  return true;
}


