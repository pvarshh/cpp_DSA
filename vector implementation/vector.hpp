#pragma once
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <initializer_list>
#include <type_traits>

template <typename T>
class vector {
    static_assert(std::is_trivially_constructible_v<T>);
    static_assert(std::is_trivially_destructible_v<T>);
    T * buffer;
    std::size_t buffCap;
    std::size_t numElts;


    public: 

    //-----------------|| Constructors + Destructor ||-----------------//

    vector() : buffer(nullptr), buffCap(0), numElts(0) { } // default constructor

    vector(const vector & other) : buffer(nullptr), buffCap(0), numElts(0) { *this = other; } // copy constructor
    
    vector & operator=(const vector & other) {
        if (this == &other) { return *this; }
        clear();
        reserve(other.buffCap);
        for (std::size_t i = 0; i < other.numElts; i++) { buffer[i] = other.buffer[i]; }
        numElts = other.numElts;
        return *this;
    } // copy assignment

    constexpr vector(std::initializer_list<T> const args) : buffCap(1), numElts(0) {
        buffer = reinterpret_cast<T *>(malloc(sizeof(T)));
        for (auto & v : args) {
            push(std::remove_cv_t<T>(v));
        }
    } // initializer constructor

    ~vector() { clear(); } // destructor


    //-----------------|| Size Manipulation + Size Accessors ||-----------------//

    void resize(std::size_t newSize) {
        if (newSize > buffCap) { reserve(newSize); }
        for (std::size_t i = numElts; i < newSize; i++) { buffer[i] = T(); }
        numElts = newSize;
    } // resize()

    void reserve(std::size_t newCap) {
        if (newCap <= buffCap) { return; }
        T * newBuffer = static_cast<T*>(std::malloc(newCap * sizeof(T)));
        if (newBuffer == nullptr) { throw std::bad_alloc(); }
        for (std::size_t i = 0; i < numElts; i++) { newBuffer[i] = buffer[i]; }
        std::free(buffer);
        buffer = newBuffer;
        buffCap = newCap;
    } // reserve()

    std::size_t size() const { return numElts; } // size()

    std::size_t capacity() const { return buffCap; } // capacity()


    //-----------------|| Data Accessors ||-----------------//

    T & operator[](std::size_t idx) { return buffer[idx]; } // operator[]

    T & at(std::size_t idx) {
        if (idx >= numElts) { throw std::out_of_range("index out of range"); }
        return buffer[idx];
    } // at()

    T * begin() { return buffer; } // begin()

    T * end() { return buffer + numElts; } // end()


    //-----------------|| Vector Manipulation ||-----------------//

    void push_back(const T & val) {
        if (numElts == buffCap) { reserve(buffCap == 0 ? 1 : buffCap * 2); }
        buffer[numElts++] = val;
    } // push_back()

    void push(T * pos, const T & val) {
        if (numElts == buffCap) { reserve(buffCap == 0 ? 1 : buffCap * 2); }
        std::memmove(pos + 1, pos, (numElts - (pos - buffer)) * sizeof(T));
        *pos = val;
        numElts++;
    } // insert()

    void pop_back() {
        if (numElts == 0) { throw std::out_of_range("pop_back on empty vector"); }
        numElts--; 
    } // pop_back()

    void pop(T * pos) {
        if (pos < buffer || pos >= buffer + numElts) { throw std::out_of_range("erase out of range"); }
        std::memmove(pos, pos + 1, (numElts - (pos - buffer) - 1) * sizeof(T));
        numElts--;
    } // erase()

    void erase(T * start, T * end) {
        if (start < buffer || start >= buffer + numElts || end < buffer || end > buffer + numElts || start > end) { throw std::out_of_range("erase out of range"); }
        std::memmove(start, end, (numElts - (end - buffer)) * sizeof(T));
        numElts -= end - start;
    } // erase()

    void clear() {
        std::free(buffer);
        buffer = nullptr;
        buffCap = 0;
        numElts = 0;
    } // clear()

    void swap(vector & other) {
        std::swap(buffer, other.buffer);
        std::swap(buffCap, other.buffCap);
        std::swap(numElts, other.numElts);
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
        if (numElts != other.numElts) { return false; }
        for (std::size_t i = 0; i < numElts; i++) { if (buffer[i] != other.buffer[i]) { return false; } }
        return true;
    } // operator==

    bool operator!=(const vector & other) const { return !(*this == other); } // operator!=

    bool operator+=(const T & val) { push_back(val); } // operator+=

    bool operator-=(const T & val) { pop_back(val); } // operator-=

};