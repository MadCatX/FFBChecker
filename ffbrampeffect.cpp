#include "ffbrampeffect.h"

FFBRampEffect::FFBRampEffect() :
  FFBEffect(FFBEffectTypes::RAMP)
{
}

struct ff_effect* FFBRampEffect::createFFStruct()
{
  struct ff_effect* eff = FFBEffect::createFFStruct(m_params);
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


bool FFBRampEffect::setParameters(const std::shared_ptr<FFBEffectParameters> params)
{
  try {
    return setParameters(std::dynamic_pointer_cast<FFBRampEffectParameters>(params));
  } catch (const std::bad_cast& ex) {
    reportError("Invalid effect parameters object " + QString(ex.what()));
    return false;
  }
}

bool FFBRampEffect::setParameters(const std::shared_ptr<FFBRampEffectParameters> params)
{
  if (!checkGenericParameters(params))
    return false;

 if (!checkBoundsInclusive(params->attackLength, 0, 0xFFFF)) {
    reportError("Attack length out of bounds.");
    return false;
  }

  if (!checkBoundsInclusive(params->attackLevel, 0, 0xFFFF)) {
    reportError("Attack level out of bounds.");
    return false;
  }

  if (!checkBoundsInclusive(params->fadeLength, 0, 0xFFFF)) {
    reportError("Fade length out of bounds.");
    return false;
  }

  if (!checkBoundsInclusive(params->endLevel, -0x7FFF, 0x7FFF)) {
    reportError("End level out of bounds");
    return false;
  }

  if (!checkBoundsInclusive(params->startLevel, -0x7FFF, 0x7FFF)) {
      reportError("Start level out of bounds");
      return false;
  }

  m_params = params;
  return true;
}

FFBRampEffect::~FFBRampEffect()
{
}
