#ifndef DEVICEPROBER_H
#define DEVICEPROBER_H

#include "ffbdevice.h"
#include <memory>
#include <QtCore/QVariant>
#include <QtCore/QObject>

class DeviceProber
{
public:
  struct DeviceInfo {
    QVariant id;
    QString name;
  };
  typedef QList<DeviceInfo> DeviceList;

  enum class DeviceInterfaces : unsigned int {
    NONE,
    LINUX,
    SDL2
  };

  virtual void closeAllDevices() = 0;
  virtual DeviceList listDevices() = 0;
  virtual std::shared_ptr<FFBDevice> openDevice(const QString& id) = 0;

  const DeviceInterfaces type;

protected:
  explicit DeviceProber() : type(DeviceInterfaces::NONE) {}
};


#endif // DEVICEPROBER_H

