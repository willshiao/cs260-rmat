#include <ostream>
#include "headers/matutil.h"

namespace will {
namespace matutil {
void addSelf(size_t n, std::ostream &os) {
  for (size_t i = 0; i < n; ++i)
    os << i << " " << i << "\n";
}

void writeAdjMatrix(const CustomMatrix &m, std::ostream &os) {
  os << "Source Target\n";
  addSelf(m.size1(), os);
  for (size_t i = 0; i < m.size1(); ++i) {
    for (size_t j = 0; j < m.size2(); ++j) {
      if (m.get(i, j) > 0) {
        os << i << " " << j << "\n";
      }
    }
  }
  os << std::flush;
}

void writeAdjMatrix(const MatrixWrapper<AdjMatrix> &m, std::ostream &os) {
  os << "Source Target\n";
  addSelf(m.size1(), os);
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
  addSelf(m.size1(), os);
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
  addSelf(m.size1(), os);
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
