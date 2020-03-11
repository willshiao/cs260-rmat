#ifndef SRC_HEADERS_UTIL_H_
#define SRC_HEADERS_UTIL_H_

#include <cmath>
#include <cstdint>
#include <ostream>

namespace will {
namespace util {

static const double EPS = 0.000001;

bool inline dequal(double a, double b) {
  return fabs(a - b) < EPS;
}

uint32_t inline hash32(uint32_t a) {
  a = (a+0x7ed55d16) + (a << 12);
  a = (a^0xc761c23c) ^ (a >> 19);
  a = (a+0x165667b1) + (a << 5);
  a = (a+0xd3a2646c) ^ (a << 9);
  a = (a+0xfd7046c5) + (a << 3);
  a = (a^0xb55a4f09) ^ (a >> 16);
  return a;
}

// From https://web.archive.org/web/20120720045250/http://www.cris.com/~Ttwang/tech/inthash.htm
uint64_t hash64(uint64_t key) {
  key = (~key) + (key << 21);
  key = key ^ (key >> 24);
  key = (key + (key << 3)) + (key << 8);
  key = key ^ (key >> 14);
  key = (key + (key << 2)) + (key << 4);
  key = key ^ (key >> 28);
  key = key + (key << 31);
  return key;
}

constexpr uint64_t SPLIT_INTERVAL = (1L << 62) - 1;

void splitKey(uint64_t key, uint64_t *a, uint64_t *b,
              uint64_t *c, uint64_t *d) {
  uint64_t diff = key % SPLIT_INTERVAL;
  *a = diff;
  *b = diff + SPLIT_INTERVAL;
  *c = *b + SPLIT_INTERVAL;
  *d = *c + SPLIT_INTERVAL;
}

double inline hash64Prob(uint64_t a) {
  return static_cast<double>(hash64(a)) / 0xFFFFFFFFFFFFFFFF;
}

float inline hash32Prob(uint32_t a) {
  return static_cast<float>(hash32(a)) / 0xFFFFFFFF;
}

}  // namespace util
}  // namespace will

#endif // SRC_HEADERS_UTIL_H_
