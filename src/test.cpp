#include <iostream>
#include <fstream>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "headers/util.h"
#include "headers/rmat.h"
#include "headers/matutil.h"
#include "headers/matrix_wrapper.h"
#include "headers/timer.h"

using namespace std;
using namespace boost::numeric::ublas;

int main(int argc, char** argv) {
  uint64_t n = atol(argv[1]);
  uint64_t m = atol(argv[2]);

  RmatConfig cfg(0.57, 0.19, 0.19);
  CustomMatrix *mat = new CustomMatrix(n);
  timer t;
  t.start();
  rmat<CustomMatrix>(mat, m, cfg);
  t.stop();
  cout << "Took: " << t.get_total() << endl;

  // timer t;
  // t.start();
  // list<Edge> l = listRmat(n, m, cfg);
  // t.stop();
  // cout << "Took: " << t.get_total() << endl;

  // fs.open("data/gen-32bit_uniform.csv", ios::trunc);
  // MatrixWrapper<CustomMatrix> *w = new MatrixWrapper<CustomMatrix>(1024, 1024, 0, true);
  // ofstream fs;
  // timer t;

  // RmatConfig cfg;
  // cout << "Starting now" << endl;

  // rmat<MatrixWrapper<CompAdjMat>>(w, 50000, cfg);
  // rmatSeq<AdjMatrix>(w, 25571, cfg);
  // rmat<CustomMatrix>(x, 5000, cfg);
  // rmatSeq<CustomMatrix>(x, 5000, cfg);
  // cout << "Finished generating graph, writing to file..." << endl;
  // will::matutil::writeAdjMatrix(*w, fs);
  // will::matutil::writeAdjMatrix(*x, fs);
  // cout << "Done!" << endl;

  // {
  //   timer t;
  //   MatrixWrapper<AdjMatrix> *w = new MatrixWrapper<AdjMatrix>(50000, 50000);
  //   RmatConfig cfg(0.57, 0.19, 0.19);
  //   t.start();
  //   rmatSeq<AdjMatrix>(w, 505571000, cfg);
  //   t.stop();
  //   cout << w->getMat() << endl;
  //   cout << "Took: " << t.get_total() << endl;
  // }

  // {
  //   timer t;
  //   RmatConfig cfg(0.57, 0.19, 0.19);
  //   t.start();
  //   std::list<Edge> res = listRmat(30000, 50557100, cfg);
  //   t.stop();
  //   cout << res.size() << endl;
  //   cout << "Took: " << t.get_total() << endl;
  // }


  // will::matutil::writeAdjMatrix(*w, std::cout);
  // std::cout << m << std::endl;
  // MatrixWrapper<CompAdjMat> w(10, 10);
  // w.insert(3, 3, 9);
  // w.set(1, 1, 9);
  // cout << static_cast<int>(w.get(3, 3)) << endl;
  // m = w.getMat();
  // will::matutil::writeAdjMatrix(*m, std::cout);
}
