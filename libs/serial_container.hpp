#pragma once
#include <algorithm>
#include <cstddef>

#include "serial_iterator.hpp"

namespace my
{
int const initial_capacity = 10;

template <typename T>
class SerialContainer
{
    typedef ContainerIterator<T> iterator;
    typedef ContainerIterator<const T> const_iterator;

   public:
    /**
     * Default constructor for SerialContainer.
     * Initializes the container with an initial capacity of 10 elements of type T.
     */
    SerialContainer()
        : capacity_(initial_capacity), size_(0), region_(new T[capacity_]) {}
    /**
     * Constructor for SerialContainer with specified capacity.
     * Initializes the container with the given capacity and sets the size to 0.
     * Allocates memory for the container to hold the specified capacity of
     * elements.
     *
     * @param capacity Initial capacity of the container.
     */
    SerialContainer(size_t capacity)
        : capacity_(capacity), size_(0), region_(new T[capacity_]) {}

    /**
     * Copy constructor for SerialContainer.
     *
     * This constructor takes another SerialContainer<T> by constant reference and
     * initializes the container with a copy of the other container.
     *
     * @param other The container to be copied.
     */
    SerialContainer(const SerialContainer& other)
        : capacity_(other.capacity_), size_(other.size_), region_(new T[capacity_])
    {
        std::copy(other.region_, other.region_ + other.size_, region_);
    }
    /**
     * Move constructor for SerialContainer.
     *
     * This constructor takes another SerialContainer<T> by rvalue reference and
     * takes ownership of the memory allocated by the other container.
     *
     * @param other The container to be moved.
     */
    SerialContainer(SerialContainer&& other) noexcept
        : capacity_(other.capacity_), size_(other.size_), region_(other.region_)
    {
        other.region_ = nullptr;
    }
    /**
     * Constructor for SerialContainer with elements from a std::initializer_list.
     * Initializes the container with the size of the initializer list and allocates memory to hold the elements.
     * Copies the elements from the initializer list to the container.
     *
     * @param elements Initializer list of elements to copy into the container.
     */
    SerialContainer(std::initializer_list<T> elements) : size_(elements.size())
    {
        capacity_ = size_;
        region_ = new T[size_];
        std::copy(elements.begin(), elements.end(), region_);
    }

    /**
     * Destructor for SerialContainer.
     *
     * This destructor is responsible for releasing the memory allocated by the
     * container.
     */
    ~SerialContainer() { delete[] region_; }
    /**
     * Copy assignment operator for SerialContainer.
     *
     * This operator takes another SerialContainer<T> by constant reference and
     * assigns the contents of the other container to this container.
     *
     * @param other The container to be copied.
     * @return A reference to this container.
     */
    SerialContainer& operator=(const SerialContainer& other)
    {
        if (this != &other)
        {
            delete[] region_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            region_ = new T[capacity_];
            std::copy(other.region_, other.region_ + other.size_, region_);
        }
        return *this;
    }
    /**
     * Move assignment operator for SerialContainer.
     *
     * This operator takes another SerialContainer<T> by rvalue reference and
     * assigns the contents of the other container to this container, taking
     * ownership of the memory allocated by the other container.
     *
     * @param other The container to be moved.
     * @return A reference to this container.
     */
    SerialContainer& operator=(SerialContainer&& other) noexcept
    {
        if (this != &other)
        {
            delete[] region_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            region_ = other.region_;
            other.region_ = nullptr;
        }
        return *this;
    }

