#ifndef DEVICEPROBER_H
#define DEVICEPROBER_H

#include "ffbdevice.h"
#include <memory>
#include <QtCore/QDir>
#include <QtCore/QObject>

class DeviceProber : public QObject
{
  Q_OBJECT
public:
  struct DeviceInfo {
    QString path;
    QString tag;
  };
  typedef QList<DeviceInfo> DeviceList;

  explicit DeviceProber(QObject* parent = 0);
  DeviceList listDevices();
  std::shared_ptr<FFBDevice> openDevice(const QString& path);

private:
  std::list<std::shared_ptr<FFBDevice>> m_openedDevices;

  static const QString DEVICE_NODES_PATH;
  static const QString res_ffbdeviceErrCap;

signals:

public slots:

};

#endif // DEVICEPROBER_H
