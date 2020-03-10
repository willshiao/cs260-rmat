#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "headers/util.h"
#include "headers/rmat.h"
#include "headers/matutil.h"

using namespace std;
using namespace boost::numeric::ublas;

int main() {
  AdjMatrix m(1005, 1005);
  RmatConfig cfg(0.45, 0.15, 0.15);
  rmat(m, 25571, cfg);
  will::matutil::writeAdjMatrix(m, std::cout);
  // std::cout << m << std::endl;
}
