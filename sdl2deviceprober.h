#ifndef SDL2DEVICEPROBER_H
#define SDL2DEVICEPROBER_H

#include "deviceprober.h"
#include "SDL.h"
#include "sdl2ffbdevice.h"
#include <list>

class SDL2DeviceProber : public DeviceProber
{
public:
  static bool initializeSDL();

  explicit SDL2DeviceProber() : DeviceProber(DeviceInterfaces::SDL2) {}
  void closeAllDevices();
  DeviceList listDevices();
  std::shared_ptr<FFBDevice> openDevice(const QString& id);

private:
  std::list<std::shared_ptr<SDL2FFBDevice>> m_openedDevices;

  static bool s_SDLInited;


};

#endif // SDL2DEVICEPROBER_H