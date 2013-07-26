#include "deviceprober.h"
#include "ffbdevice.h"
#include <QtCore/QDebug>
#include <QtWidgets/QMessageBox>
#include <linux/input.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

const QDir DeviceProber::s_deviceNodesByID("/dev/input/by-id");
const QString DeviceProber::res_ffbdeviceErrCap("FFB Device error");

DeviceProber::DeviceProber(QObject* parent) :
  QObject(parent)
{
}

QStringList DeviceProber::listDevicesByID()
{
  QStringList devices = DeviceProber::s_deviceNodesByID.entryList(QDir::NoDotAndDotDot);

  foreach (const QString s, devices)
    qDebug() << s;

  return devices;
}

std::shared_ptr<FFBDevice> DeviceProber::openDeviceByID(const QString& id)
{
  QString path = DeviceProber::s_deviceNodesByID.absoluteFilePath(id);
  /* Check if the device is already opened */
  for (std::shared_ptr<FFBDevice> dev : m_openedDevices) {
    if (QString::compare(id, dev->id()) == 0) {
      qDebug() << "Device" << id << "already opened";
      return dev;
    }
  }

  int fd = open(path.toLocal8Bit(), O_RDWR);
  if (!fd) {
    QMessageBox::critical(nullptr, res_ffbdeviceErrCap, "Cannot open device.");
    return nullptr;
  }

  int maxEffectCount;
  int ret = ioctl(fd, EVIOCGEFFECTS, &maxEffectCount);
  if (ret < 0) {
    QMessageBox::critical(nullptr, res_ffbdeviceErrCap, "Cannot query maximum effects count.\nDevice probably does not support Force Feedback (errno " + QString::number(ret) + ")");
    close(fd);
    return nullptr;
  }
  if (maxEffectCount < 1) {
    QMessageBox::critical(nullptr, res_ffbdeviceErrCap, "Maximum effect count for this device is zero.");
    close(fd);
    return nullptr;
  }

  std::shared_ptr<FFBDevice> device(new FFBDevice(fd, id, maxEffectCount));
  if (!device->queryDeviceCapabilities()) {
    QMessageBox::critical(nullptr, res_ffbdeviceErrCap, "Unable to query device capabilities.");
    return nullptr;
  }

  m_openedDevices.push_back(device);
  return device;
}
