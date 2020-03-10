#ifndef SRC_HEADERS_RMAT_H_
#define SRC_HEADERS_RMAT_H_

#include <algorithm>
#include <random>
#include <iostream>
#include <list>
#include <memory>
#include <utility>
#include <vector>

#include <cilk/cilk.h>
#include <cilk/reducer_list.h>
#include <cilk/cilk_api.h>

#include "./matutil.h"
#include "./matrix_wrapper.h"
#include "./util.h"

using will::util::hashProb;

typedef std::pair<int, int> Edge;

struct RmatConfig {
  double a, b, c, d;
  double totalA, totalB, totalC;

  RmatConfig(double _a, double _b, double _c);
  RmatConfig() : RmatConfig(0.25, 0.25, 0.25) {}
};

void listRmatHelper(cilk::reducer<cilk::op_list_append<Edge>> &red, int nEdges,
                    const RmatConfig &cfg, int x0, int y0, int x1, int y1);

std::list<Edge> listRmat(int n, int nEdges, const RmatConfig &cfg);

template <class T>
void rmat(MatrixWrapper<T> *m, int nEdges, const RmatConfig &cfg) {
  rmatHelper(m, nEdges, cfg, 0, 0, m->size1(), m->size2());
}

template <class T>
void rmatSeq(MatrixWrapper<T> *m, int nEdges, const RmatConfig &cfg) {
  rmatSeqHelper(m, nEdges, cfg, 0, 0, m->size1(), m->size2());
}

template <class T>
void rmatHelper(MatrixWrapper<T> *m, int nEdges, const RmatConfig &cfg,
                int x0, int y0, int x1, int y1) {
  int xMid = (x0 + x1) / 2;
  int yMid = (y0 + y1) / 2;
  int numA = 0, numB = 0, numC = 0, numD = 0;
  int nCells = (x1 - x0) * (y1 - y0);

  if (nCells == 1) {
    // std::cout << "Setting edge at " << y0 << ", " << x0 << std::endl;
    // (*m)(y0, x0) = 1;
    // if (nEdges > 1) std::cout << "Warning: " << nEdges << " wasted edges" << std::endl;
    m->set(y0, x0, 1);
    return;
  }

  // Could cilk_for this
  cilk_for(int i = 0; i < nEdges; ++i) {
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
    // if (nEdges > 4) std::cout << "Warning: " << nEdges << " > 4" << std::endl;
    // std::cout << "Setting 1" << std::endl;
    m->set(y0, x0, 1);
    // std::cout << "Setting 2: (" << y0 << "," << x1 << ")" << std::endl;
    m->set(y0, x1 - 1, 1);
    // std::cout << "Setting 3: (" << y1 << "," << x0 << ")" << std::endl;
    m->set(y1 - 1, x0, 1);
    // std::cout << "Setting 4" << std::endl;
    m->set(y1 - 1, x1 - 1, 1);
  } else if (nCells > 4) {
    cilk_spawn rmatHelper(m, numA, cfg, x0, y0, xMid, yMid);
    cilk_spawn rmatHelper(m, numB, cfg, xMid, y0, x1, yMid);
    cilk_spawn rmatHelper(m, numC, cfg, x0, yMid, xMid, y1);
    rmatHelper(m, numD, cfg, xMid, yMid, x1, y1);
    cilk_sync;
  }
}

template <class T>
void rmatSeqHelper(MatrixWrapper<T> *m, int nEdges, const RmatConfig &cfg,
                int x0, int y0, int x1, int y1) {
  int xMid = (x0 + x1) / 2;
  int yMid = (y0 + y1) / 2;
  int numA = 0, numB = 0, numC = 0, numD = 0;
  int nCells = (x1 - x0) * (y1 - y0);

  if (nCells == 1) {
    m->set(y0, x0, 1);
    // if (nEdges > 1) std::cout << "Warning: " << nEdges << " wasted edges" << std::endl;
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
    if (nEdges > 4) std::cout << "Warning: " << nEdges << " > 4" << std::endl;
    m->set(y0, x0, 1);
    m->set(y0, x1 - 1, 1);
    m->set(y1 - 1, x0, 1);
    m->set(y1 - 1, x1 - 1, 1);
  } else if (nCells > 4) {
    rmatHelper(m, numA, cfg, x0, y0, xMid, yMid);
    rmatHelper(m, numB, cfg, xMid, y0, x1, yMid);
    rmatHelper(m, numC, cfg, x0, yMid, xMid, y1);
    rmatHelper(m, numD, cfg, xMid, yMid, x1, y1);
  }
}

#endif  // SRC_HEADERS_RMAT_H_
