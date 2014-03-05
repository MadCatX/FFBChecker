#ifndef FFBRUMBLEEFFECT_H
#define FFBRUMBLEEFFECT_H

#include "ffbeffect.h"
#include "ffbrumbleeffectparameters.h"

class FFBRumbleEffect : public FFBEffect
{
public:
  FFBRumbleEffect();
  struct ff_effect* createFFStruct();
  inline const std::shared_ptr<FFBEffectParameters> parameters() const { return m_params; }
  bool setParameters(const std::shared_ptr<FFBEffectParameters> params);
  bool setParameters(const std::shared_ptr<FFBRumbleEffectParameters> params);

private:
  std::shared_ptr<FFBRumbleEffectParameters> m_params;
};

#endif // FFBRUMBLEEFFECT_H
