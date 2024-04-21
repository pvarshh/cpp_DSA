#include "linked_list.hpp"
#include <iostream>
#include <cassert>

void test_default_constructor() {
    linked_list<int> x;
    assert(x.size() == 0);
}

void test_copy_constructor() {
    linked_list<int> x;
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);

    linked_list<int> y = x;
    assert(x.size() == y.size());
    assert(x.front() == y.front());
    assert(x.back() == y.back());
}

void test_copy_assignment() {
    linked_list<int> x;
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);

    linked_list<int> y;
    y = x;
    assert(x.size() == y.size());
    assert(x.front() == y.front());
    assert(x.back() == y.back());
}

void test_initializer_constructor() {
    linked_list<int> x = {1, 2, 3};
    assert(x.size() == 3);
    assert(x.front() == 3);
    assert(x.back() == 1);
}

void test_size() {
    linked_list<int> x;
    assert(x.size() == 0);
    x.push_front(1);
    x.push_front(2);
    assert(x.size() == 2);
}

void test_empty() {
    linked_list<int> x;
    assert(x.empty());
    x.push_front(1);
    assert(!x.empty());
}

void test_front() {
    linked_list<int> x;
    x.push_front(1);
    x.push_front(2);
    assert(x.front() == 2);
}

void test_back() {
    linked_list<int> x;
    x.push_front(1);
    x.push_front(2);
    assert(x.back() == 1);
}

void test_push_front() {
    linked_list<int> x;
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);
    assert(x.size() == 3);
    assert(x.front() == 3);
    assert(x.back() == 1);
}

void test_push_back() {
    linked_list<int> x;
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    assert(x.size() == 3);
    assert(x.front() == 1);
    assert(x.back() == 3);
}

void test_pop_front() {
    linked_list<int> x;
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);
    x.pop_front();
    assert(x.size() == 2);
    assert(x.front() == 2);
    assert(x.back() == 1);
}

void test_pop_back() {
    linked_list<int> x;
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);
    x.pop_back();
    assert(x.size() == 2);
    assert(x.front() == 3);
    assert(x.back() == 2);
}

void test_insert() {
    linked_list<int> x;
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);
    x.insert(x[1], 4);
    assert(x.size() == 4);
    assert(x.front() == 3);
    assert(x.back() == 1);
    assert(x[1]->value == 4);
}

void test_erase() {
    linked_list<int> x;
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);
    x.erase(x[1]);
    assert(x.size() == 2);
    assert(x.front() == 3);
    assert(x.back() == 1);
}

void test_clear() {
    linked_list<int> x;
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);
    x.clear();
    assert(x.size() == 0);
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
    test_push_back();
    test_pop_front();
    test_pop_back();
    test_insert();
    test_erase();
    test_clear();
    std::cout << "All tests passed\n";
    return 0;
}  