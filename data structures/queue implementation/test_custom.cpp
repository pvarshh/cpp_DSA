#include "queue.hpp"
#include <iostream>
#include <cassert>

void test_default_constructor() {
    queue<int> q;
    assert(q.size() == 0);
    assert(q.empty());
}

void test_copy_constructor() {
    queue<int> q1;
    q1.push(1);
    q1.push(2);
    q1.push(3);

    queue<int> q2 = q1;
    assert(q1.size() == q2.size());
    assert(q1.top() == q2.top());
}

void test_copy_assignment() {
    queue<int> q1;
    q1.push(1);
    q1.push(2);
    q1.push(3);

    queue<int> q2;
    q2 = q1;
    assert(q1.size() == q2.size());
    assert(q1.top() == q2.top());
}

void test_initializer_constructor() {
    queue<int> q = {1, 2, 3};
    assert(q.size() == 3);
    assert(q.top() == 1);
}

void test_size() {
    queue<int> q;
    assert(q.size() == 0);
    q.push(1);
    q.push(2);
    assert(q.size() == 2);
}

void test_empty() {
    queue<int> q;
    assert(q.empty());
    q.push(1);
    assert(!q.empty());
}

void test_top() {
    queue<int> q;
    q.push(1);
    q.push(2);
    assert(q.top() == 1);
}

void test_push() {
    queue<int> q;
    q.push(1);
    assert(q.size() == 1);
    assert(q.top() == 1);
}

void test_pop() {
    queue<int> q;
    q.push(1);
    q.push(2);
    q.pop();
    assert(q.size() == 1);
    assert(q.top() == 2);
}

void test_clear() {
    queue<int> q;
    q.push(1);
    q.push(2);
    q.clear();
    assert(q.size() == 0);
    assert(q.empty());
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
