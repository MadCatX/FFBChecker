#ifndef FFBDEVICE_H
#define FFBDEVICE_H

#include "ffbeffect.h"
#include <memory>
#include <vector>
#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/stat.h>

class FFBDevice : public QObject
{
  Q_OBJECT
public:

  explicit FFBDevice(const int fd, const QString& id, const int maxEffectCount, QObject* parent = 0);
  QStringList availableConditionSubtypesList() const;
  QStringList availableEffectsList() const;
  QStringList availableWaveformsList() const;
  inline ConditionSubtypes conditionSubtypeByIdx(const int idx) { return m_availableConditionSubtypes[idx]; }
  QString conditionSubtypeName(const ConditionSubtypes subtype) const;
  QString effectName(const FFBEffectTypes effect) const;
  const std::shared_ptr<FFBEffectParameters> effectParameters(const int idx);
  FFBEffect::FFBEffectStatus effectStatusByIdx(const int idx) const;
  inline FFBEffectTypes effectTypeFromSelectionIdx(const int idx) const { return m_availableEffects[idx]; }
  unsigned int effectTypeToIdx(FFBEffectTypes type);
  FFBEffectTypes effectTypeByEffectIdx(const int idx) const;
  bool hasEffect(FFBEffectTypes id) const;
  bool hasPeriodicWaveform(PeriodicWaveforms id) const;
  inline const QString& id() const { return c_id; }
  inline int maxEffectCount() const { return c_maxEffectCount; }
  bool queryDeviceCapabilities();
  bool removeAndEraseEffect(const int idx);
  bool startEffect(const int idx, FFBEffectTypes type, std::shared_ptr<FFBEffectParameters> params);
  bool stopEffect(const int idx);
  QString waveformName(const PeriodicWaveforms waveform) const;
  inline PeriodicWaveforms waveformByIdx(const int idx) const { return m_availablePeriodicWaveforms[idx]; }

private:
  bool removeEffect(const int idx);
  int uploadEffect(struct ff_effect* effect);
  std::vector<ConditionSubtypes> m_availableConditionSubtypes;
  std::vector<FFBEffectTypes> m_availableEffects;
  std::vector<PeriodicWaveforms> m_availablePeriodicWaveforms;
  std::vector<std::shared_ptr<FFBEffect>> m_effects;

  const int c_fd;
  const QString c_id;
  const int c_maxEffectCount;

  static inline unsigned long longIdx(unsigned long bit) { return bit / BITS_PER_LONG; }
  static inline unsigned long offset(unsigned long bit) { return bit % BITS_PER_LONG; }
  static inline bool testBit(unsigned long bit, unsigned long* array) { return (array[longIdx(bit)] >> offset(bit)) & 1; }

  static const quint8 BITS_PER_LONG;
signals:

public slots:

};

#endif // FFBDEVICE_H
