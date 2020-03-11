#include "headers/rmat.h"
#include "headers/util.h"
#include <boost/numeric/ublas/matrix.hpp>

using boost::numeric::ublas::matrix;
using will::util::hash32Prob;

RmatConfig::RmatConfig(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {
  d = _a + _b + _c;
  totalA = _a;
  totalB = totalA + _b;
  totalC = totalB + _c;
  if (d < 0) {
    std::cout << "Warning: a + b + c > 1" << std::endl;
  }
}

std::list<Edge> listRmat(size_t n, size_t nEdges, const RmatConfig &cfg) {
  cilk::reducer<cilk::op_list_append<Edge>> red;
  listRmatHelper(red, nEdges, cfg, 0, 0, n, n);
  const std::list<Edge> &edgeList = red.get_value();
  // std::vector<Edge> out(edgeList.size());
  // std::copy(edgeList.begin(), edgeList.end(), out.begin());
  return std::move(edgeList);
}

void listRmatHelper(cilk::reducer<cilk::op_list_append<Edge>> &red, size_t nEdges,
                    const RmatConfig &cfg, size_t x0, size_t y0, size_t x1, size_t y1) {
  size_t xMid = (x0 + x1) / 2;
  size_t yMid = (y0 + y1) / 2;
  size_t numA = 0, numB = 0, numC = 0, numD = 0;
  size_t nCells = (x1 - x0) * (y1 - y0);

  if (nCells == 1) {
    red->push_back({y0, x0});
    return;
  }

  // Could cilk_for this
  cilk_for(size_t i = 0; i < nEdges; ++i) {
    double prob = hash32Prob(i);
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
    red->push_back({ y0, x0 });
    red->push_back({ y0, x1 - 1 });
    red->push_back({ y1 - 1, x0 });
    red->push_back({ y1 - 1, x1 - 1 });
  } else if (nCells > 4) {
    cilk_spawn listRmatHelper(red, numA, cfg, x0, y0, xMid, yMid);
    cilk_spawn listRmatHelper(red, numB, cfg, xMid, y0, x1, yMid);
    cilk_spawn listRmatHelper(red, numC, cfg, x0, yMid, xMid, y1);
    listRmatHelper(red, numD, cfg, xMid, yMid, x1, y1);
    cilk_sync;
  }
}
