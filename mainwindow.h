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
  explicit MainWindow(const QString& title, QWidget* parent = 0);
  ~MainWindow();

private:
  enum class ErrorMessages {
    BAD_EFFECT_SLOT,
    CANT_REMOVE_EFFECT,
    CANT_START_EFFECT,
    CANT_UPLOAD_EFFECT
  };

  void createDeviceProber(const DeviceProber::DeviceInterfaces iface);
  EffectSettings* effectSettingsByType(FFBEffectTypes type);
  QString effectTypeToEffectName(const FFBEffectTypes type) const;
  void fillDeviceList();
  void fillEffectSlotsList(const int effectCount);
  void fillEffectTypesList(const std::vector<FFBEffectTypes>& list);
  bool readEnvelopeParameters(std::shared_ptr<FFBEnvelopeParameters> params, const EnvelopeSettings* es);
  bool readEffectParameters(std::shared_ptr<FFBEffectParameters>& params, FFBEffectTypes etype);
  bool readGeneralEffectParameters(std::shared_ptr<FFBEffectParameters> params);
  void setEffectStatusText(const FFBEffect::FFBEffectStatus status);
  void setEffectTypeIndexByType(const FFBEffectTypes etype);
  void showErrorMsgBox(const ErrorMessages msgCode);

  std::shared_ptr<FFBDevice> m_activeDevice;
  ConditionEffectSettings* m_conditionEffSet;
  ConstantEffectSettings* m_constantEffSet;
  std::shared_ptr<DeviceProber> m_prober;
  PeriodicEffectSettings* m_periodicEffSet;
  RampEffectSettings* m_rampEffSet;
  RumbleEffectSettings* m_rumbleEffSet;
  Ui::MainWindow* ui;

  static const QString res_deviceErrorCap;
  static const QString res_effectNotLoaded;
  static const QString res_effectPlaying;
  static const QString res_effectUploaded;
  static const QString res_inputFormatErrCap;

private slots:
  void onDeviceSelected(const int cboxIdx);
  void onEffectSlotSelected(const int cboxIdx);
  void onEffectTypeSelected(const int cboxIdx);
  void onInterfaceSelected(const int cboxIdx);
  void onRefreshDevicesClicked();
  void onRemoveEffectClicked();
  void onStartEffectClicked();
  void onStopEffectClicked();
  void onUploadEffectClicked();
};

#endif // MAINWINDOW_H
