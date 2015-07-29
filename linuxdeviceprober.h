#ifndef LINUXDEVICEPROBER_H
#define LINUXDEVICEPROBER_H

#include "deviceprober.h"
#include "linuxffbdevice.h"

class LinuxDeviceProber : public DeviceProber
{
public:
  explicit LinuxDeviceProber() {}
  void closeAllDevices();
  DeviceList listDevices();
  std::shared_ptr<FFBDevice> openDevice(const QString& id);

private:
  std::list<std::shared_ptr<LinuxFFBDevice>> m_openedDevices;

  static const QString DEVICE_NODES_PATH;
  static const QString res_ffbdeviceErrCap;

signals:

public slots:

};

#endif // LINUXDEVICEPROBER_H
