#ifndef GLOBALS_H
#define GLOBALS_H

#define APP_NAME "FFBChecker"
static const int APP_VERSION_MAJOR(0);
static const int APP_VERSION_MINOR(2);
static const char APP_VERSION_REL('b');

enum class FFBEffectTypes { NONE, CONSTANT, PERIODIC, RAMP, CONDITION, RUMBLE};
enum class PeriodicWaveforms { NONE, SQUARE, TRIANGLE, SINE, SAW_UP, SAW_DOWN };
enum class ConditionSubtypes { NONE, SPRING, FRICTION, DAMPER, INERTIA };

template<typename T> inline bool checkBoundsInclusive(const T& val, const T& min, const T& max)
{
  if (val >= min && val <= max)
    return true;
  else
    return false;
}

template<typename T> inline bool checkBoundsExclusive(const T& val, const T& min, const T& max)
{
  if (val > min && val < max)
    return true;
  else
    return false;
}

#endif // GLOBALS_H
