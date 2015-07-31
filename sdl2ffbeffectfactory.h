#ifndef SDL2FFBEFFECTFACTORY_H
#define SDL2FFBEFFECTFACTORY_H

#include "globals.h"
#include "ffbnulleffect.h"

class SDL2FFBEffectFactory
{
public:
  static std::shared_ptr<FFBEffect> createEffect(FFBEffectTypes type);

  SDL2FFBEffectFactory() = delete;
};

#endif // LINUXFFBEFFECTFACTORY_H
