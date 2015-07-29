#include "linuxffbrumbleeffect.h"

LinuxFFBRumbleEffect::LinuxFFBRumbleEffect() :
  LinuxFFBEffect(FFBEffectTypes::RUMBLE)
{
}

struct ff_effect* LinuxFFBRumbleEffect::createFFStruct()
{
  struct ff_effect* eff = LinuxFFBEffect::createFFStruct(m_params);

  eff->type = FF_RUMBLE;

  eff->u.rumble.strong_magnitude = m_params->strongMagnitude;
  eff->u.rumble.weak_magnitude = m_params->weakMagnitude;

  return eff;
}

bool LinuxFFBRumbleEffect::setParameters(const std::shared_ptr<FFBEffectParameters> params)
{
  try {
    return setParameters(std::dynamic_pointer_cast<FFBRumbleEffectParameters>(params));
  } catch (std::bad_cast& ex) {
    reportError("Invalid effect parameters object " + QString(ex.what()));
    return false;
  }
}

bool LinuxFFBRumbleEffect::setParameters(const std::shared_ptr<FFBRumbleEffectParameters> params)
{
  if (!checkGenericParameters(params))
    return false;

  if (!checkBoundsInclusive(params->strongMagnitude, 0, 0xFFFF)) {
    reportError("Strong magnitude out of bounds");
    return false;
  }

  if (!checkBoundsInclusive(params->weakMagnitude, 0, 0xFFFF)) {
    reportError("Weak magnitude out of bounds");
    return false;
  }

  m_params = params;
  return true;
}
