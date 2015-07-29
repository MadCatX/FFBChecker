#ifndef LINUXFFBCONDITIONEFFECT_H
#define LINUXFFBCONDITIONEFFECT_H

#include "linuxffbeffect.h"
#include "ffbconditioneffectparameters.h"

class LinuxFFBConditionEffect : public LinuxFFBEffect
{
public:
  explicit LinuxFFBConditionEffect();
  struct ff_effect* createFFStruct();
  inline const std::shared_ptr<FFBEffectParameters> parameters() const { return m_params; }
  bool setParameters(const std::shared_ptr<FFBEffectParameters> params);
  bool setParameters(const std::shared_ptr<FFBConditionEffectParameters> params);
  bool operator==(const FFBEffect& other) const;

private:
  std::shared_ptr<FFBConditionEffectParameters> m_params;
};

#endif // FFBCONDITIONEFFECT_H