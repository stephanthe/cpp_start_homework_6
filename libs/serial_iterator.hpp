#pragma once
#include <cstddef>
#include <iterator>

namespace my {

template <typename T>
class ContainerIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    ContainerIterator(pointer ptr) : ptr_(ptr) {}

    ContainerIterator& operator=(const ContainerIterator& other)=default;
    
    ContainerIterator& operator=(ContainerIterator&& other)=default;

    ~ContainerIterator() = default;
    
    // Операторы сравнения
    bool operator==(const ContainerIterator& other) const { return ptr_ == other.ptr_; }
    bool operator!=(const ContainerIterator& other) const { return !(*this == other); }

    reference operator*() const { return *ptr_; }

    pointer operator->() const { return ptr_; }

    ContainerIterator& operator++() {
        ++ptr_;
        return *this;
    }

        ContainerIterator operator++(int) {
        ContainerIterator temp = *this;
        ++(*this);
        return temp;
    }

        ContainerIterator& operator--() {
        --ptr_;
        return *this;
    }

        ContainerIterator operator--(int) {
        ContainerIterator temp = *this;
        --(*this);
        return temp;
    }

    ContainerIterator& operator+=(difference_type offset) {
        ptr_ += offset;
        return *this;
    }

    ContainerIterator& operator-=(difference_type offset) {
        ptr_ -= offset;
        return *this;
    }

    reference operator[](difference_type index) const { return *(ptr_ + index); }

    bool operator<(const ContainerIterator& other) const { return ptr_ < other.ptr_; }
    bool operator>(const ContainerIterator& other) const { return ptr_ > other.ptr_; }
    bool operator<=(const ContainerIterator& other) const { return !(*this > other); }
    bool operator>=(const ContainerIterator& other) const { return !(*this < other); }


    friend ContainerIterator operator+(ContainerIterator it, difference_type offset) {
        return ContainerIterator(it.ptr_ + offset);
    }
    friend ContainerIterator operator-(ContainerIterator it, difference_type offset) {
        return ContainerIterator(it.ptr_ - offset);
    }

    difference_type operator-(const ContainerIterator& other) const { return ptr_ - other.ptr_; }

private:
    pointer ptr_;
};

}  // namespace my