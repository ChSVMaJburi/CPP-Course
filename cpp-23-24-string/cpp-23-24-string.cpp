#include "cpp-23-24-string.hpp"

#include <string.h>

#include <iostream>
#include <vector>

String::String() noexcept {
  capacity_ = 0;
  size_ = 0;
  str_ = nullptr;
}

String::String(size_t size, char character) {
  size_ = size;
  Reserve(size_ + 1);
  for (size_t i = 0; i < size; ++i) {
    str_[i] = character;
  }
}
String::String(const char* str) {
  if (str == nullptr) {
    return;
  }
  SetCapacity(strlen(str) + 1);
  size_ = strlen(str);
  for (size_t i = 0; i < size_; ++i) {
    str_[i] = str[i];
  }
}
String::String(const String& other) : String(other.str_) {}
String::~String() { delete[] str_; }
String& String::operator=(const String& other) {
  size_ = other.size_;
  capacity_ = other.capacity_;
  delete[] str_;
  str_ = new char[capacity_];
  for (size_t i = 0; i < size_; ++i) {
    str_[i] = other.str_[i];
  }
  return *this;
}
void String::Clear() { size_ = 0; }
void String::PushBack(char character) {
  if (size_ + 1 >= capacity_) {
    SetCapacity(capacity_ * 2);
  }
  str_[size_++] = character;
}
void String::PopBack() {
  if (!Empty()) {
    --size_;
  }
}
void String::Resize(size_t new_size) {
  Reserve(new_size + 1);
  size_ = new_size;
}
void String::Resize(size_t new_size, char character) {
  size_t old_size = size_;
  Resize(new_size);
  for (size_t i = old_size; i < new_size; ++i) {
    str_[i] = character;
  }
}
void String::Reserve(size_t new_cap) {
  if (new_cap > capacity_) {
    SetCapacity(new_cap);
  }
}
void String::ShrinkToFit() { SetCapacity(size_); }
void String::Swap(String& other) {
  String third = *this;
  *this = other;
  other = third;
}
char& String::operator[](size_t ind) { return str_[ind]; }
char String::operator[](size_t ind) const { return str_[ind]; }
char& String::Front() { return str_[0]; }
char String::Front() const { return str_[0]; }
char& String::Back() { return str_[size_ - 1]; }
char String::Back() const { return str_[size_ - 1]; }
size_t String::Size() const { return size_; }
bool String::Empty() const { return size_ == 0; }
size_t String::Capacity() const { return capacity_; }
const char* String::Data() { return str_; }
bool String::operator<(const String& other) const {
  size_t sz_min = std::min(size_, other.size_);
  for (size_t i = 0; i < sz_min; ++i) {
    if (str_[i] < other.str_[i]) {
      return true;
    } else if (str_[i] > other.str_[i]) {
      return false;
    }
  }
  return (sz_min == size_);
}
bool String::operator>(const String& other) const { return other < *this; }
bool String::operator==(const String& other) const {
  if (other.size_ != size_) {
    return false;
  }
  for (size_t i = 0; i < size_; ++i) {
    if (str_[i] != other.str_[i]) {
      return false;
    }
  }
  return true;
}
bool String::operator<=(const String& other) const {
  return *this < other || *this == other;
}
bool String::operator>=(const String& other) const { return other <= *this; }
bool String::operator!=(const String& other) const { return !(*this == other); }
String& String::operator+=(const String& other) {
  size_t old_size = size_;
  size_ += other.size_;
  Reserve(size_ + 1);
  for (size_t i = old_size; i < size_; ++i) {
    str_[i] = other.str_[i - old_size];
  }
  return *this;
}
String String::operator+(const String& other) const {
  String third = other;
  third += *this;
  return third;
}
String& String::operator*(unsigned int times) {
  size_t old_size = size_;
  size_ *= times;
  Reserve(size_ + 1);
  for (size_t i = old_size; i < size_; ++i) {
    str_[i] = str_[i - old_size];
  }
  return *this;
}
std::vector<String> String::Split(const String& delim = " ") {
  std::vector<String> ans;
  size_t sz = delim.Size();
  String cur;
  for (size_t i = 0; i < size_; ++i) {
    bool flag = 0;
    if (i + sz >= size_) {
      flag = 1;
    } else {
      for (size_t j = 0; j < sz; ++j) {
        if (str_[i + j] != delim[j]) {
          flag = 1;
          break;
        }
      }
    }
    if (!flag) {
      ans.push_back(cur);
      cur.Clear();
      i += sz - 1;
    } else {
      cur.PushBack(str_[i]);
    }
  }
  ans.push_back(cur);
  return ans;
}
String String::Join(const std::vector<String>& strings) {
  String ans = "";
  for (size_t i = 0; i < strings.size(); ++i) {
    ans += strings[i];
    if (i + 1 != strings.size()) {
      ans += *this;
    }
  }
  return ans;
}
void String::SetCapacity(size_t new_cap) {
  char* other = new char[new_cap];
  for (size_t i = 0; i < size_; ++i) {
    other[i] = str_[i];
  }
  str_ = other;
  for (size_t i = size_; i < new_cap; ++i) {
    str_[i] = '\0';
  }
  capacity_ = new_cap;
}
std::ostream& operator<<(std::ostream& out, const String& str) {
  for (size_t i = 0; i < str.Size(); ++i) {
    out << str[i];
  }
  return out;
}
std::istream& operator>>(std::istream& in, String& str) {
  str.Clear();
  char character;
  in >> std::noskipws;
  while (in >> character && character != ' ' && character != '\n') {
    str.PushBack(character);
  }
  return in;
}