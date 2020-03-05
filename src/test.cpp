#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "headers/util.h"
#include "headers/rmat.h"

using namespace std;
using namespace boost::numeric::ublas;

int main() {
  AdjMatrix m (1024, 1024);
  RmatConfig cfg;
  rmat(m, 10000, cfg);
  std::cout << m << std::endl;
}
