#ifndef __WILL_RMAT_HEADER__
#define __WILL_RMAT_HEADER__

#include <iostream>
#include <random>
#include <boost/numeric/ublas/matrix.hpp>
#include "./util.h"

using boost::numeric::ublas::matrix;
typedef matrix<int> AdjMatrix;

struct RmatConfig {
  double a, b, c, d;
  double totalA, totalB, totalC;

  RmatConfig (double _a, double _b, double _c);
  RmatConfig () : RmatConfig(0.25, 0.25, 0.25) {}
};

void rmat (AdjMatrix &m, int nEdges, const RmatConfig &cfg);

void rmatHelper (AdjMatrix &m, int nEdges, const RmatConfig &cfg, int x0, int y0, int x1, int y1);

#endif /* __WILL_RMAT_HEADER__ */
