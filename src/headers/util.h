#ifndef __WILL_UTIL_H__
#define __WILL_UTIL_H__

#include <cmath>

namespace will {
namespace util {

static const double EPS = 0.000001;

bool inline dequal (double a, double b) {
    return fabs(a - b) < EPS;
}

uint32_t inline hash (uint32_t a) {
   a = (a+0x7ed55d16) + (a<<12);
   a = (a^0xc761c23c) ^ (a>>19);
   a = (a+0x165667b1) + (a<<5);
   a = (a+0xd3a2646c) ^ (a<<9);
   a = (a+0xfd7046c5) + (a<<3);
   a = (a^0xb55a4f09) ^ (a>>16);
   return a;
}

float inline hashProb (uint32_t a) {
    return static_cast<float>(hash(a)) / 0xFFFFFFFF;
}

} // namespace will
} // namespace util

#endif /* __WILL_UTIL_H__ */
