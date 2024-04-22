#pragma once

#include <algorithm>
#include <vector>

template <size_t N, size_t M, typename T = int64_t>
class Matrix {
 public:
  Matrix() { data_.resize(N, std::vector<T>(M, T())); }
  Matrix(const std::vector<std::vector<T>>& other) { data_ = other; }
  Matrix(const T& elem) { data_.resize(N, std::vector<T>(M, elem)); }

  Matrix<N, M, T>& operator+=(const Matrix<N, M, T>& other) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        data_[i][j] += other(i, j);
      }
    }
    return *this;
  }
  Matrix<N, M, T>& operator-=(const Matrix<N, M, T>& other) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        data_[i][j] -= other(i, j);
      }
    }
    return *this;
  }
  Matrix<N, M, T>& operator*=(const T& elem) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        data_[i][j] *= elem;
      }
    }
    return *this;
  }

  Matrix<M, N, T> Transposed() {
    std::vector<std::vector<T>> other(M, std::vector<T>(N));
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        other[j][i] = data_[i][j];
      }
    }
    return Matrix<M, N, T>(other);
  }

  T& operator()(size_t i, size_t j) { return data_[i][j]; }
  T operator()(size_t i, size_t j) const { return data_[i][j]; }

 private:
  std::vector<std::vector<T>> data_;
};

template <size_t N, typename T>
class Matrix<N, N, T> {
 public:
  Matrix() { data_.resize(N, std::vector<T>(N, T())); }
  Matrix(const std::vector<std::vector<T>>& other) { data_ = other; }
  Matrix(const T& elem) { data_.resize(N, std::vector<T>(N, elem)); }

  Matrix<N, N, T>& operator+=(const Matrix<N, N, T>& other) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        data_[i][j] += other(i, j);
      }
    }
    return *this;
  }
  Matrix<N, N, T>& operator-=(const Matrix<N, N, T>& other) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        data_[i][j] -= other(i, j);
      }
    }
    return *this;
  }
  Matrix<N, N, T>& operator*=(const T& elem) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        data_[i][j] *= elem;
      }
    }
    return *this;
  }

  Matrix<N, N, T> Transposed() {
    std::vector<std::vector<T>> other(N, std::vector<T>(N));
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        other[j][i] = data_[i][j];
      }
    }
    return Matrix(other);
  }
  T Trace() const {
    T ans{};
    for (size_t i = 0; i < N; ++i) {
      ans += data_[i][i];
    }
    return ans;
  }

  T& operator()(size_t i, size_t j) { return data_[i][j]; }
  T operator()(size_t i, size_t j) const { return data_[i][j]; }

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
      T sum = 0;
      for (size_t k = 0; k < M; ++k) {
        sum += first(i, k) * second(k, j);
      }
      result(i, j) = sum;
    }
  }
  return Matrix(result);
}
