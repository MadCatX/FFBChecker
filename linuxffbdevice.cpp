#include "linuxffbdevice.h"
#include "linuxffbeffectfactory.h"
#include <QtWidgets/QMessageBox>
#include <QDebug>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/stat.h>

#define CHECK_EFFECT_IDX(idx) if (idx < 0 || idx > c_maxEffectCount) return false

const quint8 LinuxFFBDevice::BITS_PER_LONG = sizeof(unsigned long) * 8;

LinuxFFBDevice::LinuxFFBDevice(const int fd, const int maxEffectCount, const QString path) :
  FFBDevice(maxEffectCount),
  c_fd(fd),
  c_path(path)
{
  for (int i = 0; i < maxEffectCount; i++)
    m_effects.push_back(LinuxFFBEffectFactory::createEffect(FFBEffectTypes::NONE));
}

void LinuxFFBDevice::close()
{
  for (int idx = 0; idx < c_maxEffectCount; idx++) {
    stopEffect(idx);
    removeAndEraseEffect(idx);
  }

  ::close(c_fd);
}

bool LinuxFFBDevice::queryDeviceCapabilities()
{
  unsigned long caps[4];
  int ret = ioctl(c_fd, EVIOCGBIT(EV_FF, sizeof(caps)), caps);
  if (ret < 0)
    return false;

  /* Query FFB effects this device can do */
  if (testBit(FF_CONSTANT, caps))
    m_availableEffects.push_back(FFBEffectTypes::CONSTANT);
  if (testBit(FF_PERIODIC, caps))
    m_availableEffects.push_back(FFBEffectTypes::PERIODIC);
  if (testBit(FF_RAMP, caps))
    m_availableEffects.push_back(FFBEffectTypes::RAMP);
  if (testBit(FF_SPRING, caps) || testBit(FF_FRICTION, caps) ||
      testBit(FF_DAMPER, caps) || testBit(FF_INERTIA, caps))
    m_availableEffects.push_back(FFBEffectTypes::CONDITION);
  if (testBit(FF_RUMBLE, caps))
    m_availableEffects.push_back(FFBEffectTypes::RUMBLE);

  /* Query waveforms for PERIODIC if the device supports it */
  if (hasEffect(FFBEffectTypes::PERIODIC)) {
    if (testBit(FF_SQUARE, caps))
      m_availablePeriodicWaveforms.push_back(PeriodicWaveforms::SQUARE);
    if (testBit(FF_TRIANGLE, caps))
      m_availablePeriodicWaveforms.push_back(PeriodicWaveforms::TRIANGLE);
    if (testBit(FF_SINE, caps))
      m_availablePeriodicWaveforms.push_back(PeriodicWaveforms::SINE);
    if (testBit(FF_SAW_UP, caps))
      m_availablePeriodicWaveforms.push_back(PeriodicWaveforms::SAW_UP);
    if (testBit(FF_SAW_DOWN, caps))
      m_availablePeriodicWaveforms.push_back(PeriodicWaveforms::SAW_DOWN);
  }

  /* Query condition effect subtypes */
  if (testBit(FF_SPRING, caps))
    m_availableConditionSubtypes.push_back(ConditionSubtypes::SPRING);
  if (testBit(FF_FRICTION, caps))
    m_availableConditionSubtypes.push_back(ConditionSubtypes::FRICTION);
  if (testBit(FF_DAMPER, caps))
    m_availableConditionSubtypes.push_back(ConditionSubtypes::DAMPER);
  if (testBit(FF_INERTIA, caps))
    m_availableConditionSubtypes.push_back(ConditionSubtypes::INERTIA);

  return true;
}

bool LinuxFFBDevice::removeAndEraseEffect(const int idx)
{
  if (m_effects[idx]->status() == FFBEffect::FFBEffectStatus::NOT_LOADED)
    return true;

  if (removeEffect(idx)) {
    m_effects[idx] = LinuxFFBEffectFactory::createEffect(FFBEffectTypes::NONE);
    if (m_effects[idx]->type() != FFBEffectTypes::NONE) {
      qCritical("Unable to empty the effect slot.");
      return false;
    }
  } else {
    qCritical("Unable to stop the effect.");
    return false;
  }

  m_effects[idx]->setStatus(FFBEffect::FFBEffectStatus::NOT_LOADED);
  return true;
}

bool LinuxFFBDevice::removeEffect(const int idx)
{
  std::shared_ptr<LinuxFFBEffect> linEff;
  if (!stopEffect(idx))
    return false;

  if (m_effects[idx]->type() == FFBEffectTypes::NONE)
    return true;

  linEff = std::static_pointer_cast<LinuxFFBEffect>(m_effects[idx]);

  int internalIdx = linEff->internalIdx();
  int ret = ioctl(c_fd, EVIOCRMFF, internalIdx);
  if (ret < 0)
    return false;
  return true;
}

