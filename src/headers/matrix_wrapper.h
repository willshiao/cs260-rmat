#ifndef SRC_HEADERS_MATRIX_WRAPPER_H_
#define SRC_HEADERS_MATRIX_WRAPPER_H_

#include <iostream>
#include <memory>
#include <mutex>
#include <cstdio>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>

class CustomMatrix {
 protected:
  size_t n;

 public:
  char *mat;
  explicit CustomMatrix(size_t _n) : n(_n) {
    mat = new char[_n * _n];
    memset(mat, 0, n * n * sizeof(char));
  }
  CustomMatrix(size_t _n, size_t _, size_t __) : CustomMatrix(_n) {}
  ~CustomMatrix() {
    delete[] mat;
  }
  inline char get(size_t row, size_t col) const {
    return mat[row * n + col];
  }
  inline void set(size_t row, size_t col, char val) {
    // std::cout << "Write to " << row << ", " << col << std::endl;
    mat[row * n + col] = val;
  }
  inline size_t size1() const {
    return n;
  }
  inline size_t size2() const {
    return n;
  }
};

template <class T>
class MatrixWrapper {
 protected:
  std::unique_ptr<T> mat;
  std::mutex mat_mut;
  bool useMutex;

 public:
  explicit MatrixWrapper(T *_mat) : mat(_mat) {}
  MatrixWrapper(size_t rows, size_t cols)
    : mat(new T(rows, cols)), useMutex(false) {}
  MatrixWrapper(size_t rows, size_t cols, char st)
    : mat(new T(rows, cols, st)), useMutex(false) {}
  MatrixWrapper(size_t rows, size_t cols, char st, bool _useMutex)
    : mat(new T(rows, cols, st)), useMutex(_useMutex) {}

  inline T* getMat() const {
    return mat.get();
  }

  inline char get(size_t row, size_t col) const {
    return (*mat)(row, col);
  }

  inline void set(size_t row, size_t col, char val) {
    if (useMutex) mat_mut.lock();
    (*mat)(row, col) = val;
    if (useMutex) mat_mut.unlock();
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
