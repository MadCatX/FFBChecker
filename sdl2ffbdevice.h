#ifndef SDL2FFBDEVICE_H
#define SDL2FFBDEVICE_H

#include <SDL2/SDL.h>
#include "ffbdevice.h"

class SDL2FFBDevice : public FFBDevice {
public:
  SDL2FFBDevice(SDL_Haptic* haptic, const int maxEffectCount);
  void close();
  bool queryDeviceCapabilities();
  bool removeAndEraseEffect(const int idx);
  bool setAutocentering(const int strength);
  bool setGain(const int idx);
  bool startEffect(const int idx, const FFBEffectTypes type, std::shared_ptr<FFBEffectParameters> parameters);
  bool stopEffect(const int idx);
  bool uploadEffect(const int idx, const FFBEffectTypes type, std::shared_ptr<FFBEffectParameters> parameters);

private:
  bool removeEffect(const int idx);

  SDL_Haptic* c_haptic;

  static const QString SDL2DEV_ERR_CAPTION;
};

#endif // SDL2FFBDEVICE_H
