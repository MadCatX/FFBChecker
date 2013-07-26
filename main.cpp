#include "deviceprober.h"
#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char** argv)
{
  QApplication myApp(argc, argv);
  std::shared_ptr<DeviceProber> prober(new DeviceProber);
  MainWindow* mWin = new MainWindow(prober);

  mWin->show();
  return myApp.exec();
}
