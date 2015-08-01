#ifndef LINUXFFBCONSTANTEFFECT_H
#define LINUXFFBCONSTANTEFFECT_H

#include "linuxffbeffect.h"
#include "ffbconstanteffectparameters.h"

class LinuxFFBConstantEffect : public LinuxFFBEffect
{
public:
  explicit LinuxFFBConstantEffect();
  struct ff_effect* createFFStruct();
  inline const std::shared_ptr<FFBEffectParameters> parameters() const { return m_params; }
  bool setParameters(const std::shared_ptr<FFBEffectParameters> params);

private:
  bool setParameters(const std::shared_ptr<FFBConstantEffectParameters> params);

  std::shared_ptr<FFBConstantEffectParameters> m_params;
};

#endif // LINUXFFBCONSTANTEFFECT_H