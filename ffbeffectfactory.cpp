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
    default:
      return nullptr;
  }
}