bool LinuxFFBDevice::startEffect(const int idx, const FFBEffectTypes type, std::shared_ptr<FFBEffectParameters> parameters)
{
  std::shared_ptr<LinuxFFBEffect> linEff;
  int ret;

  CHECK_EFFECT_IDX(idx);

  if (m_effects[idx]->status() == FFBEffect::FFBEffectStatus::NOT_LOADED) {
    if (!uploadEffect(idx, type, parameters))
      return false;
  }
  if (m_effects[idx]->status() == FFBEffect::FFBEffectStatus::PLAYING)
    return true;

  linEff = std::static_pointer_cast<LinuxFFBEffect>(m_effects[idx]);

  /* Start playback */
  struct input_event evt;
  evt.type = EV_FF;
  evt.code = linEff->internalIdx();
  evt.value = linEff->parameters()->repeat;

  ret = write(c_fd, &evt, sizeof(struct input_event));
  if (ret != sizeof(struct input_event)) {
    QMessageBox::critical(nullptr, "FFB Device", "Effect could not have been started, error code: " + QString::number(ret));
    qDebug() << "Effect not started" << ret;
    return false;
  }

  linEff->setStatus(FFBEffect::FFBEffectStatus::PLAYING);

  return true;
}

bool LinuxFFBDevice::stopEffect(const int idx)
{
  std::shared_ptr<LinuxFFBEffect> linEff;

  CHECK_EFFECT_IDX(idx);

  if (m_effects[idx] == nullptr)
    return true;

  if (m_effects[idx]->status() != FFBEffect::FFBEffectStatus::PLAYING)
    return true;

  linEff = std::static_pointer_cast<LinuxFFBEffect>(m_effects[idx]);

  int internalIdx = linEff->internalIdx();

  struct input_event evt;
  evt.type = EV_FF;
  evt.code = internalIdx;
  evt.value = 0;

  int ret = write(c_fd, &evt, sizeof(struct input_event));
  if (ret != sizeof(struct input_event))
    return false;

  linEff->setStatus(FFBEffect::FFBEffectStatus::UPLOADED);
  return true;
}

bool LinuxFFBDevice::uploadEffect(const int idx, const FFBEffectTypes type, std::shared_ptr<FFBEffectParameters> parameters)
{
  struct ff_effect* kernelEff = nullptr;
  std::shared_ptr<FFBEffect> effect = LinuxFFBEffectFactory::createEffect(type);
  std::shared_ptr<LinuxFFBEffect> linEff;

  if (type != FFBEffectTypes::NONE)
    linEff = std::static_pointer_cast<LinuxFFBEffect>(effect);
  else
    return false;

  CHECK_EFFECT_IDX(idx);

  if (linEff == nullptr) {
    qDebug() << "Unable to create effect";
    return false;
  }
  if (!linEff->setParameters(parameters)) {
    qDebug() << "Unable to set effect parameters, some values are probably invalid.";
    return false;
  }

  if (idx < 0 || idx > c_maxEffectCount) {
    qCritical() << "Effect index out of bounds";
    return false;
  }

  /* There is no effect in the selected slot */
  if (m_effects[idx]->type() == FFBEffectTypes::NONE) {
    linEff->setStatus(FFBEffect::FFBEffectStatus::UPLOADED);
    qDebug() << "Creating new effect";
  } else {

    if (*m_effects[idx] != *linEff) {
      if (!removeEffect(idx)) {
        QMessageBox::critical(nullptr, "FFB Device", "Unable to remove effect");
        return false;
      }
      linEff->setStatus(FFBEffect::FFBEffectStatus::UPLOADED);
      qDebug() << "Recreating effect" << idx;
    } else {
      linEff->setInternalIdx(std::static_pointer_cast<LinuxFFBEffect>(m_effects[idx])->internalIdx());
      linEff->setStatus(m_effects[idx]->status());
      qDebug() << "Updating effect" << idx;
    }
  }

  kernelEff = linEff->createFFStruct();
  if (kernelEff == nullptr) {
    QMessageBox::critical(nullptr, "FFB Device", "ff_effect struct could not have been created. Effect not uploaded.");
    qDebug() << "struct ff_effect not created";
    return false;
  }

  int ret = ioctl(c_fd, EVIOCSFF, kernelEff);
  if (ret < 0) {
    QMessageBox::critical(nullptr, "FFB Device", "Effect could not have been uploaded, error code: " + QString::number(ret));
    qDebug() << "Effect not uploaded" << ret;
    delete kernelEff;
    return false;
  }

  linEff->setInternalIdx(kernelEff->id);
  delete kernelEff;

  m_effects[idx] = linEff;
  return true;
}
