//
// Created by 79056 on 05.11.2022.
//
#include <iostream>
#include "containers/map.hpp"

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

    gsl::map<int,int> map;

    map.insert({1,1});



    return 0;
}