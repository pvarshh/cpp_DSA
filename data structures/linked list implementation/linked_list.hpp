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
class linked_list {
    std::size_t _size;
    
    public:

    //-----------------|| Constructors + Destructor ||-----------------//

    linked_list() : _size(0) { } // default constructor

    linked_list(const linked_list & other) : _size(0) { *this = other; } // copy constructor

    linked_list & operator=(const linked_list & other) {
        if (this == &other) { return *this; }
        clear();
        for (Node* curr = other._front; curr != nullptr; curr = curr->next) {
            push(curr->value);
        }
        return *this;
    } // copy assignment

    linked_list(std::initializer_list<T> const args) : _size(0) {
        for (auto & v : args) {
            push(std::remove_cv_t<T>(v));
        }
    } // initializer constructor

    ~linked_list() { clear(); } // destructor


    //-----------------|| Capacity ||-----------------//

    std::size_t size() const { return _size; } // size()

    bool empty() const { return _size == 0; } // empty()


    //-----------------|| Data Accessors ||-----------------//

    T front () const {
        if (_front == nullptr) { throw std::out_of_range("linked_list::front(): linked_list is empty"); }
        return _front->value;
    } // front()

    T back () const {
        if (_front == nullptr) { throw std::out_of_range("linked_list::back(): linked_list is empty"); }
        return _back->value;
    } // back()


    //-----------------|| linked_list Manipulator ||-----------------//

    void push_front(T value) {
        Node<T>* new_node = new Node<T>;
        new_node->value = value;
        new_node->next = _front;
        _front = new_node;
        if (_back == nullptr) { _back = new_node; }
        _size++;
    } // push_front()

    void push_back(T value) {
        Node<T>* new_node = new Node<T>;
        new_node->value = value;
        new_node->next = nullptr;
        if (_front == nullptr) { _front = new_node; }
        else { _back->next = new_node; }
        _back = new_node;
        _size++;
    } // push_back()

    void pop_front() {
        if (_front == nullptr) { throw std::out_of_range("linked_list::pop_front(): linked_list is empty"); }
        Node<T>* temp = _front;
        _front = _front->next;
        delete temp;
        if (_front == nullptr) { _back = nullptr; }
        _size--;
    } // pop_front()

    void pop_back() {
        if (_front == nullptr) { throw std::out_of_range("linked_list::pop_back(): linked_list is empty"); }
        if (_front == _back) { delete _front; _front = _back = nullptr; _size--; return; }
        Node<T>* curr = _front;
        while (curr->next != _back) { curr = curr->next; }
        delete _back;
        _back = curr;
        _back->next = nullptr;
        _size--;
    } // pop_back()

    void clear() {
        while (_front != nullptr) {
            Node<T>* temp = _front;
            _front = _front->next;
            delete temp;
        }
        _back = nullptr;
        _size = 0;
    } // clear()


    //-----------------|| Operators ||-----------------//

    bool operator==(const linked_list & other) const {
        if (_size != other._size) { return false; }
        Node<T>* curr1 = _front;
        Node<T>* curr2 = other._front;
        while (curr1 != nullptr) {
            if (curr1->value != curr2->value) { return false; }
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        return true;
    }

    bool operator!=(const linked_list & other) const { return !(*this == other); }

    Node<T>* operator[](std::size_t index) const {
        if (index >= _size) { throw std::out_of_range("linked_list::operator[]: index out of range"); }
        Node<T>* curr = _front;
        for (std::size_t i = 0; i < index; i++) { curr = curr->next; }
        return curr;
    }

    
    //-----------------|| Helper Functions ||-----------------//

    void reverse() {
        Node<T>* prev = nullptr;
        Node<T>* curr = _front;
        Node<T>* next = nullptr;
        while (curr != nullptr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        _back = _front;
        _front = prev;
    } // reverse()

    void reverse(Node<T>* start, Node<T>* end) {
        Node<T>* prev = nullptr;
        Node<T>* curr = start;
        Node<T>* next = nullptr;
        while (curr != end) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        if (start == _front) { _front = prev; }
        else {
            Node<T>* temp = _front;
            while (temp->next != start) { temp = temp->next; }
            temp->next = prev;
        }
        start->next = curr;
    } // reverse()

    void swap(linked_list & other) {
        std::swap(_front, other._front);
        std::swap(_back, other._back);
        std::swap(_size, other._size);
    } // swap()

    Node<T>* find(T value) {
        Node<T>* curr = _front;
        while (curr != nullptr) {
            if (curr->value == value) { return curr; }
            curr = curr->next;
        }
        return nullptr;
    } // find()

    void insert(Node<T>* pos, T value) {
        Node<T>* new_node = new Node<T>;
        new_node->value = value;
        new_node->next = pos->next;
        pos->next = new_node;
        if (pos == _back) { _back = new_node; }
        _size++;
    } // insert()

    void erase(Node<T>* pos) {
        if (pos == _front) { pop_front(); return; }
        Node<T>* curr = _front;
        while (curr->next != pos) { curr = curr->next; }
        curr->next = pos->next;
        delete pos;
        if (pos == _back) { _back = curr; }
        _size--;
    } // erase()

    void erase(Node<T>* start, Node<T>* end) {
        if (start == _front) { _front = end; }
        else {
            Node<T>* curr = _front;
            while (curr->next != start) { curr = curr->next; }
            curr->next = end;
        }
        while (start != end) {
            Node<T>* temp = start;
            start = start->next;
            delete temp;
            _size--;
        }
    } // erase()


    




    Node<T>* begin() { return _front; } // begin()

    Node<T>* end() { return nullptr; } // end()

    


    
    
};
