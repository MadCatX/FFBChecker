#include "ffbdevice.h"
#include "ffbeffectfactory.h"
#include <QtWidgets/QMessageBox>
#include <QDebug>

const quint8 FFBDevice::BITS_PER_LONG = sizeof(unsigned long) * 8;

FFBDevice::FFBDevice(const int fd, const QString& id, const int maxEffectCount, QObject* parent) :
  QObject(parent),
  c_fd(fd),
  c_id(id),
  c_maxEffectCount(maxEffectCount)
{
  for (int i = 0; i < maxEffectCount; i++)
    m_effects.push_back(FFBEffectFactory::createEffect(FFBEffectTypes::NONE));
}

QStringList FFBDevice::availableConditionSubtypesList() const
{
  QStringList list;

  for (const ConditionSubtypes s : m_availableConditionSubtypes)
    list << conditionSubtypeName(s);

  return list;
}

QStringList FFBDevice::availableEffectsList() const
{
  QStringList list;

  for (const FFBEffectTypes e : m_availableEffects)
    list << effectName(e);

  return list;
}

QStringList FFBDevice::availableWaveformsList() const
{
  QStringList list;

  for (const PeriodicWaveforms w : m_availablePeriodicWaveforms)
    list << waveformName(w);

  return list;
}

QString FFBDevice::conditionSubtypeName(const ConditionSubtypes subtype) const
{
  switch (subtype) {
    case ConditionSubtypes::DAMPER:
      return "Damper";
    case ConditionSubtypes::FRICTION:
      return "Friction";
    case ConditionSubtypes::INERTIA:
      return "Inertia";
    case ConditionSubtypes::SPRING:
      return "Spring";
    default:
      return "Unknown subtype";
  }
}

QString FFBDevice::effectName(const FFBEffectTypes effect) const
{
  switch (effect) {
    case FFBEffectTypes::CONSTANT:
      return "Constant force";
    case FFBEffectTypes::PERIODIC:
      return "Periodic force";
    case FFBEffectTypes::RAMP:
      return "Ramp";
    case FFBEffectTypes::CONDITION:
      return "Condition";
    case FFBEffectTypes::RUMBLE:
      return "Rumble";
    default:
      return "Unknown effect";
  }
}

const std::shared_ptr<FFBEffectParameters> FFBDevice::effectParameters(const int idx)
{
  if (idx >= c_maxEffectCount)
    return nullptr;

  return m_effects[idx]->parameters();
}

FFBEffect::FFBEffectStatus FFBDevice::effectStatusByIdx(const int idx) const
{
  if (m_effects[idx] == nullptr)
    return FFBEffect::FFBEffectStatus::NOT_LOADED;

  return m_effects[idx]->status();
}

FFBEffectTypes FFBDevice::effectTypeByEffectIdx(const int idx) const
{
  return m_effects[idx]->type();
}

unsigned int FFBDevice::effectTypeToIdx(FFBEffectTypes type)
{
  for (unsigned int i = 0; i < m_availableEffects.size(); i++) {
    if (m_availableEffects[i] == type)
      return i;
  }
  qWarning() << "Effect type no found in the list!";
  return 0;
}

QString FFBDevice::waveformName(const PeriodicWaveforms waveform) const
{
  switch (waveform) {
    case PeriodicWaveforms::SQUARE:
      return "Square";
    case PeriodicWaveforms::TRIANGLE:
      return "Triangle";
    case PeriodicWaveforms::SINE:
      return "Sine";
    case PeriodicWaveforms::SAW_UP:
      return "Saw up";
    case PeriodicWaveforms::SAW_DOWN:
      return "Saw down";
    default:
      return "Unknown waveform";
  }
}

bool FFBDevice::hasEffect(FFBEffectTypes id) const
{
  for (const FFBEffectTypes e : m_availableEffects)
    if (e == id) return true;

  return false;
}

bool FFBDevice::hasPeriodicWaveform(PeriodicWaveforms id) const
{
  for (const PeriodicWaveforms w : m_availablePeriodicWaveforms)
    if (w == id) return true;

  return false;
}

bool FFBDevice::queryDeviceCapabilities()
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

