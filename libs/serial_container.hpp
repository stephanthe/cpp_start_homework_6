#pragma once
#include <algorithm>
#include <cstddef>

namespace my
{
int const initial_capacity = 10;

template <typename T>
class SerialContainer
{
  public:
    SerialContainer() : capacity_(initial_capacity), size_(0), region_(new T[capacity_]) {}
    ~SerialContainer() { delete[] region_; }

  private:
    size_t capacity_{0};
    size_t size_{0};
    T *region_{nullptr};
};

} // namespace my