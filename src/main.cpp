#include <iostream>

#include "../libs/serial_container.hpp"

template <typename T>
std::ostream& operator<<(std::ostream& ostream, const my::SerialContainer<T>& container)
{
    for (const auto i : container)
    {
        ostream << i << " ";
    }
    ostream << "   size:" << container.size() << "   capacity:" << container.capacity() << "\n";
    return ostream;
};

int main(int argc, char* argv[])
{
    {
        my::SerialContainer<int> container;
        std::cout << "Default constructor:\n";
        std::cout << container << "\n";
    }
    {
        my::SerialContainer<int> container(100);
        std::cout << "Constructor with capacity 100:\n";
        std::cout << container << std::endl;
        std::cout << "Pushing back 10 elements:\n";
        for (size_t i = 0; i < 10; ++i)
        {
            container.push_back(i);
        }
        std::cout << container << "\n";
    }

    my::SerialContainer<int> container{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << "Constructor with initializer list:\n";
    std::cout << container << "\n";

    std::cout << "Erasing elements 3, 5, 7:\n";
    container.erase(6);
    container.erase(4);
    container.erase(2);
    std::cout << container << "\n";

    std::cout << "Inserting element 10 to start:\n";
    container.insert(10, 0);
    std::cout << container << "\n";

    std::cout << "Inserting element 20 to middle:\n";
    container.insert(20, container.size() / 2);
    std::cout << container << "\n";

    std::cout << "Inserting element 30 to end:\n";
    container.insert(30, container.size());
    std::cout << container << "\n";
    {
        std::cout << "Inserting other container {31, 32, 33}:\n";
        my::SerialContainer<int> container2{31, 32, 33};
        container.insert(container2, 5);
        std::cout << container << "\n";
    }
    std::cout << "Erasing 3 elements from position 2:\n";
    container.erase(2, 3);
    std::cout << container << "\n";

    std::cout << "Accessing elements with iterators and *iter:\n";
    for (auto iter = container.cbegin(); iter != container.cend(); ++iter)
    {
        std::cout << *iter << " ";
    }
    std::cout << "\n\n";
    std::cout << "Accessing elements with iterators and iter.get():\n";
    for (auto iter = container.begin(); iter != container.end(); ++iter)
    {
        std::cout << iter.get() << " ";
    }
    std::cout << "\n\n";
    std::cout << "auto iter : container:\n";
    for (const auto iter : container)
    {
        std::cout << iter << " ";
    }

    std::cout << "\n\n";
    std::cout << "container.begin() = 22:\n";
    auto my_iter = container.begin();
    *my_iter = 22;
    std::cout << container << "\n";

    std::cout << "std::advance(my_iter,4) = 44:\n";
    std::advance(my_iter, 4);
    *my_iter = 44;
    std::cout << container << "\n";

    std::cout << "std::advance(my_iter,-3) = 66:\n";
    std::advance(my_iter, -3);
    *my_iter = 66;
    std::cout << container << "\n";

    std::cout << "container[5] = 55:\n";
    container[5] = 55;
    std::cout << container << "\n";

    std::cout << "container[5] = " << container[5] << "\n";
}
