#include "cpp-23-24-big-integer.hpp"

BigInt::BigInt() : digits_{0} {}

BigInt::BigInt(int64_t num) {
  negative_ = num < 0;
  num *= (num < 0 ? -1 : 1);
  while (num != 0) {
    digits_.push_back(num % kMod);
    num /= kMod;
  }
  if (digits_.empty()) {
    digits_.push_back(0);
  }
  Update();
}

BigInt::BigInt(const std::string& str) { size_t start = 0;
  if (str[0] == '-') {
    negative_ = true;
    start = 1;
  }
  for (int i = str.size(); i >= start; --i) {
    if ((str.size() - i) % 2 == 1) {
      digits_.back() += (str[i] - '0') * 10;
    } else {
      digits_.push_back(str[i] - '0');
    }
    if (i == 0) {
      break;
    }
  }
  Update();
}
BigInt::BigInt(const BigInt& other) : digits_(other.digits_), negative_(other.negative_) {

}
BigInt::~BigInt() = default;
BigInt& BigInt::operator=(const BigInt& other) {
  digits_ = other.digits_;
  negative_ = other.negative_;
  return *this;
}
bool operator==(const BigInt& cur, const BigInt& other) {
  return cur.digits_ == other.digits_ && other.negative_ == cur.negative_;
}
bool operator!=(const BigInt& cur, const BigInt& other) {
  return !(cur == other);
}
bool operator<(const BigInt& cur, const BigInt& other) {
  if (cur.negative_ && !other.negative_) {
    return true;
  }
  if (!cur.negative_ && other.negative_) {
    return false;
  }
  bool flag = (cur.negative_ && other.negative_);
  if (cur.digits_.size() != other.digits_.size()) {
    return (cur.digits_.size() > other.digits_.size()) & flag;
  }
  for (int i = cur.digits_.size() - 1; i >= 0; --i) {
    if (cur.digits_[i] != other.digits_[i]) {
      return cur.digits_[i] < other.digits_[i];
    }
  }
  return false;
}
bool operator<=(const BigInt& cur, const BigInt& other) {
  return cur < other || cur == other;
}
bool operator>(const BigInt& cur, const BigInt& other) { return other < cur; }
bool operator>=(const BigInt& cur, const BigInt& other) {
  return cur > other || cur == other;
}
void BigInt::Update() {
  while (digits_.size() > 1 && digits_.back() == 0) {
    digits_.pop_back();
  }
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
    Update();
    return *this;
  }
  size_t size_mx = std::max(other.digits_.size(), digits_.size());
  bool add = false;
  std::vector<unsigned char> ans;
  for (size_t i = 0; i < size_mx; ++i) {
    unsigned char sum = add;
    if (i < digits_.size()) {
      sum += digits_[i];
    }
    if (i < other.digits_.size()) {
      sum += other.digits_[i];
    }
    ans.push_back(sum % kMod);
    add = sum / kMod;
  }
  if (add) {
    ans.push_back(add);
  }
  digits_ = ans;
  negative_ ^= ans_neg;
  Update();
  return *this;
}
BigInt BigInt::operator+(const BigInt& other) const {
  BigInt third = *this;
  return third += other;
}
BigInt& BigInt::operator-() {
  negative_ ^= 1;
  Update();
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
    Update();
    return *this;
  }
  if (*this < other) {
    *this = -(other - *this);
    negative_ ^= ans_neg;
    Update();
    return *this;
  }
  bool del = false;
  std::vector<unsigned char> ans;
  for (size_t i = 0; i < digits_.size(); ++i) {
    char sum = digits_[i];
    if (del) {
      --sum;
      del = false;
    }
    if (i < other.digits_.size()) {
      sum -= other.digits_[other.digits_.size() - 1 - i];
    }
    if (sum < 0) {
      sum += kMod;
      del = true;
    }
    ans.push_back(sum);
  }
  digits_ = ans;
  negative_ ^= ans_neg;
  Update();
  return *this;
}
BigInt BigInt::operator-(const BigInt& other) const {
  BigInt third = *this;
  return third -= other;
}
BigInt& BigInt::operator*=(const BigInt& other) {
  size_t size1 = digits_.size();
  size_t size2 = other.digits_.size();
  std::vector<unsigned short> ans(size1 + size2);
  for (size_t i = 0; i < size1; ++i) {
    for (size_t j = 0; j < size2; ++j) {
      ans[i + j] += static_cast<unsigned short>(digits_[i]) * other.digits_[j];
    }
  }
  unsigned char add = 0;
  for (auto& cur_num : ans) {
    cur_num += add;
    add = cur_num / kMod;
    cur_num %= kMod;
  }
  negative_ ^= other.negative_;
  digits_.resize(ans.size());
  for (size_t i = 0; i < ans.size(); ++i) {
    digits_[i] = ans[i];
  }
  Update();
  return *this;
}
BigInt BigInt::operator*(const BigInt& other) const {
  BigInt third = *this;
  return third *= other;
}
BigInt& BigInt::operator/=(const BigInt& other_) {
  BigInt other = other_;
  if (other == 0) {
    throw std::runtime_error("Division by zero");
  }
  bool ans_negative = other.negative_ ^ negative_;
  other.negative_ = negative_ = false;
  if (*this < other_) {
    return *this = 0;
  }
  BigInt ans = 0;
  BigInt cur_num = 0;
  for (size_t i = 0; i + 1 < other.digits_.size(); ++i) {
    cur_num = cur_num * kMod + digits_[i];
  }
  for (size_t i = other.digits_.size() - 1; i < digits_.size(); ++i) {
    cur_num = cur_num * kMod + digits_[i];
    unsigned char left = kMinDigit;
    unsigned char right = kMaxDigit;
    while (left < right) {
      unsigned char mid = (left + right + 1) >> 1;
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
  Update();
  return *this;
}
BigInt BigInt::operator/(const BigInt& other) const {
  BigInt third = *this;
  return third /= other;
}
BigInt& BigInt::operator%=(const BigInt& other) {
  return *this -= *this / other * other;
}
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
