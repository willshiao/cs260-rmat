#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "headers/util.h"
#include "headers/rmat.h"
#include "headers/matutil.h"
#include "headers/matrix_wrapper.h"
#include "headers/timer.h"

using namespace std;
using namespace boost::numeric::ublas;

int main() {
  // AdjMatrix *m = new AdjMatrix(1005, 1005);
  // {
  //   timer t;
  //   MatrixWrapper<SparseAdjMat> *w = new MatrixWrapper<SparseAdjMat>(5005, 5005);
  //   RmatConfig cfg(0.45, 0.15, 0.15);
  //   t.start();
  //   rmat<SparseAdjMat>(w, 55571, cfg);
  //   t.stop();
  //   cout << "Took: " << t.get_total() << endl;
  // }

  timer t;
  MatrixWrapper<AdjMatrix> *w = new MatrixWrapper<AdjMatrix>(30000, 30000);
  RmatConfig cfg(0.45, 0.15, 0.15);
  t.start();
  rmat<AdjMatrix>(w, 50557100, cfg);
  t.stop();
  cout << w->getMat() << endl;
  cout << "Took: " << t.get_total() << endl;

  {
    timer t;
    MatrixWrapper<AdjMatrix> *w = new MatrixWrapper<AdjMatrix>(30000, 30000);
    RmatConfig cfg(0.45, 0.15, 0.15);
    t.start();
    rmatSeq<AdjMatrix>(w, 50557100, cfg);
    t.stop();
    cout << w->getMat() << endl;
    cout << "Took: " << t.get_total() << endl;
  }

  {
    timer t;
    RmatConfig cfg(0.45, 0.15, 0.15);
    t.start();
    auto res = listRmat(30000, 50557100, cfg);
    t.stop();
    cout << res.size() << endl;
    cout << "Took: " << t.get_total() << endl;
  }


  // will::matutil::writeAdjMatrix(*w, std::cout);
  // std::cout << m << std::endl;
  // MatrixWrapper<CompAdjMat> w(10, 10);
  // w.insert(3, 3, 9);
  // w.set(1, 1, 9);
  // cout << static_cast<int>(w.get(3, 3)) << endl;
  // m = w.getMat();
  // will::matutil::writeAdjMatrix(*m, std::cout);
}
