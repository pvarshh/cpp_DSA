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
class deque {
    Node<T>* _front;
    std::size_t _size;
    
    public:


    //-----------------|| Constructors + Destructor ||-----------------//

    deque() : _front(nullptr), _size(0) { } // default constructor

    deque(const deque & other) : _front(nullptr), _size(0) { *this = other; } // copy constructor

    deque & operator=(const deque & other) {
        if (this == &other) { return *this; }
        clear();
        for (Node* curr = other._front; curr != nullptr; curr = curr->next) {
            push(curr->value);
        }
        return *this;
    } // copy assignment

    deque(std::initializer_list<T> const args) : _front(nullptr), _size(0) {
        for (auto & v : args) {
            push(std::remove_cv_t<T>(v));
        }
    } // initializer constructor

    ~deque() { clear(); } // destructor 

    
    //-----------------|| Size Manipulation + Size Accessors ||-----------------//

    std::size_t size() const { return _size; } // size()

    bool empty() const { return _size == 0; } // empty()


    //-----------------|| Data Accessors ||-----------------//

    T front () const {
        if (_front == nullptr) { throw std::out_of_range("deque::front(): deque is empty"); }
        return _front->value;
    } // front()

    T back() const {
        if (_front == nullptr) { throw std::out_of_range("deque::back(): deque is empty"); }
        Node<T>* curr = _front;
        while (curr->next != nullptr) { curr = curr->next; }
        return curr->value;
    } // back()


    //-----------------|| deque Manipulator ||-----------------//

    void push_front(T value) {
        Node<T>* new_node = new Node<T>;
        new_node->value = value;
        new_node->next = _front;
        _front = new_node;
        _size++;
    } // push_front()

    void pop_front() {
        if (_front == nullptr) { throw std::out_of_range("deque::pop_front(): deque is empty"); }
        Node<T>* temp = _front;
        _front = _front->next;
        delete temp;
        _size--;
    } // pop_front()

    void push_back(T value) {
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
    } // push_back()

    void pop_back() {
        if (_front == nullptr) { throw std::out_of_range("deque::pop_back(): deque is empty"); }
        if (_front->next == nullptr) { delete _front; _front = nullptr; _size--; return; }
        Node<T>* curr = _front;
        while (curr->next->next != nullptr) { curr = curr->next; }
        delete curr->next;
        curr->next = nullptr;
        _size--;
    } // pop_back()

    void clear() {
        while (_front != nullptr) {
            Node<T>* temp = _front;
            _front = _front->next;
            delete temp;
        }
        _size = 0;
    } // clear()


    //-----------------|| Operators ||-----------------//

    bool operator==(const deque & other) const {
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

    bool operator!=(const deque & other) const { return !(*this == other); }
 
};