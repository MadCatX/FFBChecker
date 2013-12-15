#ifndef FFBCONDITIONEFFECT_H
#define FFBCONDITIONEFFECT_H

#include "ffbeffect.h"
#include "ffbconditioneffectparameters.h"

class FFBConditionEffect : public FFBEffect
{
public:
  explicit FFBConditionEffect();
  struct ff_effect* createFFStruct();
  inline const std::shared_ptr<FFBEffectParameters> parameters() const { return m_params; }
  bool setParameters(const std::shared_ptr<FFBEffectParameters> params);
  bool setParameters(const std::shared_ptr<FFBConditionEffectParameters> params);
  bool operator==(const FFBEffect& other) const;

private:
  std::shared_ptr<FFBConditionEffectParameters> m_params;
};

#endif // FFBCONDITIONEFFECT_H
