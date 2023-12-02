#pragma once
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

class BigInt {
 public:
  BigInt();
  BigInt(const int64_t& num);
  BigInt(const std::string&);
  BigInt(const BigInt& other);
  ~BigInt();
  bool operator==(const BigInt& other) const;
  bool operator!=(const BigInt& other) const;
  bool operator<(const BigInt& other) const;
  bool operator<=(const BigInt& other) const;
  bool operator>(const BigInt& other) const;
  bool operator>=(const BigInt& other) const;
  BigInt& operator=(const BigInt& other);
  BigInt& operator-();
  BigInt& operator+=(const BigInt& other);
  BigInt operator+(const BigInt& other) const;
  BigInt& operator-=(const BigInt& other);
  BigInt operator-(const BigInt& other) const;
  BigInt& operator*=(const BigInt& other);
  BigInt operator*(const BigInt& other) const;
  BigInt& operator/=(const BigInt& other);
  BigInt operator/(const BigInt& other) const;
  BigInt& operator++();
  BigInt operator++(int);
  BigInt& operator--();
  BigInt operator--(int);
 private:
  void NotMinusZero();
  std::pair<std::vector<short>, bool> GetDigits(int64_t num) const;
  std::vector<short> digits_;
  bool negative_ = 0;
  const short kTen = 10;
  const short kMinDigit = 0;
  const short kMaxDigit = 9;
  friend std::istream& operator>>(std::istream& in, BigInt& num);
  friend std::ostream& operator<<(std::ostream& out, const BigInt& num);
};
