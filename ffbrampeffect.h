#ifndef FFBRAMPEFFECT_H
#define FFBRAMPEFFECT_H

#include "ffbeffect.h"
#include "ffbrampeffectparameters.h"

class FFBRampEffect : public FFBEffect
{
public:
  FFBRampEffect();
  ~FFBRampEffect();
  struct ff_effect* createFFStruct();
  inline const std::shared_ptr<FFBEffectParameters> parameters() const { return m_params; }
  bool setParameters(const std::shared_ptr<FFBEffectParameters> params);
  bool setParameters(const std::shared_ptr<FFBRampEffectParameters> params);

private:
  std::shared_ptr<FFBRampEffectParameters> m_params;
};

#endif // FFBRAMPEFFECT_H
