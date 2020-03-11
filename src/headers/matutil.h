#ifndef SRC_HEADERS_MATUTIL_H_
#define SRC_HEADERS_MATUTIL_H_

#include <iostream>
#include <list>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include "./matrix_wrapper.h"

using boost::numeric::ublas::matrix;
using boost::numeric::ublas::mapped_matrix;
using boost::numeric::ublas::compressed_matrix;

typedef matrix<char> AdjMatrix;
typedef mapped_matrix<char> SparseAdjMat;
typedef compressed_matrix<char> CompAdjMat;

namespace will {
namespace matutil {

void writeAdjMatrix(const MatrixWrapper<AdjMatrix> &m, std::ostream &os);
void writeAdjMatrix(const MatrixWrapper<CompAdjMat> &m, std::ostream &os);
void writeAdjMatrix(const MatrixWrapper<SparseAdjMat> &m, std::ostream &os);
void writeAdjMatrix(const CustomMatrix &m, std::ostream &os);
void writeAdjMatrix(const EdgeList &l, std::ostream &os);

}  // namespace matutil
}  // namespace will
#endif  // SRC_HEADERS_MATUTIL_H_
