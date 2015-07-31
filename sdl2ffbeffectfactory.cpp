#include "sdl2ffbeffectfactory.h"

std::shared_ptr<FFBEffect> SDL2FFBEffectFactory::createEffect(FFBEffectTypes type)
{
  switch (type) {
    case FFBEffectTypes::NONE:
      return std::shared_ptr<FFBEffect>(new FFBNullEffect());
    default:
      return std::shared_ptr<FFBEffect>(new FFBNullEffect());
  }
}