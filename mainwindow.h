#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "conditioneffectsettings.h"
#include "constanteffectsettings.h"
#include "deviceprober.h"
#include "ffbconstanteffectparameters.h"
#include "ffbdevice.h"
#include "ffbperiodiceffectparameters.h"
#include "ffbrampeffectparameters.h"
#include "ffbrumbleeffectparameters.h"
#include "periodiceffectsettings.h"
#include "rampeffectsettings.h"
#include "rumbleeffectsettings.h"
#include <memory>
#include <QMainWindow>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(std::shared_ptr<DeviceProber> prober, const QString& title, QWidget* parent = 0);
  ~MainWindow();

private:
  EffectSettings* effectSettingsByType(FFBEffectTypes type);
  void fillDeviceList();
  void fillEffectSlotsList(const int idx);
  void fillEffectTypesList(const QStringList& list);
  bool readEnvelopeParameters(std::shared_ptr<FFBEnvelopeParameters> params, const EnvelopeSettings* es);
  bool readEffectParameters(std::shared_ptr<FFBEffectParameters>& params, FFBEffectTypes type);
  bool readGeneralEffectParameters(std::shared_ptr<FFBEffectParameters> params);
  void setEffectStatusText(const FFBEffect::FFBEffectStatus status);

  std::shared_ptr<FFBDevice> m_activeDevice;
  ConditionEffectSettings* m_conditionEffSet;
  ConstantEffectSettings* m_constantEffSet;
  PeriodicEffectSettings* m_periodicEffSet;
  RampEffectSettings* m_rampEffSet;
  RumbleEffectSettings* m_rumbleEffSet;
  std::shared_ptr<DeviceProber> m_prober;
  Ui::MainWindow* ui;

  static const QString res_deviceErrorCap;
  static const QString res_effectNotLoaded;
  static const QString res_effectPlaying;
  static const QString res_effectUploaded;
  static const QString res_inputFormatErrCap;

private slots:
  void onDeviceSelected(const int idx);
  void onEffectSlotSelected(const int idx);
  void onEffectTypeSelected(const int idx);
  void onRefreshDevicesClicked();
  void onRemoveEffectClicked();
  void onStartEffectClicked();
  void onStopEffectClicked();
  void onUploadEffectClicked();
};

#endif // MAINWINDOW_H
