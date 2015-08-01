#ifndef LINUXFFBRAMPEFFECT_H
#define LINUXFFBRAMPEFFECT_H

#include "linuxffbeffect.h"
#include "ffbrampeffectparameters.h"

class LinuxFFBRampEffect : public LinuxFFBEffect
{
public:
  LinuxFFBRampEffect();
  struct ff_effect* createFFStruct();
  inline const std::shared_ptr<FFBEffectParameters> parameters() const { return m_params; }
  bool setParameters(const std::shared_ptr<FFBEffectParameters> params);

private:
  bool setParameters(const std::shared_ptr<FFBRampEffectParameters> params);

  std::shared_ptr<FFBRampEffectParameters> m_params;
};

#endif // FFBRAMPEFFECT_H
