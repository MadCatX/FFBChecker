#ifndef LINUXFFBDEVICE_H
#define LINUXFFBDEVICE_H

#include "ffbdevice.h"

class LinuxFFBDevice : public FFBDevice
{
public:

  explicit LinuxFFBDevice(const int fd, const int maxEffectCount, const QString path);
  const QString& path() const { return c_path; }

  /* Overriden virtual functions */
  void close();
  bool queryDeviceCapabilities();
  bool removeAndEraseEffect(const int idx);
  bool setAutocentering(const int strength);
  bool setGain(const int gain);
  bool startEffect(const int idx, const FFBEffectTypes type, std::shared_ptr<FFBEffectParameters> parameters);
  bool stopEffect(const int idx);
  bool uploadEffect(const int idx, const FFBEffectTypes type, std::shared_ptr<FFBEffectParameters> parameters);
  inline PeriodicWaveforms waveformByIdx(const int idx) const { return m_availablePeriodicWaveforms[idx]; }

private:
  bool removeEffect(const int idx);

  const int c_fd;
  const QString c_path;

  static inline unsigned long longIdx(unsigned long bit) { return bit / BITS_PER_LONG; }
  static inline unsigned long offset(unsigned long bit) { return bit % BITS_PER_LONG; }
  static inline bool testBit(unsigned long bit, unsigned long* array) { return (array[longIdx(bit)] >> offset(bit)) & 1; }

  static const quint8 BITS_PER_LONG;
  static const QString LNXDEV_ERR_CAPTION;

signals:

public slots:

};

#endif // LINUXFFBDEVICE_H
