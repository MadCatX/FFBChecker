#include "sdl2ffbeffectfactory.h"

std::shared_ptr<FFBEffect> SDL2FFBEffectFactory::createEffect(FFBEffectTypes type)
{
  switch (type) {
    case FFBEffectTypes::NONE:
      return std::shared_ptr<FFBEffect>(new FFBNullEffect());
    case FFBEffectTypes::CONDITION:
      return std::shared_ptr<SDL2FFBEffect>(new SDL2FFBConditionEffect());
    case FFBEffectTypes::CONSTANT:
      return std::shared_ptr<SDL2FFBEffect>(new SDL2FFBConstantEffect());
    default:
      return std::shared_ptr<FFBEffect>(new FFBNullEffect());
  }
}