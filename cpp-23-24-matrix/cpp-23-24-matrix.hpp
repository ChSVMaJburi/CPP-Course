#pragma once

#include <algorithm>
#include <vector>

template <size_t N, size_t M, typename T = int64_t>
class Matrix {
 public:
  Matrix() : data_(N, std::vector<T>(M)) {}
  Matrix(const std::vector<std::vector<T>>& other) : data_(other) {}
  Matrix(const T& elem) : data_(N, std::vector<T>(M, elem)) {}

  Matrix<N, M, T>& operator+=(const Matrix<N, M, T>& other);

  Matrix<N, M, T>& operator-=(const Matrix<N, M, T>& other);
  Matrix<N, M, T>& operator*=(const T& elem);

  Matrix<M, N, T> Transposed() const;

  T& operator()(size_t first_index, size_t second_index);
  const T& operator()(size_t first_index, size_t second_index) const;

 private:
  std::vector<std::vector<T>> data_;
};

template <size_t N, typename T>
class Matrix<N, N, T> {
 public:
  Matrix() : data_(N, std::vector<T>(N)) {}
  Matrix(const std::vector<std::vector<T>>& other) : data_(other) {}
  Matrix(const T& elem) : data_(N, std::vector<T>(N, elem)) {}

  Matrix<N, N, T>& operator+=(const Matrix<N, N, T>& other);
  Matrix<N, N, T>& operator-=(const Matrix<N, N, T>& other);
  Matrix<N, N, T>& operator*=(const T& elem);

  Matrix<N, N, T> Transposed() const;
  T Trace() const;

  T& operator()(size_t first_index, size_t second_index);
  const T& operator()(size_t first_index, size_t second_index) const;

 private:
  std::vector<std::vector<T>> data_;
};

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
Matrix<N, K, T> operator*(const Matrix<N, M, T>& first,
                          const Matrix<M, K, T>& second) {
  Matrix<N, K, T> result;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < K; ++j) {
      T sum = first(i, 0) * second(0, j);
      for (size_t k = 1; k < M; ++k) {
        sum += first(i, k) * second(k, j);
      }
      result(i, j) = sum;
    }
  }
  return result;
}
template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator+=(const Matrix<N, M, T>& other) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      data_[i][j] += other(i, j);
    }
  }
  return *this;
}
template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator-=(const Matrix<N, M, T>& other) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      data_[i][j] -= other(i, j);
    }
  }
  return *this;
}
template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator*=(const T& elem) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      data_[i][j] *= elem;
    }
  }
  return *this;
}

template <size_t N, size_t M, typename T>
Matrix<M, N, T> Matrix<N, M, T>::Transposed() const {
  Matrix<M, N, T> other(std::vector<std::vector<T>>(M, std::vector<T>(N)));
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      other(j, i) = data_[i][j];
    }
  }
  return other;
}
template <size_t N, typename T>
T Matrix<N, N, T>::Trace() const {
  T ans = data_[0][0];
  for (size_t i = 1; i < N; ++i) {
    ans += data_[i][i];
  }
  return ans;
}

template <size_t N, size_t M, typename T>
T& Matrix<N, M, T>::operator()(size_t first_index, size_t second_index) {
  return data_[first_index][second_index];
}
template <size_t N, size_t M, typename T>
const T& Matrix<N, M, T>::operator()(size_t first_index,
                                     size_t second_index) const {
  return data_[first_index][second_index];
}
template <size_t N, typename T>
Matrix<N, N, T>& Matrix<N, N, T>::operator+=(const Matrix<N, N, T>& other) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      data_[i][j] += other(i, j);
    }
  }
  return *this;
}
template <size_t N, typename T>
Matrix<N, N, T>& Matrix<N, N, T>::operator-=(const Matrix<N, N, T>& other) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      data_[i][j] -= other(i, j);
    }
  }
  return *this;
}
template <size_t N, typename T>
Matrix<N, N, T>& Matrix<N, N, T>::operator*=(const T& elem) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      data_[i][j] *= elem;
    }
  }
  return *this;
}

template <size_t N, typename T>
Matrix<N, N, T> Matrix<N, N, T>::Transposed() const {
  Matrix<N, N, T> other(data_);
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      other(j, i) = data_[i][j];
    }
  }
  return other;
}
template <size_t N, typename T>
T& Matrix<N, N, T>::operator()(size_t first_index, size_t second_index) {
  return data_[first_index][second_index];
}
template <size_t N, typename T>
const T& Matrix<N, N, T>::operator()(size_t first_index,
                                     size_t second_index) const {
  return data_[first_index][second_index];
}
