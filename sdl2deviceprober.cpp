#include "sdl2deviceprober.h"
#include <QtCore/QDebug>
#include <QtWidgets/QMessageBox>

bool SDL2DeviceProber::s_SDLInited = false;

bool SDL2DeviceProber::initializeSDL()
{
  int ret;

  if (s_SDLInited)
    return true;

  ret = SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC);
  if (ret == 0) {
    s_SDLInited = true;
    return true;
  }

  QMessageBox::warning(nullptr, "SDL2 error",
		       QString("Unable to initialize SDL2 (%1). SDL2 interface will not be available.").arg(SDL_GetError()));
  return false;
}

void SDL2DeviceProber::closeAllDevices()
{
  if (!s_SDLInited)
    return;

  return;
}

DeviceProber::DeviceList SDL2DeviceProber::listDevices()
{
  DeviceProber::DeviceList devList;
  int numHapt;

  if (!s_SDLInited)
    return devList;

  numHapt = SDL_NumHaptics();

  for (int idx = 0; idx < numHapt; idx++) {
    DeviceProber::DeviceInfo dinfo;

    dinfo.name = QString(SDL_HapticName(idx));
    dinfo.id = QVariant(idx);

    devList.push_back(dinfo);
  }

  return devList;
}

std::shared_ptr<FFBDevice> SDL2DeviceProber::openDevice(const QString& id)
{
  SDL_Haptic* haptic;
  std::shared_ptr<SDL2FFBDevice> device;
  int idx;
  int maxEffectCount;
  bool ok;

  if (!s_SDLInited)
    return nullptr;

  idx = id.toInt(&ok);
  if (!ok)
    return nullptr;

  haptic = SDL_HapticOpen(idx);
  if (haptic == nullptr)
    return nullptr;

  maxEffectCount = SDL_HapticNumEffects(haptic);
  if (maxEffectCount < 1) {
    QMessageBox::critical(nullptr, "SDL2 device error", "Maximum effect count for this device is zero.");
    SDL_HapticClose(haptic);
    return nullptr;
  }

  device = std::make_shared<SDL2FFBDevice>(haptic, maxEffectCount);
  if (!device->queryDeviceCapabilities()) {
    QMessageBox::critical(nullptr, "SDL2 device error", "Unable to query device capabilities.");
    device->close();
    return nullptr;
  }

  m_openedDevices.push_back(device);
  return device;
}


