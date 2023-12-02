#include "cpp-23-24-big-integer.hpp"

BigInt::BigInt() {
  digits_.push_back(0);
}
std::pair<std::vector<short>, bool> BigInt::GetDigits(int64_t num) const {
  std::vector<short> digits;
  bool negative = num < 0;
  while (num != 0) {
    digits.push_back(num % kTen);
    if (digits.back() < 0) {
      digits.back() *= -1;
    }
    num /= kTen;
  }
  if (digits.empty()) {
    digits.push_back(0);
  }
  reverse(digits.begin(), digits.end());
  return {digits, negative};
}
BigInt::BigInt(const int64_t& num) {
  auto digits = GetDigits(num);
  negative_ = digits.second;
  digits_ = digits.first;
}
BigInt::BigInt(const std::string& str) {
  size_t start = 0;
  if (str[0] == '-') {
    negative_ = true;
    start = 1;
  }
  for (size_t i = start; i < str.size(); ++i) {
    digits_.push_back(str[i] - '0');
  }
  if (digits_.size() == 1 && digits_.back() == 0) {
    negative_ = false;
  }
}
BigInt::BigInt(const BigInt& other) {
  digits_ = other.digits_;
  negative_ = other.negative_;
}
BigInt::~BigInt() = default;
BigInt& BigInt::operator=(const BigInt& other) {
  digits_ = other.digits_;
  negative_ = other.negative_;
  return *this;
}
bool BigInt::operator==(const BigInt& other) const {
  return digits_ == other.digits_ && other.negative_ == negative_;
}
bool BigInt::operator!=(const BigInt& other) const {
  return !(*this == other);
}
bool BigInt::operator<(const BigInt& other) const {
  if (negative_ && !other.negative_) {
    return true;
  }
  if (!negative_ && other.negative_) {
    return false;
  }
  if (negative_ && other.negative_) {
    BigInt this_ = *this;
    BigInt other_ = other;
    other_.negative_ = false;
    this_.negative_ = false;
    return other_ < this_;
  }
  if (digits_.size() < other.digits_.size()) {
    return true;
  }
  if (digits_.size() > other.digits_.size()) {
    return false;
  }
  return digits_ < other.digits_;
}
bool BigInt::operator<=(const BigInt& other) const {
  return *this < other || *this == other;
}
bool BigInt::operator>(const BigInt& other) const {
  return other < *this;
}
bool BigInt::operator>=(const BigInt& other) const {
  return *this > other || *this == other;
}
void BigInt::NotMinusZero() {
  if (digits_.size() == 1 && digits_[0] == 0) {
    negative_ = false;
  }
}
BigInt& BigInt::operator+=(const BigInt& other_) {
  BigInt other = other_;
  bool ans_neg = false;
  if (negative_) {
    ans_neg = true;
    other.negative_ ^= 1;
    negative_ = false;
  }
  if (other.negative_) {
    other.negative_ = false;
    *this -= other;
    negative_ ^= ans_neg;
    NotMinusZero();
    return *this;
  }
  size_t size_mx = std::max(other.digits_.size(), digits_.size());
  bool add = false;
  std::vector<short> ans;
  for (size_t i = 0; i < size_mx; ++i) {
    short sum = add;
    if (i < digits_.size()) {
      sum += digits_[digits_.size() - 1 - i];
    }
    if (i < other.digits_.size()) {
      sum += other.digits_[other.digits_.size() - 1 - i];
    }
    ans.push_back(sum % kTen);
    add = sum / kTen;
  }
  if (add) {
    ans.push_back(add);
  }
  reverse(ans.begin(), ans.end());
  digits_ = ans;
  negative_ ^= ans_neg;
  NotMinusZero();
  return *this;
}
BigInt BigInt::operator+(const BigInt& other) const {
  BigInt third = *this;
  return third += other;
}
BigInt& BigInt::operator-() {
  negative_ ^= 1;
  NotMinusZero();
  return *this;
}
BigInt& BigInt::operator-=(const BigInt& other_) {
  BigInt other = other_;
  bool ans_neg = false;
  if (negative_) {
    ans_neg = true;
    other.negative_ ^= 1;
    negative_ = false;
  }
  if (other.negative_) {
    other.negative_ = false;
    *this += other;
    negative_ ^= ans_neg;
    NotMinusZero();
    return *this;
  }
  if (*this < other) {
    *this = -(other - *this);
    negative_ ^= ans_neg;
    NotMinusZero();
    return *this;
  }
  bool del = false;
  std::vector<short> ans;
  for (size_t i = 0; i < digits_.size(); ++i) {
    short sum = digits_[digits_.size() - 1 - i];
    if (del) {
      --sum;
      del = false;
    }
    if (i < other.digits_.size()) {
      sum -= other.digits_[other.digits_.size() - 1 - i];
    }
    if (sum < 0) {
      sum += kTen;
      del = true;
    }
    ans.push_back(sum);
  }
  while(ans.size() > 1 && ans.back() == 0) {
    ans.pop_back();
  }
  reverse(ans.begin(), ans.end());
  digits_ = ans;
  negative_ ^= ans_neg;
  NotMinusZero();
  return *this;
}
BigInt BigInt::operator-(const BigInt& other) const {
  BigInt third = *this;
  return third -= other;
}
BigInt& BigInt::operator*=(const BigInt& other) {
  size_t size1 = digits_.size();
  size_t size2 = other.digits_.size();
  std::vector<short> ans(size1 + size2);
  for (size_t i = 0; i < size1; ++i) {
    for (size_t j = 0; j < size2; ++j) {
      ans[i + j] += digits_[size1 - 1 - i] * other.digits_[size2 - 1 - j];
    }
  }
  short add = 0;
  for (auto& cur_num: ans) {
    cur_num += add;
    add = cur_num / kTen;
    cur_num %= kTen;
  }
  while (ans.size() > 1 && ans.back() == 0) {
    ans.pop_back();
  }
  reverse(ans.begin(), ans.end());
  negative_ ^= other.negative_;
  digits_ = ans;
  NotMinusZero();
  return *this;
}
BigInt BigInt::operator*(const BigInt& other) const {
  BigInt third = *this;
  return third *= other;
}
BigInt& BigInt::operator/=(const BigInt& other_) {
  BigInt other = other_;
  if (other == 0) {
    throw std::runtime_error("Деление на ноль");
  }
  bool ans_negative = other.negative_ ^ negative_;
  other.negative_ = negative_ = false;
  BigInt ans = 0;
  BigInt cur_num = 0;
  for (size_t i = 0; i + 1 < other.digits_.size(); ++i) {
    cur_num = cur_num * kTen + digits_[i];
  }
  for (size_t i = other.digits_.size() - 1; i < digits_.size(); ++i) {
    cur_num = cur_num * kTen + digits_[i];
    short left = kMinDigit;
    short right = kMaxDigit;
    while (left < right) {
      short mid = (left + right + 1) >> 1;
      if (other * mid <= cur_num) {
        left = mid;
      } else {
        right = mid - 1;
      }
    }
    cur_num -= other * left;
    ans = ans * 10 + left;
  }
  ans.negative_ = ans_negative;
  *this = ans;
  NotMinusZero();
  return *this;
}
BigInt BigInt::operator/(const BigInt& other) const {
  BigInt third = *this;
  return third /= other;
}
BigInt& BigInt::operator%=(const BigInt& other) { return *this -= *this / other * other; }
BigInt BigInt::operator%(const BigInt& other) const {
  BigInt third = *this;
  return third %= other;
}
BigInt& BigInt::operator++() { return (*this += 1); }
BigInt BigInt::operator++(int) { return ++(*this) - 1; }
BigInt& BigInt::operator--() { return (*this -= 1); }
BigInt BigInt::operator--(int) { return --(*this) + 1; }
std::ostream& operator<<(std::ostream& out, const BigInt& num) {
  if (num.negative_) {
    out << "-";
  }
  for (const auto cur_dig : num.digits_) {
    out << cur_dig;
  }
  return out;
}

std::istream& operator>>(std::istream& in, BigInt& num) {
  std::string tmp;
  in >> tmp;
  num = tmp;
  return in;
}
