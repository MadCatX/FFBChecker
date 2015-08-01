#include "linuxffbrampeffect.h"
#include "globalsettings.h"

LinuxFFBRampEffect::LinuxFFBRampEffect() :
  LinuxFFBEffect(FFBEffectTypes::RAMP)
{
}

struct ff_effect* LinuxFFBRampEffect::createFFStruct()
{
  struct ff_effect* eff = LinuxFFBEffect::createFFStruct(m_params);
  if (eff == nullptr)
    return nullptr;

  eff->type = FF_RAMP;

  eff->u.ramp.envelope.attack_length = m_params->attackLength;
  eff->u.ramp.envelope.attack_level = m_params->attackLevel;
  eff->u.ramp.envelope.fade_length = m_params->fadeLength;
  eff->u.ramp.envelope.fade_level = m_params->fadeLevel;

  eff->u.ramp.end_level = m_params->endLevel;
  eff->u.ramp.start_level = m_params->startLevel;

  return eff;
}


bool LinuxFFBRampEffect::setParameters(const std::shared_ptr<FFBEffectParameters> params)
{
  try {
    return setParameters(std::dynamic_pointer_cast<FFBRampEffectParameters>(params));
  } catch (const std::bad_cast& ex) {
    reportError("Invalid effect parameters object " + QString(ex.what()));
    return false;
  }
}

bool LinuxFFBRampEffect::setParameters(const std::shared_ptr<FFBRampEffectParameters> params)
{
  if (!GlobalSettings::GS()->doSanityChecks)
    return true;

  if (!checkGenericParameters(params))
    return false;

  if (!checkEnvelopeParameters(params->attackLength, params->attackLevel, params->fadeLength, params->fadeLevel))
    return false;

  if (!checkBoundsInclusive(params->endLevel, -0x7FFF, 0x7FFF)) {
    reportError("End level must be within <-32767; 32767>");
    return false;
  }

  if (!checkBoundsInclusive(params->startLevel, -0x7FFF, 0x7FFF)) {
    reportError("Start level must be within <-32767; 32767>");
    return false;
  }

  m_params = params;
  return true;
}
