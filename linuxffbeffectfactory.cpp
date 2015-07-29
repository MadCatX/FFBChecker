#include "linuxffbeffectfactory.h"

std::shared_ptr<FFBEffect> LinuxFFBEffectFactory::createEffect(FFBEffectTypes type)
{
  switch (type) {
    case FFBEffectTypes::NONE:
      return std::shared_ptr<FFBEffect>(new FFBNullEffect());
    case FFBEffectTypes::CONSTANT:
      return std::shared_ptr<LinuxFFBEffect>(new LinuxFFBConstantEffect());
    case FFBEffectTypes::PERIODIC:
      return std::shared_ptr<LinuxFFBEffect>(new LinuxFFBPeriodicEffect());
    case FFBEffectTypes::CONDITION:
      return std::shared_ptr<LinuxFFBEffect>(new LinuxFFBConditionEffect());
    case FFBEffectTypes::RAMP:
      return std::shared_ptr<LinuxFFBEffect>(new LinuxFFBRampEffect());
    case FFBEffectTypes::RUMBLE:
      return std::shared_ptr<LinuxFFBEffect>(new LinuxFFBRumbleEffect());
    default:
      return nullptr;
  }
}
