#pragma once 

using namespace std;

template<typename T>
class Vector {
    private:
        T* _elt;
        size_t _num_elts;
        size_t _capacity;

    public:
        /* -------- MEMBER FUNCTIONS --------*/
        Vector() : _elt(0), _num_elts(1), _capacity(0) { } // default ctor;

        Vector(size_t s) : _elt(new T[s]), _num_elts(s), _capacity(s) { } // ctor

        Vector(const Vector& original) : _elt(new T[original._capacity]), _num_elts(original._num_elts), _capacity(original._capacity) {
            for (size_t i = 0; i < _num_elts; i++) { _elt[i] = original._elt[i]; }
        } // copy ctor

        Vector& operator=(const Vector& original) {
            if (this != &original) {
                delete[] _elt;
                _elt = new T[original._capacity];
                _num_elts = original._num_elts;
                _capacity = original._capacity;
                for (size_t i = 0; i < _num_elts; i++) { _elt[i] = original._elt[i]; }
            }
            return *this;
        } // copy assignment

        ~Vector() { delete[] _elt; } // dtor


        /* -------- ITERATORS --------*/
        class iterator;

        iterator begin() { return iterator(_elt); } // begin()

        iterator end() { return iterator(_elt + _num_elts); } // end()


        /* -------- ELEMENT ACCESS --------*/
        T at(size_t pos) {
            if (pos >= _num_elts) { throw out_of_range("Index out of range"); }
            return _elt[pos];
        } // at()

        T operator[](size_t pos) { return _elt[pos]; } // operator[]

        T front() { return _elt[0]; } // front()

        T back() { return _elt[_num_elts - 1]; } // front()


        /* -------- CAPACITY --------*/        
        bool empty() { return _num_elts == 0; } // empty()

        size_t size() { return _num_elts; } // size()

        void reserve(size_t new_cap) {
            if (new_cap > _capacity) {
                T* new_elt = new T[new_cap];
                for (size_t i = 0; i < _num_elts; i++) { new_elt[i] = _elt[i]; }
                delete[] _elt;
                _elt = new_elt;
                _capacity = new_cap;
            }   
        } // reserve()

        size_t :capacity() { return _capacity; } // capacity()



        /* -------- MODIFIERS --------*/
        void clear() {
            delete[] _elt;
            _elt = 0;
            _num_elts = 0;
            _capacity = 0;
        } // clear()

        void insert(iterator pos, const T& val) {
            if (_num_elts == _capacity) {
                _capacity = _capacity == 0 ? 1 : _capacity * 2;
                T* new_elt = new T[_capacity];
                for (size_t i = 0; i < pos._ptr - _elt; i++) { new_elt[i] = _elt[i]; }
                new_elt[pos._ptr - _elt] = val;
                for (size_t i = pos._ptr - _elt + 1; i < _num_elts + 1; i++) { new_elt[i] = _elt[i - 1]; }
                delete[] _elt;
                _elt = new_elt;
                _num_elts++;
            } 
            else {
                for (size_t i = _num_elts; i > pos._ptr - _elt; i--) { _elt[i] = _elt[i - 1]; }
                _elt[pos._ptr - _elt] = val;
                _num_elts++;
            }
        } // insert()

        void erase(iterator pos) {
            for (size_t i = pos._ptr - _elt; i < _num_elts - 1; i++) { _elt[i] = _elt[i + 1]; }
            _num_elts--;
        } // erase()

        void erase(iterator start, iterator end) {
            for (size_t i = 0; i < end._ptr - start._ptr; i++) {
                for (size_t j = start._ptr - _elt; j < _num_elts - 1; j++) { _elt[j] = _elt[j + 1]; }
                _num_elts--;
            }
        } // erase()

        void push_back(const T& val) {
            if (_num_elts == _capacity) {
                _capacity = _capacity == 0 ? 1 : _capacity * 2;
                T* new_elt = new T[_capacity];
                for (size_t i = 0; i < _num_elts; i++) { new_elt[i] = _elt[i]; }
                new_elt[_num_elts] = val;
                delete[] _elt;
                _elt = new_elt;
                _num_elts++;
            } 
            else {
                _elt[_num_elts] = val;
                _num_elts++;
            }
        } // push_back()

        void pop_back() { _num_elts--; } // pop_back()

        void resize(size_t count) {
            if (count < _num_elts) {
                _num_elts = count;
            } 
            else if (count > _num_elts) {
                if (count > _capacity) {
                    _capacity = count;
                    T* new_elt = new T[_capacity];
                    for (size_t i = 0; i < _num_elts; i++) { new_elt[i] = _elt[i]; }
                    delete[] _elt;
                    _elt = new_elt;
                }
                for (size_t i = _num_elts; i < count; i++) { _elt[i] = T(); }
                _num_elts = count;
            }
        } // resize()

        void swap(size_t pos1, size_t pos2) {
            T temp = _elt[pos1];
            _elt[pos1] = _elt[pos2];
            _elt[pos2] = temp;
        } // swap()


        /* -------- USEFUL --------*/
        bool operator==(const Vector& other) {
            if (_num_elts != other._num_elts) { return false; }
            for (size_t i = 0; i < _num_elts; i++) {
                if (_elt[i] != other._elt[i]) { return false; }
            }
            return true;
        } // operator==()

        bool operator!=(const Vector& other) { return !(*this == other); } // operator!=()

        void reverse(iterator start, iterator end) {
            for (size_t i = 0; i < (end._ptr - start._ptr) / 2; i++) {
                T temp = start._ptr[i];
                start._ptr[i] = end._ptr[-i - 1];
                end._ptr[-i - 1] = temp;
            }
        } // reverse()

        void print() {
            for (size_t i = 0; i < _num_elts; i++) { cout << _elt[i] << " "; }
            cout << endl;
        } // print()

        void sort(iterator start, iterator end) {
            for (size_t i = 0; i < end._ptr - start._ptr - 1; i++) {
                for (size_t j = 0; j < end._ptr - start._ptr - i - 1; j++) {
                    if (start._ptr[j] > start._ptr[j + 1]) {
                        T temp = start._ptr[j];
                        start._ptr[j] = start._ptr[j + 1];
                        start._ptr[j + 1] = temp;
                    }
                }
            }
        } // sort()
};

template<class T> class iterator {
    private:
        T* _ptr;

    public:
        iterator(T* p) :_ptr(p) {}
        iterator& operator++() {
            _ptr++;
            return *this;
        }
        iterator& operator--() {
            _ptr--;
            return *this;
        }
        T& operator*() { return *_ptr; }
        iterator operator+(int n) { return iterator(_ptr + n); }
        iterator operator-(int n) { return iterator(_ptr - n); }
        bool operator==(const iterator& b) const { return *_ptr == *b._ptr; }
        bool operator!=(const iterator& b) const { return *_ptr != *b._ptr; }
        bool operator<(const iterator& b) const { return *_ptr < *b._ptr; }
        bool operator>(const iterator& b) const { return *_ptr > *b._ptr; }
};
