#ifndef SRC_HEADERS_MATRIX_WRAPPER_H_
#define SRC_HEADERS_MATRIX_WRAPPER_H_

#include <iostream>
#include <memory>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>

template <class T>
class MatrixWrapper {
 protected:
  std::unique_ptr<T> mat;

 public:
  MatrixWrapper(int rows, int cols) : mat(new T(rows, cols)) {}

  inline T* getMat() const {
    return mat.get();
  }

  inline char get(int row, int col) const {
    return (*mat)(row, col);
  }

  inline void set(int row, int col, char val) {
    (*mat)(row, col) = val;
  }

  inline int size1() const {
    return mat->size1();
  }

  inline int size2() const {
    return mat->size2();
  }

  inline void insert(int row, int col, char val) {
    mat->insert_element(row, col, val);
  }
};

#endif  // SRC_HEADERS_MATRIX_WRAPPER_H_
