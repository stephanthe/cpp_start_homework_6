#pragma once
#include <cstddef>
#include <iostream>

namespace my {
template <typename T>
struct Node {
    Node();
    T value_;
    Node<T>* next_{nullptr};
    Node<T>* prev_{nullptr};
};

template <typename T>
Node<T>::Node() {
  prev_ = nullptr;
  next_ = nullptr;
}

template <typename T>
class List {
   public:
    
    List() : head_(nullptr), tail_(nullptr), size_(0) {}

    
    List(std::initializer_list<T> elements) : head_(nullptr), tail_(nullptr), size_(0)
    {
        for (const auto& val : elements) {
            push_back(val);
        }
    }


    ~List() {
        Node<T>* current = head_;
        while (current != nullptr) {
            Node<T>* next = current->next_;
            delete current;
            current = next;
        }
    }

    bool empty() const { return size_; }

    size_t size() const { return size_; }

    T& operator[](size_t index) const{
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* current = head_;
        for (size_t i = 0; i < index; i++) {
            current = current->next_;
        }
        return current->value_;
    }
    void push_back(T const& val) {
        Node<T>* node = new Node<T>;
        node->value_ = val;
        if (size_ == 0) {
            head_ = tail_ = node;
        }
        else{   
            tail_->next_ = node;
            node->prev_ = tail_;
            tail_ = node;
        }
        size_++;
    }
    void push_front(T const& val) {
        Node<T>* node = new Node<T>;
        node->value_ = val;
        if (size_ == 0) {
            head_ = tail_ = node;
        }
        else{
            head_->prev_ = node;
            node->next_ = head_;
            head_ = node;
        }
        size_++;
    }

    void erase(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* current = head_;
        for (size_t i = 0; i < index; i++) {
            current = current->next_;
        }
        if (current == head_) {
            head_ = current->next_;
        }
        else if (current == tail_) {
            tail_ = current->prev_;
        }
        else {
            current->prev_->next_ = current->next_;
            current->next_->prev_ = current->prev_;
        }
        delete current;
        size_--;
    }
    void insert(T const& val, size_t index) {    
        if (index > size_) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* node = new Node<T>;
        node->value_ = val;
        if (index == 0) {
            node->next_ = head_;
            head_->prev_ = node;
            head_ = node;
        }
        else if (index == size_) {
            tail_->next_ = node;
            node->prev_ = tail_;
            tail_ = node;
        }
        else {
            Node<T>* current = head_;
            for (size_t i = 0; i < index; i++) {
                current = current->next_;
            }
            node->next_ = current;
            node->prev_ = current->prev_;
            current->prev_->next_ = node;
            current->prev_ = node;
        }
        size_++;
        
    }
   private:
    Node<T>* head_{nullptr};
    Node<T>* tail_{nullptr};
    size_t size_{0};
};

}  // namespace my
