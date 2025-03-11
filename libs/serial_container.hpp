#pragma once
#include <algorithm>
#include <cstddef>
#include <memory>

#include "serial_iterator.hpp"

namespace my
{
int const initial_capacity = 10;

template <typename T>
class SerialContainer
{
//    typedef ContainerIterator<T> iterator;
    using iterator = ContainerIterator<T>;
//    typedef ContainerIterator<const T> const_iterator;
    using const_iterator = ContainerIterator<const T>;

   public:
    /**
     * Default constructor for SerialContainer.
     * Initializes the container with an initial capacity of 10 elements of type T.
     */
    SerialContainer()
        : capacity_(initial_capacity), size_(0), region_(std::make_unique<T[]>(capacity_)) {}
    /**
     * Constructor for SerialContainer with specified capacity.
     * Initializes the container with the given capacity and sets the size to 0.
     * Allocates memory for the container to hold the specified capacity of
     * elements.
     *
     * @param capacity Initial capacity of the container.
     */
    explicit SerialContainer(size_t capacity)
        : capacity_(capacity), size_(0), region_(std::make_unique<T[]>(capacity_)) {}

    /**
     * Copy constructor for SerialContainer.
     *
     * This constructor takes another SerialContainer<T> by constant reference and
     * initializes the container with a copy of the other container.
     *
     * @param other The container to be copied.
     */
    SerialContainer(const SerialContainer& other)
        : capacity_(other.capacity_), size_(other.size_)
    {
        region_ = std::make_unique<T[]>(capacity_);
        std::copy(other.region_.get(), other.region_.get() + other.size_, region_.get());
    }
    /**
     * Move constructor for SerialContainer.
     *
     * This constructor takes another SerialContainer<T> by rvalue reference and
     * takes ownership of the memory allocated by the other container.
     *
     * @param other The container to be moved.
     */

     SerialContainer(SerialContainer&& other) noexcept = default;

    /**
     * Constructor for SerialContainer with elements from a std::initializer_list.
     * Initializes the container with the size of the initializer list and allocates memory to hold the elements.
     * Copies the elements from the initializer list to the container.
     *
     * @param elements Initializer list of elements to copy into the container.
     */

    SerialContainer(std::initializer_list<T> elements) : size_(elements.size()), capacity_(elements.size())
    {
        region_ = std::make_unique<T[]>(size_);
        std::copy(elements.begin(), elements.end(), region_.get());
    }

    /**
     * Destructor for SerialContainer.
     *
     * This destructor is responsible for releasing the memory allocated by the
     * container.
     */
    ~SerialContainer() noexcept = default;

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
            capacity_ = other.capacity_;
            size_ = other.size_;
            region_ = std::make_unique<T[]>(capacity_);
            std::copy(other.region_.get(), other.region_.get() + other.size_, region_.get());
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
    SerialContainer& operator=(SerialContainer&& other) noexcept = default;

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
        if (index > size_) {
            throw std::out_of_range("Index out of range");
        }
        if (size_ == capacity_)
        {
            increase_capacity(capacity_ * 2);
        }
        std::copy_backward(region_.get() + index, region_.get() + size_, region_.get() + size_ + 1);
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
        if (index > size_) {
            throw std::out_of_range("Index out of range");
        }
        if (size_ + other.size_ > capacity_) {
            size_t new_capacity = std::max(capacity_ * 2, size_ + other.size_);
            auto new_region = std::make_unique<T[]>(new_capacity);
            std::copy(region_.get(), region_.get() + index, new_region.get());
            std::copy(other.region_.get(), other.region_.get() + other.size_, new_region.get() + index);
            std::copy(region_.get() + index, region_.get() + size_, new_region.get() + index + other.size_);
            region_ = std::move(new_region);
            capacity_ = new_capacity;
        } else {
            std::copy_backward(region_.get() + index, region_.get() + size_, region_.get() + size_ + other.size_);
            std::copy(other.region_.get(), other.region_.get() + other.size_, region_.get() + index);
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
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        std::copy(region_.get() + index + 1, region_.get() + size_, region_.get() + index);
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
        if (index + count > size_) {
            throw std::out_of_range("Index out of range");
        }
        std::copy(region_.get() + index + count, region_.get() + size_, region_.get() + index);
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
        if (new_capacity > capacity_) {
            auto new_region = std::make_unique<T[]>(new_capacity);
            std::copy(region_.get(), region_.get() + size_, new_region.get());
            region_ = std::move(new_region);
            capacity_ = new_capacity;
        }
    }

    void clear() {
        region_ = std::make_unique<T[]>(initial_capacity);
    }

    void resize(size_t new_size) {
        if (new_size > capacity_) {
            increase_capacity(new_size);
        }
        size_ = new_size;
    }

    /**
     * Returns an iterator pointing to the first element of the container.
     *
     * @return An iterator pointing to the first element of the container.
     */
    iterator begin() noexcept { return iterator(region_.get()); }

    const_iterator begin() const noexcept { return const_iterator(region_.get()); }

    iterator end() noexcept { return iterator(region_.get() + size_); }

    const_iterator end() const noexcept { return const_iterator(region_.get() + size_); }

    const_iterator cbegin() const noexcept { return const_iterator(region_.get()); }

    const_iterator cend() const noexcept { return const_iterator(region_.get() + size_); }

    /**
     * Returns an iterator pointing to the first element of the container.
     *
     * @return An iterator pointing to the first element of the container.
     */

    size_t size() const noexcept { return size_; }
    
    
    T& operator[](size_t index) noexcept { return region_[index]; }

    T& at(size_t index)
{
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return region_[index];
}
    
    /**
     * Returns the current capacity of the container.
     *
     * @return The current capacity of the container.
     */
    size_t capacity() const { return capacity_; }

    void swap(SerialContainer& other) noexcept
    {
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
        std::swap(region_, other.region_);
    }

   private:
    size_t capacity_{0};
    size_t size_{0};
    std::unique_ptr<T[]> region_;
};

}  // namespace my