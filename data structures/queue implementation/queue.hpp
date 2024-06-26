#pragma once
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <initializer_list>
#include <type_traits>

template <typename T>
struct Node {
    Node<T>* next;
    T value;
}; 

template <typename T>
class queue {
    Node<T>* _front;
    std::size_t _size;
    
    public:


    //-----------------|| Constructors + Destructor ||-----------------//

    queue() : _front(nullptr), _size(0) { } // default constructor

    queue(const queue & other) : _front(nullptr), _size(0) { *this = other; } // copy constructor

    queue & operator=(const queue & other) {
        if (this == &other) { return *this; }
        clear();
        for (Node* curr = other._front; curr != nullptr; curr = curr->next) {
            push(curr->value);
        }
        return *this;
    } // copy assignment

    queue(std::initializer_list<T> const args) : _front(nullptr), _size(0) {
        for (auto & v : args) {
            push(std::remove_cv_t<T>(v));
        }
    } // initializer constructor

    
    //-----------------|| Size Manipulation + Size Accessors ||-----------------//

    std::size_t size() const { return _size; } // size()

    bool empty() const { return _size == 0; } // empty()


    //-----------------|| Data Accessors ||-----------------//

    T front () const {
        if (_front == nullptr) { throw std::out_of_range("queue::front(): queue is empty"); }
        return _front->value;
    } // front()


    //-----------------|| queue Manipulator ||-----------------//

    void push(T value) {
        Node<T>* new_node = new Node<T>;
        new_node->value = value;
        new_node->next = nullptr;
        if (_front == nullptr) { _front = new_node; } 
        else {
            Node<T>* curr = _front;
            while (curr->next != nullptr) { curr = curr->next; }
            curr->next = new_node;
        }
        _size++;
    } // push()

    void pop() {
        if (_front == nullptr) { throw std::out_of_range("queue::pop(): queue is empty"); }
        Node<T>* temp = _front;
        _front = _front->next;
        delete temp;
        _size--;
    } // pop()

    void clear() {
        while (_front != nullptr) {
            Node<T>* temp = _front;
            _front = _front->next;
            delete temp;
        }
        _size = 0;
    } // clear()


    //-----------------|| Operators ||-----------------//

    bool operator==(const queue & other) const {
        if (_size != other._size) { return false; }
        Node<T>* curr = _front;
        Node<T>* other_curr = other._front;
        while (curr != nullptr) {
            if (curr->value != other_curr->value) { return false; }
            curr = curr->next;
            other_curr = other_curr->next;
        }
        return true;
    }

    bool operator!=(const queue & other) const { return !(*this == other); }

    void & operator+=(const T & value) {
        push(value);
        return *this;
    }

    void & operator--() {
        pop();
        return *this;
    }
 
};