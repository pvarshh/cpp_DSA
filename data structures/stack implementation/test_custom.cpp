#include "stack.hpp"
#include <iostream>
#include <cassert>

void test_default_constructor() {
    stack<int> s;
    assert(s.size() == 0);
    assert(s.empty());
}

void test_copy_constructor() {
    stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);

    stack<int> s2 = s1;
    assert(s1.size() == s2.size());
    assert(s1.top() == s2.top());
}

void test_copy_assignment() {
    stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);

    stack<int> s2;
    s2 = s1;
    assert(s1.size() == s2.size());
    assert(s1.top() == s2.top());
}

void test_initializer_constructor() {
    stack<int> s = {1, 2, 3};
    assert(s.size() == 3);
    assert(s.top() == 3);
}

void test_size() {
    stack<int> s;
    assert(s.size() == 0);
    s.push(1);
    s.push(2);
    assert(s.size() == 2);
}

void test_empty() {
    stack<int> s;
    assert(s.empty());
    s.push(1);
    assert(!s.empty());
}

void test_top() {
    stack<int> s;
    s.push(1);
    s.push(2);
    assert(s.top() == 1);
}

void test_push() {
    stack<int> s;
    s.push(1);
    assert(s.size() == 1);
    assert(s.top() == 1);
}

void test_pop() {
    stack<int> s;
    s.push(1);
    s.push(2);
    s.pop();
    assert(s.size() == 1);
    assert(s.top() == 1);
}

void test_clear() {
    stack<int> s;
    s.push(1);
    s.push(2);
    s.clear();
    assert(s.size() == 0);
    assert(s.empty());
}

int main() {
    test_default_constructor();
    test_copy_constructor();
    test_copy_assignment();
    test_initializer_constructor();
    test_size();
    test_empty();
    test_top();
    test_push();
    test_pop();
    test_clear();

    std::cout << "All tests passed!\n";
    return 0;
}
