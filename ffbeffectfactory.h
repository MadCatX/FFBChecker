#ifndef FFBEFFECTFACTORY_H
#define FFBEFFECTFACTORY_H

#include "globals.h"
#include "ffbconstanteffect.h"
#include "ffbnulleffect.h"
#include "ffbperiodiceffect.h"

class FFBEffectFactory
{
public:
  static std::shared_ptr<FFBEffect> createEffect(FFBEffectTypes type);

private:
  FFBEffectFactory();

};

#endif // FFBEFFECTFACTORY_H
