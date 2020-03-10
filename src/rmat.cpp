#include "headers/rmat.h"
#include "headers/util.h"
#include <boost/numeric/ublas/matrix.hpp>

using boost::numeric::ublas::matrix;
using will::util::hashProb;

RmatConfig::RmatConfig(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {
  d = _a + _b + _c;
  totalA = _a;
  totalB = totalA + _b;
  totalC = totalB + _c;
  if (d < 0) {
    std::cout << "Warning: a + b + c > 1" << std::endl;
  }
}

void rmat(AdjMatrix *m, int nEdges, const RmatConfig &cfg) {
  rmatHelper(m, nEdges, cfg, 0, 0, m->size1(), m->size2());
}

void rmatHelper(AdjMatrix *m, int nEdges, const RmatConfig &cfg, int x0, int y0,
                int x1, int y1) {
  int xMid = (x0 + x1) / 2;
  int yMid = (y0 + y1) / 2;
  int numA = 0, numB = 0, numC = 0, numD = 0;
  int nCells = (x1 - x0) * (y1 - y0);

  if (nCells == 1) {
    // std::cout << "Setting edge at " << y0 << ", " << x0 << std::endl;
    (*m)(y0, x0) = 1;
    return;
  }

  // Could cilk_for this
  for (int i = 0; i < nEdges; ++i) {
    double prob = hashProb(i);
    if (prob <= cfg.totalA)
      numA++;
    else if (prob <= cfg.totalB)
      numB++;
    else if (prob <= cfg.totalC)
      numC++;
    else
      numD++;
  }
  if (nCells == 4) {
    // std::cout << "Setting 1" << std::endl;
    (*m)(y0, x0) = numA;
    // std::cout << "Setting 2: (" << y0 << "," << x1 << ")" << std::endl;
    (*m)(y0, x1 - 1) = numB;
    // std::cout << "Setting 3: (" << y1 << "," << x0 << ")" << std::endl;
    (*m)(y1 - 1, x0) = numC;
    // std::cout << "Setting 4" << std::endl;
    (*m)(y1 - 1, x1 - 1) = numD;
  } else if (nCells > 4) {
    rmatHelper(m, numA, cfg, x0, y0, xMid, yMid);
    rmatHelper(m, numB, cfg, xMid, y0, x1, yMid);
    rmatHelper(m, numC, cfg, x0, yMid, xMid, y1);
    rmatHelper(m, numD, cfg, xMid, yMid, x1, y1);
  }
}
