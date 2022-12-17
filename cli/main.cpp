//
// Created by 79056 on 05.11.2022.
//
//#include <containers/array.hpp>
#include <iostream>
#include "containers/array.hpp"

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
    gsl::array<test_struct, 5> arr;
    arr.fill({1, false});
    for (auto &i : arr) {
        std::cout << i << std::endl;
    }
    return 0;
}