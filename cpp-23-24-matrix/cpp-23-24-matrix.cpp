#include "cpp-23-24-matrix.hpp"

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix() {
  data_.resize(N, std::vector<T>(M, T()));
}
template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(const std::vector<std::vector<T>>& other) {
  data_ = other;
}
template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(const T& elem) {
  data_.resize(N, std::vector<T>(M, elem));
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator+=(const Matrix<N, M, T>& other) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      data_[i][j] += other(i, j);
    }
  }
}
template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator-=(const Matrix<N, M, T>& other) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      data_[i][j] -= other(i, j);
    }
  }
}
template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator*=(const T& elem) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      data_[i][j] *= elem;
    }
  }
}

template <size_t N, size_t M, typename T>
T& Matrix<N, M, T>::operator()(size_t i, size_t j) {
  return data_[i][j];
}
template <size_t N, size_t M, typename T>
T Matrix<N, M, T>::operator()(size_t i, size_t j) const {
  return data_[i][j];
}

template <size_t N, size_t M, typename T>
Matrix<M, N, T> Matrix<N, M, T>::Transported() {
  std::vector<std::vector<T>> other(M, std::vector<T>(N));
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      other[j][i] = data_[i][j];
    }
  }
  return Matrix(other);
}
template <size_t N, size_t M, typename T>
typename std::enable_if<N == M, T>::type Matrix<N, M, T>::Trace() const {
  T ans{};
  for (size_t i = 0; i < N; ++i) {
    ans += data_[i][i];
  }
  return ans;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator==(const Matrix<N, M, T>& first,
                           const Matrix<N, M, T>& second) {
  return first.data_ == second.data_;
}
template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator+(const Matrix<N, M, T>& first,
                          const Matrix<N, M, T>& second) {
  auto third = first;
  third += second;
  return third;
}
template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator-(const Matrix<N, M, T>& first,
                          const Matrix<N, M, T>& second) {
  auto third = first;
  third -= second;
  return third;
}
template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator*(const Matrix<N, M, T>& first, const T& elem) {
  auto third = first;
  third *= elem;
  return third;
}
template <size_t N, size_t M, size_t K, typename T>
Matrix<N, M, T> operator*(const Matrix<N, M, T>& first,
                          const Matrix<M, K, T>& second) {
  auto third = first;
  third *= second;
  return third;
}
