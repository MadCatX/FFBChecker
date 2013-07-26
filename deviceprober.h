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
  explicit DeviceProber(QObject* parent = 0);
  QStringList listDevicesByID();
  std::shared_ptr<FFBDevice> openDeviceByID(const QString& id);

private:
  std::list<std::shared_ptr<FFBDevice>> m_openedDevices;

  static const QDir s_deviceNodesByID;
  static const QString res_ffbdeviceErrCap;

signals:

public slots:

};

#endif // DEVICEPROBER_H
