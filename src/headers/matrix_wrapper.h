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
  explicit MatrixWrapper(T *_mat) : mat(_mat) {}
  MatrixWrapper(size_t rows, size_t cols) : mat(new T(rows, cols)) {}
  MatrixWrapper(size_t rows, size_t cols, char st)
    : mat(new T(rows, cols, st)) {}

  inline T* getMat() const {
    return mat.get();
  }

  inline char get(size_t row, size_t col) const {
    return (*mat)(row, col);
  }

  inline void set(size_t row, size_t col, char val) {
    (*mat)(row, col) = val;
  }

  inline size_t size1() const {
    return mat->size1();
  }

  inline size_t size2() const {
    return mat->size2();
  }

  inline void insert(size_t row, size_t col, char val) {
    mat->insert_element(row, col, val);
  }
};

#endif  // SRC_HEADERS_MATRIX_WRAPPER_H_
