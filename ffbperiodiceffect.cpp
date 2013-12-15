#include "ffbperiodiceffect.h"
#include "globalsettings.h"
#include <QDebug>

FFBPeriodicEffect::FFBPeriodicEffect() :
  FFBEffect(FFBEffectTypes::PERIODIC)
{}

struct ff_effect* FFBPeriodicEffect::createFFStruct()
{
  struct ff_effect* eff = FFBEffect::createFFStruct(m_params);
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

bool FFBPeriodicEffect::setParameters(const std::shared_ptr<FFBEffectParameters> params)
{
  try {
    return setParameters(std::dynamic_pointer_cast<FFBPeriodicEffectParameters>(params));
  } catch (const std::bad_cast& ex) {
    reportError("Invalid effect parameters object " + QString(ex.what()));
    return false;
  }
}

bool FFBPeriodicEffect::setParameters(const std::shared_ptr<FFBPeriodicEffectParameters> params)
{
  if (!checkGenericParameters(params))
    return false;

  if (GlobalSettings::GS()->doSanityChecks) {
    if (!checkBoundsInclusive(params->attackLength, 0, 0x7FFF)) {
      reportError("Attack length out of bounds.");
      return false;
    }

    if (!checkBoundsInclusive(params->attackLevel, 0, 0x7FFF)) {
      reportError("Attack level out of bounds.");
      return false;
    }

    if (!checkBoundsInclusive(params->fadeLength, 0, 0x7FFF)) {
      reportError("Fade length out of bounds.");
      return false;
    }

    if (!checkBoundsInclusive(params->fadeLevel, 0, 0x7FFF)) {
      reportError("Fade level out of bounds.");
      return false;
    }

    if (!checkBoundsInclusive(params->magnitude, -0x7FFF, 0x7FFF)) {
      reportError("Magnitude out of bounds.");
      return false;
    }

    if (!checkBoundsInclusive(params->offset, -0x7FFF, 0x7FFF)) {
      reportError("Offset out of bounds.");
      return false;
    }

    if (!checkBoundsInclusive(params->period, 0, 0x7FFF)) {
      reportError("Period out of bounds.");
      return false;
    }

    if (!checkBoundsInclusive(params->phase, 0, 0x7FFF)) {
      reportError("Phase out of bounds.");
      return false;
    }

    if (params->waveform == PeriodicWaveforms::NONE) {
      reportError("Invalid waveform type.");
      return false;
    }
  }

  m_params = params;
  return true;
}

bool FFBPeriodicEffect::operator==(const FFBEffect& other) const
{
  if (this->type() != other.type())
    return false;
  else {
    try {
      const FFBPeriodicEffect& eff = dynamic_cast<const FFBPeriodicEffect&>(other);
      return this->m_params->waveform == eff.m_params->waveform;
    } catch(std::bad_cast&) {
      return false;
    }
  }
}

FFBPeriodicEffect::~FFBPeriodicEffect()
{
}
