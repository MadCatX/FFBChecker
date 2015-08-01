#ifndef SDL2FFBRAMPEFFECT_H
#define SDL2FFBRAMPEFFECT_H

#include "sdl2ffbeffect.h"
#include "ffbrampeffectparameters.h"

class SDL2FFBRampEffect : public SDL2FFBEffect
{
public:
  SDL2FFBRampEffect();
  SDL_HapticEffect* createFFstruct();
  inline const std::shared_ptr<FFBEffectParameters> parameters() const { return m_params; }
  bool setParameters(const std::shared_ptr<FFBEffectParameters> params);

private:
  bool setParameters(const std::shared_ptr<FFBRampEffectParameters> params);

  std::shared_ptr<FFBRampEffectParameters> m_params;
};

#endif // SDL2FFBRAMPEFFECT_H
