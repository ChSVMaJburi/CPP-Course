#pragma once
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

class BigInt {
 public:
  BigInt();
  BigInt(int64_t num);
  BigInt(const std::string&);
  BigInt(const BigInt& other);
  ~BigInt();
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
  BigInt& operator%=(const BigInt& other);
  BigInt operator%(const BigInt& other) const;
  BigInt& operator++();
  BigInt operator++(int);
  BigInt& operator--();
  BigInt operator--(int);

 private:
  void Update();
  unsigned char GetDigit(size_t index) const;
  std::vector<unsigned char> digits_;
  bool negative_ = false;
  const unsigned char kMod = 100;
  const unsigned char kMinDigit = 0;
  const unsigned char kMaxDigit = 9;
  friend std::istream& operator>>(std::istream& in, BigInt& num);
  friend std::ostream& operator<<(std::ostream& out, const BigInt& num);
  friend bool operator==(const BigInt& cur, const BigInt& other);
  friend bool operator<(const BigInt& cur, const BigInt& other);
};
bool operator==(const BigInt& cur, const BigInt& other);
bool operator!=(const BigInt& cur, const BigInt& other);
bool operator<=(const BigInt& cur, const BigInt& other);
bool operator>(const BigInt& cur, const BigInt& other);
bool operator>=(const BigInt& cur, const BigInt& other);
