#pragma once

#include <algorithm>
#include <vector>

template <size_t N, size_t M, typename T = int64_t>
class Matrix {
 public:
  Matrix();
  Matrix(const std::vector<std::vector<T>>& other);
  Matrix(const T& elem);
  Matrix<N, M, T>& operator+=(const Matrix<N, M, T>& other);
  Matrix<N, M, T>& operator-=(const Matrix<N, M, T>& other);
  Matrix<N, M, T>& operator*=(const T& elem);
  Matrix<M, N, T> Transported();
  typename std::enable_if<N == M, T>::type Trace() const;
  T& operator()(size_t i, size_t j);
  T operator()(size_t i, size_t j) const;

 private:
  std::vector<std::vector<T>> data_;
};

template <size_t N, size_t M, typename T = int64_t>
Matrix<N, M, T> operator==(const Matrix<N, M, T>& first,
                           const Matrix<N, M, T>& second);
template <size_t N, size_t M, typename T = int64_t>
Matrix<N, M, T> operator+(const Matrix<N, M, T>& first,
                          const Matrix<N, M, T>& second);
template <size_t N, size_t M, typename T = int64_t>
Matrix<N, M, T> operator-(const Matrix<N, M, T>& first,
                          const Matrix<N, M, T>& second);
template <size_t N, size_t M, typename T = int64_t>
Matrix<N, M, T> operator*(const Matrix<N, M, T>& first, const T& elem);
template <size_t N, size_t M, size_t K, typename T = int64_t>
Matrix<N, K, T> operator*(const Matrix<N, M, T>& first,
                          const Matrix<M, K, T>& second);
