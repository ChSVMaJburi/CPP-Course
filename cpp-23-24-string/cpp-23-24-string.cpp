#include "cpp-23-24-string.hpp"

String::String() noexcept = default;

String::String(size_t size, char character) {
  SetCapacity(size + 1);
  size_ = size;
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
  if (&other == this) {
    return *this;
  }
  size_ = 0;
  SetCapacity(other.capacity_);
  size_ = other.size_;
  for (size_t i = 0; i < size_; ++i) {
    str_[i] = other.str_[i];
  }
  if (str_) {
    str_[size_] = '\0';
  }
  return *this;
}

void String::Clear() {
  size_ = 0;
  if (capacity_ != 0) {
    str_[0] = '\0';
  }
}

void String::PushBack(char character) {
  if (size_ + 1 >= capacity_) {
    SetCapacity(std::max<size_t>(1, capacity_) * 2);
  }
  str_[size_++] = character;
  str_[size_] = '\0';
}

void String::PopBack() {
  if (!Empty()) {
    --size_;
    str_[size_] = '\0';
  }
}

void String::Resize(size_t new_size) {
  Reserve(new_size + 1);
  size_ = new_size;
  str_[size_] = '\0';
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
  std::swap(capacity_, other.capacity_);
  std::swap(size_, other.size_);
  std::swap(str_, other.str_);
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

const char* String::Data() const { return str_; }

bool operator<(const String& first, const String& second) {
  size_t sz_min = std::min(first.Size(), second.Size());
  for (size_t i = 0; i < sz_min; ++i) {
    if (first[i] != second[i]) {
      return first[i] < second[i];
    }
  }
  return (sz_min == first.Size());
}

bool operator>(const String& first, const String& second) {
  return second < first;
}

bool operator==(const String& first, const String& second) {
  if (first.Size() != second.Size()) {
    return false;
  }
  for (size_t i = 0; i < first.Size(); ++i) {
    if (first[i] != second[i]) {
      return false;
    }
  }
  return true;
}

bool operator<=(const String& first, const String& second) {
  return first < second || first == second;
}

bool operator>=(const String& first, const String& second) {
  return second <= first;
}

bool operator!=(const String& first, const String& second) {
  return !(first == second);
}

String& String::operator+=(const String& other) {
  const size_t kSize = size_;
  Reserve(size_ + other.size_ + 1);
  size_ += other.Size();
  for (size_t i = kSize; i < size_; ++i) {
    str_[i] = other.str_[i - kSize];
  }
  str_[size_] = '\0';
  return *this;
}

String String::operator+(const String& other) const {
  String third = *this;
  third += other;
  return third;
}

String& String::operator*=(unsigned int times) {
  if (times == 0) {
    *this = String();
    return *this;
  }
  const size_t kSize = size_;
  Reserve(size_ * times + 1);
  size_ *= times;
  for (size_t i = kSize; i < size_; ++i) {
    str_[i] = str_[i - kSize];
  }
  str_[size_] = '\0';
  return *this;
}

String String::operator*(unsigned int times) const {
  String answer = *this;
  return answer *= times;
}

std::vector<String> String::Split(const String& delim) {
  std::vector<String> ans;
  const size_t kSize = delim.Size();
  String cur;
  for (size_t i = 0; i < size_; ++i) {
    bool flag = false;
    if (i + kSize > size_) {
      flag = true;
    } else {
      for (size_t j = 0; j < kSize; ++j) {
        if (str_[i + j] != delim[j]) {
          flag = true;
          break;
        }
      }
    }
    if (!flag) {
      ans.push_back(cur);
      cur.Clear();
      i += kSize - 1;
    } else {
      cur.PushBack(str_[i]);
    }
  }
  ans.push_back(cur);
  return ans;
}

String String::Join(const std::vector<String>& strings) const {
  String ans;
  for (size_t i = 0; i < strings.size(); ++i) {
    ans += strings[i];
    if (i + 1 != strings.size()) {
      ans += *this;
    }
  }
  return ans;
}

void String::SetCapacity(size_t new_cap) {
  if (new_cap == 0) {
    capacity_ = 0;
    delete[] str_;
    str_ = nullptr;
    return;
  }
  char* other = new char[new_cap];
  for (size_t i = 0; i < size_; ++i) {
    other[i] = str_[i];
  }
  delete[] str_;
  str_ = other;
  str_[size_] = '\0';
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
