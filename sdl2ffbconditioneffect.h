#ifndef SDL2FFBCONDITIONEFFECT_H
#define SDL2FFBCONDITIONEFFECT_H

#include "sdl2ffbeffect.h"
#include "ffbconditioneffectparameters.h"

class SDL2FFBConditionEffect : public SDL2FFBEffect
{
public:
  SDL2FFBConditionEffect();
  virtual SDL_HapticEffect* createFFstruct();
  inline const std::shared_ptr<FFBEffectParameters> parameters() const { return m_params; }
  bool setParameters(const std::shared_ptr<FFBEffectParameters> params);

  bool operator==(const FFBEffect& other) const;

private:
  bool setParameters(const std::shared_ptr<FFBConditionEffectParameters> params);

  std::shared_ptr<FFBConditionEffectParameters> m_params;
};

#endif // SDL2FFBCONDITIONEFFECT_H
