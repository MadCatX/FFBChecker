#include "linuxffbconstanteffect.h"
#include "globalsettings.h"

LinuxFFBConstantEffect::LinuxFFBConstantEffect() :
  LinuxFFBEffect(FFBEffectTypes::CONSTANT)
{}

struct ff_effect* LinuxFFBConstantEffect::createFFStruct()
{
  /* Set up generic effect parameters */
  struct ff_effect* eff = LinuxFFBEffect::createFFStruct(m_params);

  eff->type = FF_CONSTANT;

  eff->u.constant.envelope.attack_length = m_params->attackLength;
  eff->u.constant.envelope.attack_level = m_params->attackLevel;
  eff->u.constant.envelope.fade_length = m_params->fadeLength;
  eff->u.constant.envelope.fade_level= m_params->fadeLevel;

  eff->u.constant.level = m_params->level;

  return eff;
}

bool LinuxFFBConstantEffect::setParameters(const std::shared_ptr<FFBEffectParameters> params)
{
  try {
    return setParameters(std::dynamic_pointer_cast<FFBConstantEffectParameters>(params));
  } catch (const std::bad_cast&) {
      return false;
  }
  return false;
}

bool LinuxFFBConstantEffect::setParameters(const std::shared_ptr<FFBConstantEffectParameters> params)
{
  if (!GlobalSettings::GS()->doSanityChecks)
    return true;

  if (!checkGenericParameters(params))
    return false;

  if (!checkEnvelopeParameters(params->attackLength, params->attackLevel, params->fadeLength, params->fadeLevel))
    return false;

  if (!checkBoundsInclusive(params->level, -0x7FFF, 0x7FFF)) {
    reportError("Level out of bounds.");
    return false;
  }

  m_params = params;
  return true;
}
