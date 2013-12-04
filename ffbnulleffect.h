#ifndef FFBNULLEFFECT_H
#define FFBNULLEFFECT_H

#include "ffbeffect.h"

class FFBNullEffect : public FFBEffect
{
public:
  explicit FFBNullEffect();
  inline struct ff_effect* createFFStruct() { return nullptr; }
  inline const std::shared_ptr<FFBEffectParameters> parameters() const { return nullptr; }
  inline bool setParameters(const std::shared_ptr<FFBEffectParameters> params) { (void)(params); return false; }
};

#endif // FFBNULLEFFECT_H
