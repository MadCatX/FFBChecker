#ifndef SDL2FFBDEVICE_H
#define SDL2FFBDEVICE_H

#include "SDL.h"
#include "ffbdevice.h"

class SDL2FFBDevice : public FFBDevice {
public:
  SDL2FFBDevice(SDL_Haptic* haptic, const int maxEffectCount);
  void close();
  bool queryDeviceCapabilities();
  bool removeAndEraseEffect(const int idx);
  bool startEffect(const int idx, const FFBEffectTypes type, std::shared_ptr<FFBEffectParameters> parameters);
  bool stopEffect(const int idx);
  bool uploadEffect(const int idx, const FFBEffectTypes type, std::shared_ptr<FFBEffectParameters> parameters);

private:
  SDL_Haptic* c_haptic;
};

#endif // SDL2FFBDEVICE_H