#ifndef GLOBALS_H
#define GLOBALS_H

enum class FFBEffectTypes { NONE, CONSTANT, PERIODIC, RAMP, SPRING, FRICTION, DAMPER, RUMBLE, INERTIA };
enum class PeriodicWaveforms { NONE, SQUARE, TRIANGLE, SINE, SAW_UP, SAW_DOWN };

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
