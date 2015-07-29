#ifndef LinuxFFBEFFECTFACTORY_H
#define FFBEFFECTFACTORY_H

#include "globals.h"
#include "linuxffbconditioneffect.h"
#include "linuxffbconstanteffect.h"
#include "ffbnulleffect.h"
#include "linuxffbperiodiceffect.h"
#include "linuxffbrampeffect.h"
#include "linuxffbrumbleeffect.h"

class LinuxFFBEffectFactory
{
public:
  static std::shared_ptr<FFBEffect> createEffect(FFBEffectTypes type);

private:
  LinuxFFBEffectFactory() {};

};

#endif // FFBEFFECTFACTORY_H
