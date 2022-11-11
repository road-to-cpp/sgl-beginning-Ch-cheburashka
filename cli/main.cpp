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
    std::cout << vector_int;
    std::cout << vector_int.front() << std::endl;
    std::cout << vector_int.back() << std::endl;
    return 0;
}








//gsl::vector<int> vector_int;
//vector_int.push_back(1);
//std::cout << "size:  " << vector_int.size() << std::endl;
//std::cout << "capacity: " << vector_int.capacity() << std::endl;
//std::cout << "data:  " << vector_int << std::endl;
//
//vector_int.resize(7,8);
//std::cout << "size:  " << vector_int.size() << std::endl;
//std::cout << "capacity: " << vector_int.capacity() << std::endl;
//std::cout << "data:  " << vector_int << std::endl;
//
//vector_int.push_back(67);
//std::cout << "size:  " << vector_int.size() << std::endl;
//std::cout << "capacity: " << vector_int.capacity() << std::endl;
//std::cout << "data:  " << vector_int << std::endl;
//
//for (int i =0;i<3;i++){
//vector_int.push_back(2);
//}
//std::cout << "size:  " << vector_int.size() << std::endl;
//std::cout << "capacity: " << vector_int.capacity() << std::endl;
//std::cout << "data:  " << vector_int << std::endl;
//
//vector_int.clear();
//std::cout << "size:  " << vector_int.size() << std::endl;
//std::cout << "capacity: " << vector_int.capacity() << std::endl;
//std::cout << "data:  " << vector_int << std::endl;
//
//if (vector_int.empty())
//std::cout << "empty";
//else
//std::cout << "not empty" << std::endl;