//
// Created by 79056 on 05.11.2022.
//

#include <iostream>
#include <containers/vector.hpp>
#include <containers/linked_list.hpp>

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

int main () {

    gsl::vector<int> vec (2,2);
    std::cout << vec << std::endl;
    std::cout << "\n\nRESIZE\n\n";
    vec.resize(6,5);
    std::cout << vec;

    return 0;
}


