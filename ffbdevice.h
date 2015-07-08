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

  explicit FFBDevice(const int fd, const QString& path, const int maxEffectCount, QObject* parent = 0);
  const std::vector<ConditionSubtypes>& availableConditionSubtypesList() const;
  const std::vector<FFBEffectTypes>& availableEffectsList() const;
  const std::vector<PeriodicWaveforms>& availableWaveformsList() const;
  const std::shared_ptr<FFBEffectParameters> effectParameters(const int idx);
  FFBEffect::FFBEffectStatus effectStatusByIdx(const int idx) const;
  FFBEffectTypes effectTypeByEffectIdx(const int idx) const;
  bool hasEffect(FFBEffectTypes id) const;
  bool hasPeriodicWaveform(PeriodicWaveforms id) const;
  inline int maxEffectCount() const { return c_maxEffectCount; }
  inline const QString& path() const { return c_path; }
  bool queryDeviceCapabilities();
  bool removeAndEraseEffect(const int idx);
  bool startEffect(const int idx, const FFBEffectTypes type, std::shared_ptr<FFBEffectParameters> parameters);
  bool stopEffect(const int idx);
  bool uploadEffect(const int idx, const FFBEffectTypes type, std::shared_ptr<FFBEffectParameters> parameters);
  inline PeriodicWaveforms waveformByIdx(const int idx) const { return m_availablePeriodicWaveforms[idx]; }

private:
  bool removeEffect(const int idx);
  std::vector<ConditionSubtypes> m_availableConditionSubtypes;
  std::vector<FFBEffectTypes> m_availableEffects;
  std::vector<PeriodicWaveforms> m_availablePeriodicWaveforms;
  std::vector<std::shared_ptr<FFBEffect>> m_effects;

  const int c_fd;
  const int c_maxEffectCount;
  const QString c_path;

  static inline unsigned long longIdx(unsigned long bit) { return bit / BITS_PER_LONG; }
  static inline unsigned long offset(unsigned long bit) { return bit % BITS_PER_LONG; }
  static inline bool testBit(unsigned long bit, unsigned long* array) { return (array[longIdx(bit)] >> offset(bit)) & 1; }

  static const quint8 BITS_PER_LONG;
signals:

public slots:

};

#endif // FFBDEVICE_H
