#include "deviceprober.h"
#include "globalsettings.h"
#include "mainwindow.h"
#include <QtWidgets/QApplication>

#include <QDebug>

const QString NO_CHECKS_ARG("--no-checks");

int main(int argc, char** argv)
{
  QApplication myApp(argc, argv);
  const QString VERSION_STRING = QString(APP_NAME) + " " + QString::number(APP_VERSION_MAJOR) + "." + QString::number(APP_VERSION_MINOR) +
                                 QString(APP_VERSION_REL);

  /* Setup global settings */
  {
    bool doSanityChecks;
    QStringList cmdArgs = QCoreApplication::arguments();
    if (cmdArgs.contains(NO_CHECKS_ARG)) {
      doSanityChecks = false;
      qDebug() << "Disabling effect parameters sanity checks";
    } else
      doSanityChecks = true;

   GlobalSettings::init(doSanityChecks);
  }

  std::shared_ptr<DeviceProber> prober(new DeviceProber);
  MainWindow* mWin = new MainWindow(prober, VERSION_STRING);

  mWin->show();
  return myApp.exec();
}
