#ifndef LINUXFFBPERIODICEFFECT_H
#define LINUXFFBPERIODICEFFECT_H

#include "linuxffbeffect.h"
#include "ffbperiodiceffectparameters.h"

class LinuxFFBPeriodicEffect : public LinuxFFBEffect
{
public:
  LinuxFFBPeriodicEffect();
  struct ff_effect* createFFStruct();
  inline const std::shared_ptr<FFBEffectParameters> parameters() const { return m_params; }
  bool setParameters(const std::shared_ptr<FFBEffectParameters> params);
  bool setParameters(const std::shared_ptr<FFBPeriodicEffectParameters> params);
  bool operator==(const FFBEffect& other) const;

private:
  std::shared_ptr<FFBPeriodicEffectParameters> m_params;
};

#endif // LINUXFFBPERIODICEFFECT_H
