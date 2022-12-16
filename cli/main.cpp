//
// Created by 79056 on 05.11.2022.
//
//#include <containers/array.hpp>
#include <iostream>

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


int sum (int a, int b) {
    return a+b;
}

int main() {
    std::cout << sum(4, 5) << std::endl << std::endl;
}