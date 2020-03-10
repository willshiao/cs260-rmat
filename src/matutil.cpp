#include <ostream>
#include "headers/matutil.h"

namespace will {
namespace matutil {
void writeAdjMatrix(const AdjMatrix &m, std::ostream &os) {
  os << "Source Target\n";
  for (unsigned i = 0; i < m.size1(); ++i) {
    for (unsigned j = 0; j < m.size2(); ++j) {
      if (m(i, j) > 0) {
        os << i << " " << j << "\n";
      }
    }
  }
  os << std::flush;
}
}  // namespace matutil
}  // namespace will
