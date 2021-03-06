#include "linuxffbperiodiceffect.h"
#include "globalsettings.h"
#include <QDebug>

LinuxFFBPeriodicEffect::LinuxFFBPeriodicEffect() :
  LinuxFFBEffect(FFBEffectTypes::PERIODIC)
{}

struct ff_effect* LinuxFFBPeriodicEffect::createFFStruct()
{
  struct ff_effect* eff = LinuxFFBEffect::createFFStruct(m_params);
  if (eff == nullptr)
    return nullptr;

  eff->type = FF_PERIODIC;

  eff->u.periodic.envelope.attack_length = m_params->attackLength;
  eff->u.periodic.envelope.attack_level = m_params->attackLevel;
  eff->u.periodic.envelope.fade_length = m_params->fadeLength;
  eff->u.periodic.envelope.fade_level = m_params->fadeLevel;

  eff->u.periodic.magnitude = m_params->magnitude;
  eff->u.periodic.offset = m_params->offset;
  eff->u.periodic.period = m_params->period;
  eff->u.periodic.phase = m_params->phase;

  switch (m_params->waveform) {
    case PeriodicWaveforms::SINE:
      eff->u.periodic.waveform= FF_SINE;
      break;
    case PeriodicWaveforms::SQUARE:
      eff->u.periodic.waveform = FF_SQUARE;
      break;
    case PeriodicWaveforms::SAW_DOWN:
      eff->u.periodic.waveform = FF_SAW_DOWN;
      break;
    case PeriodicWaveforms::SAW_UP:
      eff->u.periodic.waveform = FF_SAW_UP;
      break;
    case PeriodicWaveforms::TRIANGLE:
      eff->u.periodic.waveform = FF_TRIANGLE;
      break;
    case PeriodicWaveforms::NONE:
      delete eff;
      return nullptr;
  }

  return eff;
}

bool LinuxFFBPeriodicEffect::setParameters(const std::shared_ptr<FFBEffectParameters> params)
{
  try {
    return setParameters(std::dynamic_pointer_cast<FFBPeriodicEffectParameters>(params));
  } catch (const std::bad_cast& ex) {
    reportError("Invalid effect parameters object " + QString(ex.what()));
    return false;
  }
}

bool LinuxFFBPeriodicEffect::setParameters(const std::shared_ptr<FFBPeriodicEffectParameters> params)
{
  if (!GlobalSettings::GS()->doSanityChecks)
    return true;

  if (!checkGenericParameters(params))
    return false;

  if (!checkEnvelopeParameters(params->attackLength, params->attackLevel, params->fadeLength, params->fadeLevel))
    return false;

  if (!checkBoundsInclusive(params->magnitude, -0x7FFF, 0x7FFF)) {
    reportError("Magnitude must be within <-32767; 32767>");
    return false;
  }

  if (!checkBoundsInclusive(params->offset, -0x7FFF, 0x7FFF)) {
    reportError("Offset must be within <32767; 32767>");
    return false;
  }

  if (!checkBoundsInclusive(params->period, 0, 0x7FFF)) {
    reportError("Period must be within <0; 32767>");
    return false;
  }

  if (!checkBoundsInclusive(params->phase, 0, 0x7FFF)) {
    reportError("Phase must be within <0; 32767>");
    return false;
  }

  if (params->waveform == PeriodicWaveforms::NONE) {
    reportError("Invalid waveform type.");
    return false;
  }

  m_params = params;
  return true;
}

bool LinuxFFBPeriodicEffect::operator==(const FFBEffect& other) const
{
  if (this->type() != other.type())
    return false;
  else {
    try {
      const LinuxFFBPeriodicEffect& eff = dynamic_cast<const LinuxFFBPeriodicEffect&>(other);
      return this->m_params->waveform == eff.m_params->waveform;
    } catch(std::bad_cast&) {
      return false;
    }
  }
}

