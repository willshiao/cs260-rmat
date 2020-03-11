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

// constexpr size_t N = 20000;
// constexpr size_t N_EDGES = 4000000;
constexpr size_t N = 1000;
constexpr size_t N_EDGES = 25500;

template <class T>
inline void saveToFile(const string &name, T *mat, timer *t) {
  string fileName = "data/benchmark/" + name + ".csv";
  ofstream ofs;
  ofs.open(fileName, ios::trunc);
  t->start();
  will::matutil::writeAdjMatrix(*mat, ofs);
  t->stop();
}

template <class T>
inline void runWrappedBenchmark(const RmatConfig &cfg, const string &shortname,
                                bool parallel = false, bool useMutex = false) {
  string name = (parallel ? "par_" : "seq_") + shortname;
  cout << "Running " << name << " benchmark" << endl;
  timer t1, t2, t3;
  t1.start();
  T *w = new T(N, N, 0, useMutex);
  t1.stop();
  t2.start();
  if (parallel) rmat<T>(w, N_EDGES, cfg);
  else
    rmatSeq<T>(w, N_EDGES, cfg);
  t2.stop();
  saveToFile<T>(name, w, &t3);
  cout << "Took " << t1.get_total() << " to allocate" << endl;
  cout << "Took " << t2.get_total() << " to run RMAT" << endl;
  cout << "Took " << t3.get_total() << " to save to file" << endl;
}

inline void runListRmat(const RmatConfig &cfg, const string &shortname,
                                bool parallel = true) {
  if (parallel != true)
    cout << "WARNING: no sequential implementation yet" << endl;
  string name = (parallel ? "par_" : "seq_") + shortname;
  cout << "Running " << name << " benchmark" << endl;
  timer t1, t2, t3;
  t1.start();
  std::list<Edge> l;
  t1.stop();
  t2.start();
  l = listRmat(N, N_EDGES, cfg);
  t2.stop();
  EdgeList el(&l, N);
  saveToFile<EdgeList>(name, &el, &t3);
  cout << "Took " << t1.get_total() << " to allocate" << endl;
  cout << "Took " << t2.get_total() << " to run RMAT" << endl;
  cout << "Took " << t3.get_total() << " to save to file" << endl;
}

int main() {
  const RmatConfig cfg(0.57, 0.19, 0.19);

  cout << "===== Running sequential benchmarks =====" << endl;
  runWrappedBenchmark<MatrixWrapper<AdjMatrix>>(cfg, "boost-mat", false);
  // runWrappedBenchmark<MatrixWrapper<CompAdjMat>>(cfg, "compressed-mat", false);
  runWrappedBenchmark<MatrixWrapper<SparseAdjMat>>(cfg, "sparse-mat", false);
  runWrappedBenchmark<CustomMatrix>(cfg, "custom-mat", false);

  cout << "===== Running parallel benchmarks =====" << endl;
  runWrappedBenchmark<MatrixWrapper<AdjMatrix>>(cfg, "boost-mat", true);
  // runWrappedBenchmark<MatrixWrapper<CompAdjMat>>(cfg, "compressed-mat-mut",
                                                //  true, true);
  runWrappedBenchmark<MatrixWrapper<SparseAdjMat>>(cfg, "sparse-mat-mut",
                                                 true, true);
  runWrappedBenchmark<CustomMatrix>(cfg, "custom-mat", true);
  runListRmat(cfg, "custom-list");

  cout << "Done!" << endl;
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
