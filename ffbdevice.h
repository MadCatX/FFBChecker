#ifndef FFBDEVICE_H
#define FFBDEVICE_H

#include "ffbeffect.h"
#include <memory>
#include <vector>

class FFBDevice {
public:
  virtual ~FFBDevice() = default;

  const std::vector<ConditionSubtypes>& availableConditionSubtypesList() const;
  const std::vector<FFBEffectTypes>& availableEffectsList() const;
  const std::vector<PeriodicWaveforms>& availableWaveformsList() const;
  const std::shared_ptr<FFBEffectParameters> effectParameters(const int idx);
  FFBEffect::FFBEffectStatus effectStatusByIdx(const int idx) const;
  FFBEffectTypes effectTypeByEffectIdx(const int idx) const;
  bool hasEffect(FFBEffectTypes id) const;
  bool hasPeriodicWaveform(PeriodicWaveforms id) const;
  inline int maxEffectCount() const { return c_maxEffectCount; }
  inline PeriodicWaveforms waveformByIdx(const int idx) const { return m_availablePeriodicWaveforms[idx]; }

  virtual void close() = 0;
  virtual bool queryDeviceCapabilities() = 0;
  virtual bool removeAndEraseEffect(const int idx) = 0;
  virtual bool setAutocentering(const int strength) = 0;
  virtual bool setGain(const int gain) = 0;
  virtual bool startEffect(const int idx, const FFBEffectTypes type, std::shared_ptr<FFBEffectParameters> parameters) = 0;
  virtual bool stopEffect(const int idx) = 0;
  virtual bool uploadEffect(const int idx, const FFBEffectTypes type, std::shared_ptr<FFBEffectParameters> parameters) = 0;

protected:
  explicit FFBDevice(const int maxEffectCount) :
    c_maxEffectCount(maxEffectCount) {}

  std::vector<ConditionSubtypes> m_availableConditionSubtypes;
  std::vector<FFBEffectTypes> m_availableEffects;
  std::vector<PeriodicWaveforms> m_availablePeriodicWaveforms;
  bool m_adjustableAC;
  bool m_adjustableGain;

  std::vector<std::shared_ptr<FFBEffect>> m_effects;

  const int c_maxEffectCount;

};

#endif // FFBDEVICE_H
