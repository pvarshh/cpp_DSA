#pragma once
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <initializer_list>
#include <type_traits>

template <typename T>
class vector {
        static_assert(std::is_trivially_constructible<T>::value);
        static_assert(std::is_trivially_destructible<T>::value);
        T * buffer;
        std::size_t buff_cap;
        std::size_t num_elts;


    public: 

    //-----------------|| Constructors + Destructor ||-----------------//

    vector() : buffer(nullptr), buff_cap(0), num_elts(0) { } // default constructor

    vector(const vector & other) : buffer(nullptr), buff_cap(0), num_elts(0) { *this = other; } // copy constructor
    
    vector & operator=(const vector & other) {
        if (this == &other) { return *this; }
        clear();
        reserve(other.buff_cap);
        for (std::size_t i = 0; i < other.num_elts; i++) { buffer[i] = other.buffer[i]; }
        num_elts = other.num_elts;
        return *this;
    } // copy assignment

    vector(std::initializer_list<T> const args) : buff_cap(1), num_elts(0) {
        buffer = reinterpret_cast<T *>(malloc(sizeof(T)));
        for (auto & v : args) {
            push(std::remove_cv_t<T>(v));
        }
    } // initializer constructor

    ~vector() { clear(); } // destructor


    //-----------------|| Size Manipulation + Size Accessors ||-----------------//

    void resize(std::size_t new_size) {
        if (new_size > buff_cap) { reserve(new_size); }
        for (std::size_t i = num_elts; i < new_size; i++) { buffer[i] = T(); }
        num_elts = new_size;
    } // resize()

    void reserve(std::size_t new_cal) {
        if (new_cal <= buff_cap) { return; }
        T * new_buffer = static_cast<T*>(std::malloc(new_cal * sizeof(T)));
        if (new_buffer == nullptr) { throw std::bad_alloc(); }
        for (std::size_t i = 0; i < num_elts; i++) { new_buffer[i] = buffer[i]; }
        std::free(buffer);
        buffer = new_buffer;
        buff_cap = new_cal;
    } // reserve()

    std::size_t size() const { return num_elts; } // size()

    std::size_t capacity() const { return buff_cap; } // capacity()


    //-----------------|| Data Accessors ||-----------------//

    T & operator[](std::size_t idx) { return buffer[idx]; } // operator[]

    T & at(std::size_t idx) {
        if (idx >= num_elts) { throw std::out_of_range("index out of range"); }
        return buffer[idx];
    } // at()

    bool empty() const { return num_elts == 0; } // empty()

    T * begin() { return buffer; } // begin()

    T * end() { return buffer + num_elts; } // end()


    //-----------------|| Vector Manipulation ||-----------------//

    void push_back(const T & val) {
        if (num_elts == buff_cap) { reserve(buff_cap == 0 ? 1 : buff_cap * 2); }
        buffer[num_elts++] = val;
    } // push_back()

    void push(T * pos, const T & val) {
        if (num_elts == buff_cap) { reserve(buff_cap == 0 ? 1 : buff_cap * 2); }
        std::memmove(pos + 1, pos, (num_elts - (pos - buffer)) * sizeof(T));
        *pos = val;
        num_elts++;
    } // insert()

    void pop_back() {
        if (num_elts == 0) { throw std::out_of_range("pop_back on empty vector"); }
        num_elts--; 
    } // pop_back()

    void pop(T * pos) {
        if (pos < buffer || pos >= buffer + num_elts) { throw std::out_of_range("erase out of range"); }
        std::memmove(pos, pos + 1, (num_elts - (pos - buffer) - 1) * sizeof(T));
        num_elts--;
    } // erase()

    void erase(T * start, T * end) {
        if (start < buffer || start >= buffer + num_elts || end < buffer || end > buffer + num_elts || start > end) { throw std::out_of_range("erase out of range"); }
        std::memmove(start, end, (num_elts - (end - buffer)) * sizeof(T));
        num_elts -= end - start;
    } // erase()

    void clear() {
        std::free(buffer);
        buffer = nullptr;
        buff_cap = 0;
        num_elts = 0;
    } // clear()

    void swap(vector & other) {
        std::swap(buffer, other.buffer);
        std::swap(buff_cap, other.buff_cap);
        std::swap(num_elts, other.num_elts);
    } // swap()

    void reverse(T * start, T * end) {
        while (start < end) {
            std::swap(*start, *end);
            start++;
            end--;
        }
    } // reverse()

    
    //-----------------|| Operators ||-----------------//

    bool operator==(const vector & other) const {
        if (num_elts != other.num_elts) { return false; }
        for (std::size_t i = 0; i < num_elts; i++) { if (buffer[i] != other.buffer[i]) { return false; } }
        return true;
    } // operator==

    bool operator!=(const vector & other) const { return !(*this == other); } // operator!=

    void operator+=(const T & val) { push_back(val); } // operator+=

    void operator-=(const T & val) { pop_back(val); } // operator-=

};