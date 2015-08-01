#ifndef LINUXFFBEFFECT_H
#define LINUXFFBEFFECT_H

#include "ffbeffect.h"
#include <linux/input.h>

class LinuxFFBEffect : public FFBEffect {
public:
  explicit LinuxFFBEffect(FFBEffectTypes type);
  virtual struct ff_effect* createFFStruct() = 0;
  inline int internalIdx() const { return m_internalIdx; }
  inline void setInternalIdx(int idx) { m_internalIdx = idx; }

protected:
  struct ff_effect* createFFStruct(const std::shared_ptr<FFBEffectParameters> params);
  bool checkEnvelopeParameters(const int attackLength, const int attackLevel, const int fadeLength, const int fadeLevel);
  bool checkGenericParameters(const std::shared_ptr<FFBEffectParameters> params);

private:

  int m_internalIdx;

};

#endif // LINUXFFBEFFECT_H
