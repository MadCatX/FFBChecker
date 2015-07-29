#ifndef FFBNULLEFFECT_H
#define FFBNULLEFFECT_H

#include "ffbeffect.h"

class FFBNullEffect : public FFBEffect
{
public:
  explicit FFBNullEffect();
  inline const std::shared_ptr<FFBEffectParameters> parameters() const { return nullptr; }
  inline bool setParameters(const std::shared_ptr<FFBEffectParameters> params) { (void)(params); return false; }

protected:
  bool checkGenericParameters(const std::shared_ptr<FFBEffectParameters> params) { Q_UNUSED(params); return false; }
};

#endif // FFBNULLEFFECT_H
