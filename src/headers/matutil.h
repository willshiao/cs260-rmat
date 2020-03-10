#ifndef SRC_HEADERS_MATUTIL_H_
#define SRC_HEADERS_MATUTIL_H_

#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>

using boost::numeric::ublas::matrix;
typedef matrix<char> AdjMatrix;

namespace will {
namespace matutil {

void writeAdjMatrix(const AdjMatrix &m, std::ostream &os);


}  // namespace matutil
}  // namespace will
#endif  // SRC_HEADERS_MATUTIL_H_
