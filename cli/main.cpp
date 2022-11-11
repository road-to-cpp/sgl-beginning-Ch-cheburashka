//
// Created by 79056 on 05.11.2022.
//

#include <iostream>
#include <containers/vector.hpp>

int main () {
    gsl::vector<int> vector_int;
    vector_int.push_back(1);
    for (int i = 0;i < 3;i++){
        vector_int.push_back(6);
    }
    vector_int.push_back(7);
    std::cout << "size: " << vector_int.size() << std::endl;
    std::cout << "capacity: " << vector_int.capacity() << std::endl;
    std::cout << vector_int << std::endl;

    vector_int.insert(8,3);
    std::cout << "size: " << vector_int.size() << std::endl;
    std::cout << "capacity: " << vector_int.capacity() << std::endl;
    std::cout << vector_int << std::endl;

    vector_int.erase(2,3);
    std::cout << "size: " << vector_int.size() << std::endl;
    std::cout << "capacity: " << vector_int.capacity() << std::endl;
    std::cout << vector_int;

    return 0;
}