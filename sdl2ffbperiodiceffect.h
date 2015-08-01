#ifndef SDL2FFBPERIODICEFFECT_H
#define SDL2FFBPERIODICEFFECT_H

#include "sdl2ffbeffect.h"
#include "ffbperiodiceffectparameters.h"

class SDL2FFBPeriodicEffect : public SDL2FFBEffect
{
public:
  SDL2FFBPeriodicEffect();
  SDL_HapticEffect* createFFstruct();
  inline const std::shared_ptr<FFBEffectParameters> parameters() const { return m_params; }
  bool setParameters(const std::shared_ptr<FFBEffectParameters> params);

  bool operator==(const FFBEffect& other) const;

private:
  bool setParameters(const std::shared_ptr<FFBPeriodicEffectParameters> params);

  std::shared_ptr<FFBPeriodicEffectParameters> m_params;
};

#endif // SDL2FFBPERIODICEFFECT_H
