#include "../libs/list.hpp"
#include <list>
#include <iostream>

template <typename T>
std::ostream& operator<<(std::ostream& ostream, const my::List<T>& list) {
    for (size_t i = 0; i < list.size(); i++) {
        ostream << list[i] << " ";}
    return ostream;
}
int main() {
    my::List<int> ml = my::List<int>();
    my::List<int> container1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    my::List<int> container =my::List<int>();;
    std::cout << "size: "<<container.size()<<"\n"<<"\n";
    for (int i = 0; i < 10; i++) {
        container.push_back(i);
    }
    std::cout << "container1:\n";
    std::cout << container1  << "\n";
    std::cout << "container1 size: "<<container1.size()<<"\n\n";
    std::cout << "container:\n";
    std::cout << container;
    std::cout << "\n";
    std::cout << "container size: "<<container.size()<<"\n\n";

    std::cout << "Erasing elements 3, 5, 7:\n";
    container.erase(6);
    container.erase(4);
    container.erase(2);
    std::cout << "container:\n";
    std::cout << container;
    std::cout << "\n";
    std::cout << "container size: "<<container.size()<<"\n\n";

    std::cout << "Inserting element 10 to start:\n";
    container.push_front(10);
    std::cout << "container1:\n";
    std::cout << container  << "\n";
    std::cout << "container size: "<<container.size()<<"\n\n";

    std::cout << "Inserting element 20 to middle:\n";
    container.insert(20, container.size() / 2);
    std::cout << "container size: "<<container.size()<<"\n\n";
    
    std::cout << "Inserting element 30 to end:\n";
    container.insert(30, container.size());
    std::cout << container << "\n";
    std::cout << "container size: "<<container.size()<<"\n\n";

    std::cout << "container[2]:\n";
    std::cout << container[2]<<"\n";
}

