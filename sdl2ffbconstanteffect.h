#ifndef SDL2FFBCONSTANTEFFECT_H
#define SDL2FFBCONSTANTEFFECT_H

#include "sdl2ffbeffect.h"
#include "ffbconstanteffectparameters.h"

class SDL2FFBConstantEffect :  public SDL2FFBEffect
{
public:
  explicit SDL2FFBConstantEffect();
  SDL_HapticEffect* createFFstruct();
  inline const std::shared_ptr<FFBEffectParameters> parameters() const { return m_params; }
  bool setParameters(const std::shared_ptr<FFBEffectParameters> params);

private:
  bool setParameters(const std::shared_ptr<FFBConstantEffectParameters> params);

  std::shared_ptr<FFBConstantEffectParameters> m_params;
};

#endif // SDL2FFBCONSTANTEFFECT_H
