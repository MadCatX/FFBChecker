#include "deviceprober.h"
#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include <QDebug>

int main(int argc, char** argv)
{
  QApplication myApp(argc, argv);
  const QString VERSION_STRING = QString(APP_NAME) + " " + QString::number(APP_VERSION_MAJOR) + "." + QString::number(APP_VERSION_MINOR) +
                                 QString(APP_VERSION_REL);
  qDebug() << VERSION_STRING;
  std::shared_ptr<DeviceProber> prober(new DeviceProber);
  MainWindow* mWin = new MainWindow(prober);

  mWin->show();
  return myApp.exec();
}
