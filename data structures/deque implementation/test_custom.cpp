#include "deque.hpp"
#include <iostream>
#include <cassert>

void test_default_constructor() {
    deque<int> d;
    assert(d.size() == 0);
    assert(d.empty());
}

void test_copy_constructor() {
    deque<int> d1;
    d1.push_front(1);
    d1.push_front(2);
    d1.push_front(3);

    deque<int> d2 = d1;
    assert(d1.size() == d2.size());
    assert(d1.front() == d2.front());
    assert(d1.back() == d2.back());
}

void test_copy_assignment() {
    deque<int> d1;
    d1.push_front(1);
    d1.push_front(2);
    d1.push_front(3);

    deque<int> d2;
    d2 = d1;
    assert(d1.size() == d2.size());
    assert(d1.front() == d2.front());
    assert(d1.back() == d2.back());
}

void test_initializer_constructor() {
    deque<int> d = {1, 2, 3};
    assert(d.size() == 3);
    assert(d.front() == 1);
    assert(d.back() == 3);
}

void test_size() {
    deque<int> d;
    assert(d.size() == 0);
    d.push_front(1);
    d.push_front(2);
    assert(d.size() == 2);
}

void test_empty() {
    deque<int> d;
    assert(d.empty());
    d.push_front(1);
    assert(!d.empty());
}

void test_front() {
    deque<int> d;
    d.push_front(1);
    d.push_front(2);
    assert(d.front() == 2);
}

void test_back() {
    deque<int> d;
    d.push_front(1);
    d.push_front(2);
    assert(d.back() == 1);
}

void test_push_front() {
    deque<int> d;
    d.push_front(1);
    assert(d.size() == 1);
}

void test_pop_front() {
    deque<int> d;
    d.push_front(1);
    d.push_front(2);
    d.pop_front();
    assert(d.size() == 1);
    assert(d.front() == 1);
}

void test_push_back() {
    deque<int> d;
    d.push_back(1);
    assert(d.size() == 1);
}

void test_pop_back() {
    deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.pop_back();
    assert(d.size() == 1);
    assert(d.back() == 1);
}

void test_clear() {
    deque<int> d;
    d.push_front(1);
    d.push_front(2);
    d.clear();
    assert(d.size() == 0);
    assert(d.empty());
}

int main() {
    test_default_constructor();
    test_copy_constructor();
    test_copy_assignment();
    test_initializer_constructor();
    test_size();
    test_empty();
    test_front();
    test_back();
    test_push_front();
    test_pop_front();
    test_push_back();
    test_pop_back();
    test_clear();
    return 0;
}