    /**
     * Adds an element to the end of the container.
     *
     * If the container's capacity is exceeded, the capacity is doubled.
     *
     * @param value The value to be added to the container.
     */
    void push_back(const T& value)
    {
        if (size_ == capacity_)
        {
            increase_capacity(capacity_ * 2);
        }
        region_[size_++] = value;
    }
    /**
     * Inserts a value at the specified index in the container.
     *
     * If the container's capacity is exceeded, the capacity is doubled.
     *
     * @param value The value to be inserted into the container.
     * @param index The index at which the value is to be inserted.
     */
    void insert(const T& value, size_t index)
    {
        if (size_ == capacity_)
        {
            increase_capacity(capacity_ * 2);
        }
        std::copy(region_ + index, region_ + size_, region_ + index + 1);
        region_[index] = value;
        size_++;
    }

    /**
     * Inserts all elements from another container at the specified index in the
     * current container.
     *
     * If the total size of the two containers exceeds the current capacity, the
     * capacity is increased to the total size of the two containers.
     *
     * @param other The container from which to insert elements.
     * @param index The index at which to insert the elements.
     */
    void insert(SerialContainer& other, size_t index)
    {
        if (size_ + other.size_ > capacity_)
        {
            size_t new_capacity = std::max(capacity_ * 2, size_ + other.size_);
            T* new_region = new T[new_capacity];
            std::copy(region_, region_ + index, new_region);
            std::copy(other.region_, other.region_ + other.size_, new_region + index);
            std::copy(region_ + index, region_ + size_, new_region + index + other.size_);
            delete[] region_;
            region_ = new_region;
            capacity_ = new_capacity;
        }
        else
        {
            std::copy(region_ + index, region_ + size_, region_ + index + other.size_);
            std::copy(other.region_, other.region_ + other.size_, region_ + index);
        }
        size_ += other.size_;
    }

    /**
     * Removes the element at the specified index from the container.
     *
     * This function shifts all elements after the specified index one position
     * to the left, effectively removing the element at the index.
     *
     * @param index The index of the element to be removed.
     */
    void erase(size_t index)
    {
        std::copy(region_ + index + 1, region_ + size_, region_ + index);
        size_--;
    }
    /**
     * Removes the specified number of elements from the container, starting from the
     * specified index.
     *
     * This function shifts all elements after the specified index one position to the
     * left, effectively removing the elements from the index.
     *
     * @param index The index of the first element to be removed.
     * @param count The number of elements to be removed.
     */
    void erase(size_t index, size_t count)
    {
        std::copy(region_ + index + count, region_ + size_, region_ + index);
        size_ -= count;
    }
    /**
     * Increases the capacity of the container to the specified value.
     *
     * If the new capacity is greater than the current capacity, allocate new memory
     * and copy existing elements to the new memory.
     *
     * @param new_capacity The new capacity of the container.
     */
    void increase_capacity(size_t new_capacity)
    {
        if (new_capacity > capacity_)
        {
            T* new_region = new T[new_capacity];
            std::copy(region_, region_ + size_, new_region);
            delete[] region_;
            region_ = new_region;
            capacity_ = new_capacity;
        }
    }

    T& operator[](size_t index) { return region_[index]; }

    SerialContainer::iterator begin() noexcept
    {
        return SerialContainer::iterator(this->region_);
    }
    SerialContainer::const_iterator begin() const noexcept
    {
        return SerialContainer::const_iterator(region_);
    }
    SerialContainer::iterator end() noexcept
    {
        return SerialContainer::iterator(region_ + size_);
    }
    SerialContainer::const_iterator end() const noexcept
    {
        return const_iterator(region_ + size_);
    }
    SerialContainer::const_iterator cbegin() const noexcept
    {
        return const_iterator(region_);
    }
    SerialContainer::const_iterator cend() const noexcept
    {
        return const_iterator(region_ + size_);
    }
    /**
     * Returns an iterator pointing to the first element of the container.
     *
     * @return An iterator pointing to the first element of the container.
     */

    size_t size() const noexcept { return size_; }
    const T& operator[](size_t index) const noexcept { return region_[index]; }
    size_t capacity() const { return capacity_; }

   private:
    size_t capacity_{0};
    size_t size_{0};
    T* region_{nullptr};
};

}  // namespace my