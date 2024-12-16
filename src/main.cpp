#include <iostream>

#include "../libs/serial_container.hpp"

template <typename T>
std::ostream& operator<<(std::ostream& ostream, const my::SerialContainer<T>& container)
{
    for (const auto i : container)
    {
        ostream << i << " ";
    }
    ostream << "   size:" << container.size() << "   capacity:" << container.capacity() << std::endl;
    return ostream;
};

int main(int argc, char* argv[])
{
    {
        my::SerialContainer<int> container;
        std::cout << "Default constructor:" << std::endl;
        std::cout << container << std::endl;
    }
    {
        my::SerialContainer<int> container(100);
        std::cout << "Constructor with capacity 100:" << std::endl;
        std::cout << container << std::endl;
        std::cout << "Pushing back 10 elements:" << std::endl;
        for (size_t i = 0; i < 10; ++i)
        {
            container.push_back(i);
        }
        std::cout << container << std::endl;
    }
    {
        my::SerialContainer<int> container{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::cout << "Constructor with initializer list:" << std::endl;
        std::cout << container << std::endl;

        std::cout << "Erasing elements 3, 5, 7:" << std::endl;
        container.erase(6);
        container.erase(4);
        container.erase(2);
        std::cout << container << std::endl;

        std::cout << "Inserting element 10 to start:" << std::endl;
        container.insert(10, 0);
        std::cout << container << std::endl;

        std::cout << "Inserting element 20 to middle:" << std::endl;
        container.insert(20, container.size() / 2);
        std::cout << container << std::endl;

        std::cout << "Inserting element 30 to end:" << std::endl;
        container.insert(30, container.size());
        std::cout << container << std::endl;

        std::cout << "Inserting other container {31, 32, 33}:" << std::endl;
        my::SerialContainer<int> container2{31, 32, 33};
        container.insert(container2, 5);
        std::cout << container << std::endl;

        std::cout << "Erasing 3 elements from position 2:" << std::endl;
        container.erase(2, 3);
        std::cout << container << std::endl;

        std::cout << "Accessing elements with iterators and *iter:" << std::endl;
        for (auto iter = container.cbegin(); iter != container.cend(); ++iter)
        {
            std::cout << *iter << " ";
        }
        std::cout << "\n" << std::endl;
        std::cout << "Accessing elements with iterators and iter.get():" << std::endl;
        for (auto iter = container.begin(); iter != container.end(); ++iter)
        {
            std::cout << iter.get() << " ";
        }
        std::cout << "\n" << std::endl;
        std::cout << "auto iter : container:" << std::endl;
        for (const auto iter : container)
        {
         std::cout << iter << " ";   
        }

        std::cout << "\n" << std::endl;
        std::cout << "container.begin() = 22:" << std::endl;
        auto my_iter = container.begin();
        *my_iter = 22;
        std::cout << container << std::endl;

        std::cout << "std::advance(my_iter,4) = 44:" << std::endl;
        std::advance( my_iter,4);
        *my_iter = 44;
        std::cout << container << std::endl;

        std::cout << "std::advance(my_iter,-3) = 66:" << std::endl;
        std::advance( my_iter,-3);
        *my_iter = 66;
        std::cout << container << std::endl;

        std::cout << "container[5] = 55:" << std::endl;
        container[5] = 55;
        std::cout << container << std::endl;
        
        std::cout << container[5] << std::endl;
    }

    return 0;
}
