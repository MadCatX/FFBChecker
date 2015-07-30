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
  int numJoy;

  if (!s_SDLInited)
    return devList;

  numJoy = SDL_NumJoysticks();

  for (int idx = 0; idx < numJoy; idx++) {
    DeviceProber::DeviceInfo dinfo;

    SDL_Joystick* joystick = SDL_JoystickOpen(idx);

    if (joystick == nullptr) {
      qDebug() << "SDL2: Cannot open joystick at idx" << idx;
      continue;
    }

    if (SDL_JoystickIsHaptic(joystick) != 1) {
      qDebug() << "SDL2: Joystick at idx" << idx << "does not support force feedback";
      SDL_JoystickClose(joystick);
      continue;
    }

    dinfo.name = QString(SDL_JoystickName(joystick));
    dinfo.id = QVariant(idx);

    devList.push_back(dinfo);
    SDL_JoystickClose(joystick);
  }

  return devList;
}

std::shared_ptr<FFBDevice> SDL2DeviceProber::openDevice(const QString& id)
{
  if (!s_SDLInited)
    return nullptr;

  return nullptr;
}

