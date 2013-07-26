#ifndef FFBPERIODICEFFECT_H
#define FFBPERIODICEFFECT_H

#include "ffbeffect.h"
#include "ffbperiodiceffectparameters.h"

class FFBPeriodicEffect : public FFBEffect
{
public:
  FFBPeriodicEffect();
  ~FFBPeriodicEffect();
  struct ff_effect* createFFStruct();
  inline const std::shared_ptr<FFBEffectParameters> parameters() const { return m_params; }
  bool setParameters(const std::shared_ptr<FFBEffectParameters> params);
  bool setParameters(const std::shared_ptr<FFBPeriodicEffectParameters> params);
  bool operator==(const FFBEffect& other) const;
  bool operator!=(const FFBEffect& other) const;

private:
  std::shared_ptr<FFBPeriodicEffectParameters> m_params;
};

#endif // FFBPERIODICEFFECT_H
