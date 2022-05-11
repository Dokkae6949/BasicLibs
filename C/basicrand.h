#ifndef __BASICRAND_H__
#define __BASICRAND_H__

#include <stdlib.h>


// Returns random value in specific range || For int, char, short, ... types(min:INCLUSIVE; max:EXCLUSIVE)
#define RAND_RANGE(type, field) \
   type randRange_##type(const type min, const type max) \
   {  \
      return (type)((double)rand() / RAND_MAX * (max - min) + min); \
   }
RAND_RANGE(char, x)
RAND_RANGE(short, x)
RAND_RANGE(int, x)
RAND_RANGE(unsigned, x)
RAND_RANGE(long, x)
RAND_RANGE(float, x)
RAND_RANGE(double, x)

#endif