bool FFBDevice::removeAndEraseEffect(const int idx)
{
  if (m_effects[idx]->status() == FFBEffect::FFBEffectStatus::NOT_LOADED)
    return true;

  if (removeEffect(idx)) {
    m_effects[idx] = FFBEffectFactory::createEffect(FFBEffectTypes::NONE);
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

bool FFBDevice::removeEffect(const int idx)
{
  if (!stopEffect(idx))
    return false;

  int internalIdx = m_effects[idx]->internalIdx();
  int ret = ioctl(c_fd, EVIOCRMFF, internalIdx);
  if (ret < 0)
    return false;
  return true;
}

bool FFBDevice::startEffect(const int idx, FFBEffectTypes type, std::shared_ptr<FFBEffectParameters> params)
{
  bool dontStart = false;
  std::shared_ptr<FFBEffect> effect = FFBEffectFactory::createEffect(type);
  if (effect == nullptr) {
    qDebug() << "Unable to create effect";
    return false;
  }
  if (!effect->setParameters(params)) {
    qDebug() << "Unable to set effect parameters, some values are probably invalid.";
    return false;
  }

  if (idx < 0 || idx > c_maxEffectCount) {
    qCritical() << "Effect index out of bounds";
    return false;
  }

  /* There is no effect in the selected slot */
  if (m_effects[idx]->type() == FFBEffectTypes::NONE) {
    qDebug() << "Creating new effect";
  } else {
    if (*m_effects[idx] != *effect) {
      removeEffect(idx);
      qDebug() << "Recreating effect" << idx;
    } else {
      effect->setInternalIdx(m_effects[idx]->internalIdx());
      effect->setStatus(m_effects[idx]->status());
      if (effect->status() == FFBEffect::FFBEffectStatus::PLAYING) {
        dontStart = true;
      }
      qDebug() << "Updating effect" << idx;
    }
  }
  m_effects[idx] = effect;

  struct ff_effect* kernelEff = nullptr;
  kernelEff = m_effects[idx]->createFFStruct();
  if (kernelEff == nullptr) {
    QMessageBox::critical(nullptr, "FFB Device", "ff_effect struct could not have been created. Effect not uploaded.");
    qDebug() << "struct ff_effect not created";
    return false;
  }

  qDebug() << kernelEff->u.condition[0].center << kernelEff->u.condition[0].deadband << kernelEff->u.condition[1].center << kernelEff->u.condition[1].deadband;

  int ret = uploadEffect(kernelEff);
  if (ret < 0) {
    QMessageBox::critical(nullptr, "FFB Device", "Effect could not have been uploaded, error code: " + QString::number(ret));
    qDebug() << "Effect not uploaded" << ret;
    delete kernelEff;
    return false;
  }
  if (dontStart)
    return true;

  m_effects[idx]->setInternalIdx(kernelEff->id);
  m_effects[idx]->setStatus(FFBEffect::FFBEffectStatus::STOPPED);

  /* Start playback */
  struct input_event evt;
  evt.type = EV_FF;
  evt.code = kernelEff->id;
  evt.value = m_effects[idx]->parameters()->repeat;

  ret = write(c_fd, &evt, sizeof(struct input_event));
  if (ret != sizeof(struct input_event)) {
    QMessageBox::critical(nullptr, "FFB Device", "Effect could not have been started, error code: " + QString::number(ret));
    qDebug() << "Effect not started" << ret;
    delete kernelEff;
    return false;
  }

  m_effects[idx]->setStatus(FFBEffect::FFBEffectStatus::PLAYING);

  delete kernelEff;
  return true;
}

bool FFBDevice::stopEffect(const int idx)
{
  if (m_effects[idx] == nullptr)
    return true;

  if (m_effects[idx]->status() != FFBEffect::FFBEffectStatus::PLAYING)
    return true;

  int internalIdx = m_effects[idx]->internalIdx();

  struct input_event evt;
  evt.type = EV_FF;
  evt.code = internalIdx;
  evt.value = 0;

  int ret = write(c_fd, &evt, sizeof(struct input_event));
  if (ret != sizeof(struct input_event))
    return false;

  m_effects[idx]->setStatus(FFBEffect::FFBEffectStatus::STOPPED);
  return true;
}

int FFBDevice::uploadEffect(struct ff_effect* effect)
{
  int ret = ioctl(c_fd, EVIOCSFF, effect);
  if (ret < 0) {
    qDebug() << "Error while uploading effect";
    return ret;
  }

  return effect->id;
}
