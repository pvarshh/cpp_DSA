#include "vector.hpp"
#include <iostream>
#include <cassert>

void test_default_constructor() {
    vector<int> x;
    assert(x.size() == 0);
    assert(x.capacity() == 0);
}

void test_copy_constructor() {
    vector<int> x = {1, 2, 3, 4};
    vector<int> y = x;
    assert(x == y);
}

void test_copy_assignment() {
    vector<int> x = {1, 2, 3, 4};
    vector<int> y;
    y = x;
    assert(x == y);
}

void test_initializer_constructor() {
    vector<int> x = {1, 2, 3, 4};
    assert(x.size() == 4);
    assert(x[0] == 1 && x[1] == 2 && x[2] == 3 && x[3] == 4);
}

void test_resize() {
    vector<int> x = {1, 2, 3, 4};
    x.resize(6);
    assert(x.size() == 6);
}

void test_reserve() {
    vector<int> x = {1, 2, 3, 4};
    x.reserve(10);
    assert(x.capacity() == 10);
}

void test_size() {
    vector<int> x = {1, 2, 3, 4};
    assert(x.size() == 4);
}

void test_capacity() {
    vector<int> x = {1, 2, 3, 4};
    assert(x.capacity() >= 4);
}

void test_bracket_operator() {
    vector<int> x = {1, 2, 3, 4};
    assert(x[0] == 1 && x[1] == 2 && x[2] == 3 && x[3] == 4);
}

void test_at() {
    vector<int> x = {1, 2, 3, 4};
    assert(x.at(2) == 3);
    try {
        x.at(5);
    } catch (const std::out_of_range& e) {
        std::cout << "Out of range exception caught as expected\n";
    }
}

void test_begin_end() {
    vector<int> x = {1, 2, 3, 4};
    int sum = 0;
    for (auto it = x.begin(); it != x.end(); ++it) {
        sum += *it;
    }
    assert(sum == 10);
}

void test_push_back() {
    vector<int> x;
    x.push_back(5);
    assert(x.size() == 1 && x[0] == 5);
}

void test_push() {
    vector<int> x = {1, 2, 3, 4};
    auto it = x.begin() + 2;
    x.push(it, 10);
    assert(x.size() == 5 && x[2] == 10);
}

void test_pop_back() {
    vector<int> x = {1, 2, 3, 4};
    x.pop_back();
    assert(x.size() == 3);
}

void test_pop() {
    vector<int> x = {1, 2, 3, 4};
    auto it = x.begin() + 2;
    x.pop(it);
    assert(x.size() == 3 && x[2] == 4);
}

void test_erase() {
    vector<int> x = {1, 2, 3, 4, 5};
    auto start = x.begin() + 1;
    auto end = x.begin() + 3;
    x.erase(start, end);
    assert(x.size() == 3 && x[1] == 4 && x[2] == 5);
}

void test_clear() {
    vector<int> x = {1, 2, 3, 4};
    x.clear();
    assert(x.size() == 0 && x.capacity() == 0);
}

void test_swap() {
    vector<int> x = {1, 2, 3};
    vector<int> y = {4, 5};
    x.swap(y);
    assert(x.size() == 2 && y.size() == 3);
}

void test_reverse() {
    vector<int> x = {1, 2, 3, 4};
    x.reverse(x.begin(), x.end() - 1);
    assert(x[0] == 4 && x[1] == 3 && x[2] == 2 && x[3] == 1);
}

void test_equality_operator() {
    vector<int> x = {1, 2, 3};
    vector<int> y = {1, 2, 3};
    assert(x == y);
}

void test_inequality_operator() {
    vector<int> x = {1, 2, 3};
    vector<int> y = {4, 5, 6};
    assert(x != y);
}

void test_compound_assignment_plus() {
    vector<int> x = {1, 2, 3};
    x += 4;
    assert(x.size() == 4 && x[3] == 4);
}

void test_compound_assignment_minus() {
    vector<int> x = {1, 2, 3};
    x -= 2;
    assert(x.size() == 2);
}

int main() {
    test_default_constructor();
    test_copy_constructor();
    test_copy_assignment();
    test_initializer_constructor();
    test_resize();
    test_reserve();
    test_size();
    test_capacity();
    test_bracket_operator();
    test_at();
    test_begin_end();
    test_push_back();
    test_push();
    test_pop_back();
    test_pop();
    test_erase();
    test_clear();
    test_swap();
    test_reverse();
    test_equality_operator();
    test_inequality_operator();
    test_compound_assignment_plus();
    test_compound_assignment_minus();

    std::cout << "All tests passed!\n";
    return 0;
}
