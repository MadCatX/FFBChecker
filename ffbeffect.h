#ifndef FFBEFFECT_H
#define FFBEFFECT_H

#include "ffbeffectparameters.h"
#include "globals.h"
#include <memory>

class FFBEffect {
public:
  enum class FFBEffectStatus { PLAYING, UPLOADED, NOT_LOADED };

  explicit FFBEffect(FFBEffectTypes type);
  virtual const std::shared_ptr<FFBEffectParameters> parameters() const = 0;
  virtual bool setParameters(const std::shared_ptr<FFBEffectParameters> params) = 0;
  inline void setStatus(FFBEffectStatus status) { m_status = status; }
  inline FFBEffectStatus status() const { return m_status; }
  inline FFBEffectTypes type() const { return m_type; }

  virtual bool operator==(const FFBEffect&) const;
  virtual bool operator!=(const FFBEffect&) const;

protected:
  virtual bool checkEnvelopeParameters(const int attackLength, const int attackLevel, const int fadeLength, const int fadeLevel) = 0;
  virtual bool checkGenericParameters(const std::shared_ptr<FFBEffectParameters> params) = 0;
  void reportError(const QString& errorMsg) const;

  static const QString PRERR_CAPTION;

private:
  FFBEffectStatus m_status;
  FFBEffectTypes m_type;

};

#endif // FFBEFFECT_H
