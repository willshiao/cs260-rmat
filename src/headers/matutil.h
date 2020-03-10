#ifndef SRC_HEADERS_MATUTIL_H_
#define SRC_HEADERS_MATUTIL_H_

#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>

using boost::numeric::ublas::matrix;
using boost::numeric::ublas::mapped_matrix;
using boost::numeric::ublas::compressed_matrix;

typedef matrix<char> AdjMatrix;
typedef mapped_matrix<char> SpaseAdjMat;
typedef compressed_matrix<char> CompAdjMat;

namespace will {
namespace matutil {

void writeAdjMatrix(const AdjMatrix &m, std::ostream &os);

}  // namespace matutil
}  // namespace will
#endif  // SRC_HEADERS_MATUTIL_H_
