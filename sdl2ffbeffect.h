#ifndef SDL2FFBEFFECT_H
#define SDL2FFBEFFECT_H

#include "ffbeffect.h"
#include <SDL2/SDL.h>

class SDL2FFBEffect : public FFBEffect
{
public:
  explicit SDL2FFBEffect(FFBEffectTypes type) : FFBEffect(type) {}
  virtual SDL_HapticEffect* createFFstruct() = 0;
  inline int internalIdx() const { return m_internalIdx; }
  inline void setInternalIdx(const int idx) { m_internalIdx = idx; }

protected:
  SDL_HapticEffect* initFFstruct();
  virtual bool checkGenericParameters(const std::shared_ptr<FFBEffectParameters> params);
  bool checkEnvelopeParameters(const int attackLength, const int attackLevel, const int fadeLength, const int fadeLevel);

private:
  int m_internalIdx;
};

#endif // SDL2FFBEFFECT_H
