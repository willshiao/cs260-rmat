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
#include <cilk/reducer_opadd.h>
#include <cilk/cilk_api.h>

#include "./matutil.h"
#include "./matrix_wrapper.h"
#include "./util.h"

using will::util::hash32Prob;

struct RmatConfig {
  double a, b, c, d;
  double totalA, totalB, totalC;

  RmatConfig(double _a, double _b, double _c);
  RmatConfig() : RmatConfig(0.25, 0.25, 0.25) {}
};

void listRmatHelper(cilk::reducer<cilk::op_list_append<Edge>> &red,
                    size_t nEdges, const RmatConfig &cfg, size_t x0,
                    size_t y0, size_t x1, size_t y1);

std::list<Edge> listRmat(size_t n, size_t nEdges, const RmatConfig &cfg);

template <class T>
void rmat(T *m, size_t nEdges, const RmatConfig &cfg) {
  rmatHelper(m, nEdges, cfg, 0, 0, m->size1(), m->size2());
}

template <class T>
void rmatSeq(T *m, size_t nEdges, const RmatConfig &cfg) {
  rmatSeqHelper(m, nEdges, cfg, 0, 0, m->size1(), m->size2());
}

template <class T>
void rmatHelper(T *m, size_t nEdges, const RmatConfig &cfg,
                size_t x0, size_t y0, size_t x1, size_t y1) {
  // std::cout << "Call to " << x0 << ", " << y0 << ", " << x1 << ", " << y1 << " with " << nEdges << std::endl;
  if (nEdges == 0) return;
  size_t xMid = (x0 + x1) / 2;
  size_t yMid = (y0 + y1) / 2;

  size_t nCells = (x1 - x0) * (y1 - y0);
  if (nCells == 1) {
    // std::cout << "Setting edge at " << y0 << ", " << x0 << std::endl;
    // (*m)(y0, x0) = 1;
    // if (nEdges > 1) std::cout << "Warning: " << nEdges << " wasted edges" << std::endl;
    m->set(y0, x0, 1);
    return;
  }
  cilk::reducer< cilk::op_add<size_t> > redA(0);
  cilk::reducer< cilk::op_add<size_t> > redB(0);
  cilk::reducer< cilk::op_add<size_t> > redC(0);
  cilk::reducer< cilk::op_add<size_t> > redD(0);

  cilk_for(size_t i = 0; i < nEdges; ++i) {
    double prob = hash32Prob(i);
    if (prob <= cfg.totalA)
      *redA += 1;
    else if (prob <= cfg.totalB)
      *redB += 1;
    else if (prob <= cfg.totalC)
      *redC += 1;
    else
      *redD += 1;
  }
  // Required for some reason, can't use .get_value() directly in recursive call
  size_t numA = redA.get_value();
  size_t numB = redB.get_value();
  size_t numC = redC.get_value();
  size_t numD = redD.get_value();

  if (nCells == 4) {
    if (numA > 0) m->set(y0, x0, 1);
    if (numB > 0) m->set(y0, x1 - 1, 1);
    if (numC > 0) m->set(y1 - 1, x0, 1);
    if (numD > 0) m->set(y1 - 1, x1 - 1, 1);
  } else if (nCells > 4) {
    cilk_spawn rmatHelper(m, numA, cfg, x0, y0, xMid, yMid);
    cilk_spawn rmatHelper(m, numB, cfg, xMid, y0, x1, yMid);
    cilk_spawn rmatHelper(m, numC, cfg, x0, yMid, xMid, y1);
    rmatHelper(m, numD, cfg, xMid, yMid, x1, y1);
    cilk_sync;
  }
}

template <class T>
void rmatSeqHelper(T *m, size_t nEdges, const RmatConfig &cfg,
                size_t x0, size_t y0, size_t x1, size_t y1) {
  if (nEdges == 0) return;
  size_t xMid = (x0 + x1) / 2;
  size_t yMid = (y0 + y1) / 2;
  size_t numA = 0, numB = 0, numC = 0, numD = 0;
  size_t nCells = (x1 - x0) * (y1 - y0);

  if (nCells == 1) {
    m->set(y0, x0, 1);
    // if (nEdges > 1) std::cout << "Warning: " << nEdges << " wasted edges" << std::endl;
    return;
  }

  // Could cilk_for this
  for (size_t i = 0; i < nEdges; ++i) {
    double prob = hash32Prob(static_cast<uint32_t>(i));
    if (prob <= cfg.totalA)
      numA++;
    else if (prob <= cfg.totalB)
      numB++;
    else if (prob <= cfg.totalC)
      numC++;
    else
      numD++;
  }
  // std::cout << numA << ", " << numB << ", " << numC << ", " << numD << std::endl;

  if (nCells == 4) {
    // if (nEdges > 4) std::cout << "Warning: " << nEdges << " > 4" << std::endl;
    if (numA > 0) m->set(y0, x0, 1);
    if (numB > 0) m->set(y0, x1 - 1, 1);
    if (numC > 0) m->set(y1 - 1, x0, 1);
    if (numD > 0) m->set(y1 - 1, x1 - 1, 1);
  } else if (nCells > 4) {
    rmatSeqHelper(m, numA, cfg, x0, y0, xMid, yMid);
    rmatSeqHelper(m, numB, cfg, xMid, y0, x1, yMid);
    rmatSeqHelper(m, numC, cfg, x0, yMid, xMid, y1);
    rmatSeqHelper(m, numD, cfg, xMid, yMid, x1, y1);
  }
}

#endif  // SRC_HEADERS_RMAT_H_
