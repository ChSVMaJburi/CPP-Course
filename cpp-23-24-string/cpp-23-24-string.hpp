#pragma once

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

class String {
 public:
  String() noexcept;
  String(size_t size, char character);
  String(const char* str);
  String(const String& other);
  ~String();
  String& operator=(const String& other);
  void Clear();
  void PushBack(char character);
  void PopBack();
  void Resize(size_t new_size);
  void Resize(size_t new_size, char character);
  void Reserve(size_t new_cap);
  void ShrinkToFit();
  void Swap(String& other);
  char& operator[](size_t ind);
  char operator[](size_t ind) const;
  char& Front();
  char Front() const;
  char& Back();
  char Back() const;
  size_t Size() const;
  bool Empty() const;
  size_t Capacity() const;
  const char* Data() const;
  String& operator+=(const String& other);
  String& operator*=(unsigned int times);
  std::vector<String> Split(const String& delim = " ");
  String Join(const std::vector<String>& strings) const;

 private:
  void SetCapacity(size_t new_cap);
  char* str_ = nullptr;
  size_t capacity_ = 0;
  size_t size_ = 0;
};

bool operator<(const String& first, const String& second);
bool operator<=(const String& first, const String& second);
bool operator>(const String& first, const String& second);
bool operator>=(const String& first, const String& second);
bool operator==(const String& first, const String& second);
bool operator!=(const String& first, const String& second);
String operator+(const String& first, const String& second);
String operator*(const String& first, unsigned int times);

std::ostream& operator<<(std::ostream& out, const String& str);
std::istream& operator>>(std::istream& in, String& str);
