#include <ostream>
#include "headers/matutil.h"

namespace will {
namespace matutil {
void writeAdjMatrix(const MatrixWrapper<AdjMatrix> &m, std::ostream &os) {
  os << "Source Target\n";
  AdjMatrix *M = m.getMat();
  for (size_t i = 0; i < m.size1(); ++i) {
    for (size_t j = 0; j < m.size2(); ++j) {
      // if ((*M)(i, j) > 0) os << i << " " << j << " - " << ((int) (*M)(i, j)) << "\n";
      if (m.get(i, j) > 0) {
        os << i << " " << j << "\n";
      }
    }
  }
  os << std::flush;
}

void writeAdjMatrix(const MatrixWrapper<CompAdjMat> &m, std::ostream &os) {
  os << "Source Target\n";
  for (size_t i = 0; i < m.size1(); ++i) {
    for (size_t j = 0; j < m.size2(); ++j) {
      if (m.get(i, j) > 0) {
        os << i << " " << j << "\n";
      }
    }
  }
  os << std::flush;
}

void writeAdjMatrix(const MatrixWrapper<SparseAdjMat> &m, std::ostream &os) {
  os << "Source Target\n";
  for (size_t i = 0; i < m.size1(); ++i) {
    for (size_t j = 0; j < m.size2(); ++j) {
      if (m.get(i, j) > 0) {
        os << i << " " << j << "\n";
      }
    }
  }
  os << std::flush;
}
}  // namespace matutil
}  // namespace will
