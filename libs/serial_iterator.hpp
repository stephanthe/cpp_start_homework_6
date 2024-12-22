#pragma once
#include <iterator>

namespace my
{
template <typename ValueType>
class ContainerIterator : public std::iterator<std::random_access_iterator_tag, ValueType>
{
    template <typename T>
    friend class SerialContainer;

   private:
    ContainerIterator(ValueType* p) : p(p) {}

   public:
    ContainerIterator(const ContainerIterator& it) : p(it.p) {}

    bool operator!=(ContainerIterator const& other) const { return p != other.p; }
    bool operator==(ContainerIterator const& other) const { return p == other.p; }
    ValueType& operator*() const { return *p; }
    ValueType& get() { return *p; }

//    typename ContainerIterator::reference get() const { return *p; }

    ContainerIterator& operator++() noexcept
    {
        ++p;
        return *this;
    }

    ContainerIterator operator+=(size_t n) noexcept
    {
        p += n;
        return p;
    }

    ContainerIterator& operator--() noexcept
    {
        --p;
        return *this;
    }

   private:
    ValueType* p;
};
}  // namespace my