#ifndef FFBCONSTANTEFFECT_H
#define FFBCONSTANTEFFECT_H

#include "ffbeffect.h"
#include "ffbconstanteffectparameters.h"

class FFBConstantEffect : public FFBEffect
{
public:
  explicit FFBConstantEffect();
  struct ff_effect* createFFStruct();
  inline const std::shared_ptr<FFBEffectParameters> parameters() const { return m_params; }
  bool setParameters(const std::shared_ptr<FFBEffectParameters> params);
  bool setParameters(const std::shared_ptr<FFBConstantEffectParameters> params);

private:
  std::shared_ptr<FFBConstantEffectParameters> m_params;
};

#endif // FFBCONSTANTEFFECT_H
