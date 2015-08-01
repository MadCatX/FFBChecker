#ifndef SDL2FFBEFFECTFACTORY_H
#define SDL2FFBEFFECTFACTORY_H

#include "globals.h"
#include "ffbnulleffect.h"
#include "sdl2ffbconstanteffect.h"
#include "sdl2ffbconditioneffect.h"
#include "sdl2ffbperiodiceffect.h"
#include "sdl2ffbrampeffect.h"

class SDL2FFBEffectFactory
{
public:
  static std::shared_ptr<FFBEffect> createEffect(FFBEffectTypes type);

  SDL2FFBEffectFactory() = delete;
};

#endif // LINUXFFBEFFECTFACTORY_H
