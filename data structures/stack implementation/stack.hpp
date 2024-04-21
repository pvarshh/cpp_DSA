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
class stack {
    Node<T>* _top;
    std::size_t _size;
    
    public:


    //-----------------|| Constructors + Destructor ||-----------------//

    stack() : _top(nullptr), _size(0) { } // default constructor

    stack(const stack & other) : _top(nullptr), _size(0) { *this = other; } // copy constructor

    stack & operator=(const stack & other) {
        if (this == &other) { return *this; }
        clear();
        for (Node* curr = other._top; curr != nullptr; curr = curr->next) {
            push(curr->value);
        }
        return *this;
    } // copy assignment

    stack(std::initializer_list<T> const args) : _top(nullptr), _size(0) {
        for (auto & v : args) {
            push(std::remove_cv_t<T>(v));
        }
    } // initializer constructor    


    //-----------------|| Size Manipulation + Size Accessors ||-----------------//

    std::size_t size() const { return _size; } // size()

    bool empty() const { return _size == 0; } // empty()

    
    //-----------------|| Data Accessprs ||-----------------//

    T top() const {
        if (_top == nullptr) { throw std::out_of_range("stack::top(): stack is empty"); }
        return _top->value;
    } // top()


    //-----------------|| Stack Manipulator ||-----------------//

    void push(T value) {
        Node<T>* new_node = new Node<T>;
        new_node->value = value;
        new_node->next = _top;
        _top = new_node;
        _size++;
    } // push()

    void pop() {
        if (_top == nullptr) { throw std::out_of_range("stack::pop(): stack is empty"); }
        Node<T>* temp = _top;
        _top = _top->next;
        delete temp;
        _size--;
    } // pop()

    void clear() {
        while (_top != nullptr) {
            Node<T>* temp = _top;
            _top = _top->next;
            delete temp;
        }
        _size = 0;
    } // clear()


    //-----------------|| Operators ||-----------------//

    bool operator==(const queue & other) const {
        if (_size != other._size) { return false; }
        Node<T>* curr1 = _top;
        Node<T>* curr2 = other._top;
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

    void & operator--() {
        pop();
        return *this;
    }
};