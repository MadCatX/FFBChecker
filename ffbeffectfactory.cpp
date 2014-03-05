#include "ffbeffectfactory.h"

FFBEffectFactory::FFBEffectFactory()
{
}

std::shared_ptr<FFBEffect> FFBEffectFactory::createEffect(FFBEffectTypes type)
{
  switch (type) {
    case FFBEffectTypes::NONE:
      return std::shared_ptr<FFBEffect>(new FFBNullEffect());
    case FFBEffectTypes::CONSTANT:
      return std::shared_ptr<FFBEffect>(new FFBConstantEffect());
    case FFBEffectTypes::PERIODIC:
      return std::shared_ptr<FFBEffect>(new FFBPeriodicEffect());
    case FFBEffectTypes::CONDITION:
      return std::shared_ptr<FFBEffect>(new FFBConditionEffect());
    case FFBEffectTypes::RAMP:
      return std::shared_ptr<FFBEffect>(new FFBRampEffect());
    case FFBEffectTypes::RUMBLE:
      return std::shared_ptr<FFBEffect>(new FFBRumbleEffect());
    default:
      return nullptr;
  }
}
