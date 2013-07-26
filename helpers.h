#ifndef HELPERS_H
#define HELPERS_H

static inline int bitsToLongs(unsigned long bits)
{
  return (bits + 8 * sizeof(unsigned long) - 1) / (8 *sizeof(unsigned long));
}

#endif // HELPERS_H
