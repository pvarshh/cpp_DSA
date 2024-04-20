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
    Node<T>* _top;
    std::size_t _size;
    
    public:


    //-----------------|| Constructors + Destructor ||-----------------//

    queue() : _top(nullptr), _size(0) { } // default constructor

    queue(const queue & other) : _top(nullptr), _size(0) { *this = other; } // copy constructor

    queue & operator=(const queue & other) {
        if (this == &other) { return *this; }
        clear();
        for (Node* curr = other._top; curr != nullptr; curr = curr->next) {
            push(curr->value);
        }
        return *this;
    } // copy assignment

    queue(std::initializer_list<T> const args) : _top(nullptr), _size(0) {
        for (auto & v : args) {
            push(std::remove_cv_t<T>(v));
        }
    } // initializer constructor

    ~queue() { clear(); } // destructor


    //-----------------|| Size Manipulation + Size Accessors ||-----------------//

    std::size_t size() const { return _size; } // size()

    bool empty() const { return _size == 0; } // empty()


    //-----------------|| Data Accessprs ||-----------------//

    T top() const {
        if (_top == nullptr) { throw std::out_of_range("queue::front(): queue is empty"); }
        return _top->value;
    } // front()


    //-----------------|| Stack Manipulator ||-----------------//

    void push(T value) {
        Node* new_node = new Node;
        new_node->value = value;
        new_node->next = nullptr;
        if (_top == nullptr) { _top = new_node; } 
        else {
            Node* curr = _top;
            while (curr->next != nullptr) { curr = curr->next; }
            curr->next = new_node;
        }
        _size++;
    } // push()

    void pop() {
        if (_top == nullptr) { throw std::out_of_range("queue::pop(): queue is empty"); }
        Node* temp = _top;
        _top = _top->next;
        delete temp;
        _size--;
    } // pop()

    void clear() {
        while (_top != nullptr) {
            Node* temp = _top;
            _top = _top->next;
            delete temp;
        }
        _size = 0;
    } // clear()


    //-----------------|| Operators ||-----------------//

    bool operator==(const queue & other) const {
        if (_size != other._size) { return false; }
        Node* curr1 = _top;
        Node* curr2 = other._top;
        while (curr1 != nullptr) {
            if (curr1->value != curr2->value) { return false; }
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        return true;
    }

    bool operator!=(const queue & other) const { return !(*this == other); }

    void & operator+=(const T & value) {
        push(value);
        return *this;
    }

    void & operator+=(const T & value) {
        pop();
        return *this;
    }

   
};