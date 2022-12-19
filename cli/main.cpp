//
// Created by 79056 on 05.11.2022.
//
#include <iostream>
#include "containers/linked_list.hpp"

struct test_struct {
    int value = 10;
    bool flag = true;

    bool operator==(test_struct const &other) const {
        return value == other.value && flag == other.flag;
    }

    friend std::ostream &operator<<(std::ostream &os, test_struct const &ts) {
        os << "{ value: " << ts.value << " flag: " << ts.flag << " }";
        return os;
    }
};


int main() {
    gsl::linked_list<int> ls;

    for (int i = 0; i<5; i++) { ls.push_back(i); }

    gsl::linked_list_iterator it = ls.rend();

    ++it;

    std::cout << *it;

    std::cout << ls;

    return 0;
}