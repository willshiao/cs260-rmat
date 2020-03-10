#ifndef SRC_HEADERS_RMAT_H_
#define SRC_HEADERS_RMAT_H_

#include <random>
#include <iostream>

#include "./matutil.h"
#include "./util.h"

struct RmatConfig {
  double a, b, c, d;
  double totalA, totalB, totalC;

  RmatConfig(double _a, double _b, double _c);
  RmatConfig() : RmatConfig(0.25, 0.25, 0.25) {}
};

void rmat(AdjMatrix &m, int nEdges, const RmatConfig &cfg);

void rmatHelper(AdjMatrix &m, int nEdges, const RmatConfig &cfg, int x0, int y0,
                int x1, int y1);

#endif  // SRC_HEADERS_RMAT_H_
