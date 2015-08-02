#include "deviceprober.h"
#include "globalsettings.h"
#include "mainwindow.h"
#include <QtWidgets/QApplication>

#ifdef FFBC_PLATFORM_WIN32
#include <QtCore/QtPlugin>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#endif

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
    if (cmdArgs.contains(NO_CHECKS_ARG))
      doSanityChecks = false;
    else
      doSanityChecks = true;

   GlobalSettings::init(doSanityChecks);
  }

  MainWindow* mWin = new MainWindow(VERSION_STRING);

  mWin->show();
  return myApp.exec();
}
