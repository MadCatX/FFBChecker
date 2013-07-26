#ifndef FFBEFFECT_H
#define FFBEFFECT_H

#include "ffbeffectparameters.h"
#include "globals.h"
#include <memory>
#include <linux/input.h>

class FFBEffect {
public:
  enum class FFBEffectStatus { PLAYING, STOPPED, NOT_LOADED };

  explicit FFBEffect(FFBEffectTypes type);
  virtual struct ff_effect* createFFStruct() = 0;
  inline int internalIdx() const { return m_internalIdx; }
  virtual const std::shared_ptr<FFBEffectParameters> parameters() const = 0;
  void reportError(const QString& errorMsg) const;
  inline void setInternalIdx(int idx) { m_internalIdx = idx; }
  virtual bool setParameters(const std::shared_ptr<FFBEffectParameters> params) = 0;
  inline void setStatus(FFBEffectStatus status) { m_status = status; }
  inline FFBEffectStatus status() const { return m_status; }
  inline FFBEffectTypes type() const { return m_type; }

  virtual bool operator==(const FFBEffect&) const;
  virtual bool operator!=(const FFBEffect&) const;

protected:
  struct ff_effect* createFFStruct(const std::shared_ptr<FFBEffectParameters> params);
  bool checkGenericParameters(const std::shared_ptr<FFBEffectParameters> params);

private:
  int m_internalIdx;
  FFBEffectStatus m_status;
  FFBEffectTypes m_type;

signals:

public slots:

};

#endif // FFBEFFECT_H
