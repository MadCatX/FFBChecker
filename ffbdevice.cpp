#include "ffbdevice.h"

const std::vector<ConditionSubtypes>& FFBDevice::availableConditionSubtypesList() const
{
  return m_availableConditionSubtypes;
}

const std::vector<FFBEffectTypes>& FFBDevice::availableEffectsList() const
{
  return m_availableEffects;
}

const std::vector<PeriodicWaveforms>& FFBDevice::availableWaveformsList() const
{
  return m_availablePeriodicWaveforms;
}

const std::shared_ptr<FFBEffectParameters> FFBDevice::effectParameters(const int idx)
{
  if (idx >= c_maxEffectCount || idx < 0)
    return nullptr;

  if (m_effects[idx] == nullptr)
    return nullptr;

  return m_effects[idx]->parameters();
}

FFBEffect::FFBEffectStatus FFBDevice::effectStatusByIdx(const int idx) const
{
  if (idx >= c_maxEffectCount || idx < 0)
    return FFBEffect::FFBEffectStatus::NOT_LOADED;

  if (m_effects[idx] == nullptr)
    return FFBEffect::FFBEffectStatus::NOT_LOADED;

  return m_effects[idx]->status();
}

FFBEffectTypes FFBDevice::effectTypeByEffectIdx(const int idx) const
{
  if (idx >= c_maxEffectCount || idx < 0)
    return FFBEffectTypes::NONE;

  if (m_effects[idx] == nullptr)
    return FFBEffectTypes::NONE;

  return m_effects[idx]->type();
}

bool FFBDevice::hasEffect(FFBEffectTypes id) const
{
  for (const FFBEffectTypes e : m_availableEffects)
    if (e == id) return true;

  return false;
}

bool FFBDevice::hasPeriodicWaveform(PeriodicWaveforms id) const
{
  for (const PeriodicWaveforms w : m_availablePeriodicWaveforms)
    if (w == id) return true;

  return false;
}
