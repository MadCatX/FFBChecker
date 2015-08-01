#ifndef SDL2FFBEFFECT_H
#define SDL2FFBEFFECT_H

#include "ffbeffect.h"
#include "SDL.h"

class SDL2FFBEffect : public FFBEffect
{
public:
  explicit SDL2FFBEffect(FFBEffectTypes type) : FFBEffect(type) {}
  virtual SDL_HapticEffect* createFFstruct();

protected:
  virtual bool checkGenericParameters(const std::shared_ptr<FFBEffectParameters> params);
  bool checkEnvelopeParameters(const int attackLength, const int attackLevel, const int fadeLength, const int fadeLevel);
};

#endif // SDL2FFBEFFECT_H
