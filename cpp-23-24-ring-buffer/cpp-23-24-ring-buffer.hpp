#pragma once

#include <cstddef>
#include <vector>

class RingBuffer {
 public:
  explicit RingBuffer(size_t capacity) : left_(0), size_(0), arr_(capacity) {}

  size_t Size() const { return size_; }

  bool Empty() const { return size_ == 0; }

  bool TryPush(int element) {
    if (Size() == arr_.size()) {
      return false;
    }
    std::size_t right = (left_ + size_) % arr_.size();
    arr_[right] = element;
    ++size_;
    return true;
  }

  bool TryPop(int* element) {
    if (Empty()) {
      return false;
    }
    *element = arr_[left_];
    ++left_;
    if (left_ == arr_.size()) {
      left_ = 0;
    }
    --size_;
    return true;
  }

 private:
  std::vector<int> arr_;
  std::size_t left_;
  std::size_t size_;
};