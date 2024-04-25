#include "cpp-23-24-matrix.hpp"

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator+=(const Matrix<N, M, T>& other) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      data_[i][j] += other(i, j);
    }
  }
  return *this;
}