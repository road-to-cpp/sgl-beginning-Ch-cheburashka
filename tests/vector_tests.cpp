//
// Created by MrMam on 31.10.2022.
//

#include <containers/vector.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("vector_tests") {

    SECTION("Resize tests"){
        gsl::vector<int> vector_int (6,7);
        REQUIRE(vector_int.size()==6);
        vector_int.resize(8,5);
        REQUIRE(vector_int.size()==8);
        REQUIRE(vector_int.capacity() == 8);
        REQUIRE(vector_int[5] == 7);
        REQUIRE(vector_int[7] == 5);
    }

    SECTION("Push_back tests"){
        gsl::vector<int> vector_int;
        vector_int.push_back(87);
        vector_int.push_back(96);
        REQUIRE(vector_int.size()==2);
        REQUIRE(vector_int[1] == 96);
    }

    SECTION("Pop_back tests"){
        gsl::vector<int> vector_int;
        for (int i =0;i<4;i++) {
            vector_int.push_back(1);
        }
        vector_int.pop_back();
        REQUIRE(vector_int.size() == 3);
        REQUIRE(vector_int.capacity() == 4);
        REQUIRE(vector_int[3] == 0);
    }

    SECTION("Clear tests"){
        gsl::vector<int> vector_int;
        for (int i =0;i<4;i++) {
            vector_int.push_back(1);
        }
        vector_int.clear();
        REQUIRE(vector_int.capacity() == 4);
        REQUIRE(vector_int.empty()==true);
    }

    SECTION("Insert tests") {
        gsl::vector<int> vector_int;
        vector_int.push_back(1);
        for (int i = 0;i < 4;i++){
            vector_int.push_back(6);
        }
        vector_int.push_back(7);
        vector_int.insert(8,2);
        REQUIRE(vector_int[2] == 8);
        REQUIRE(vector_int.size() == 7);
    }

    SECTION("Erase tests"){
        gsl::vector<int> vector_int;
        vector_int.push_back(1);
        for (int i = 0;i < 5;i++){
            vector_int.push_back(6);
        }
        vector_int.push_back(7);
        vector_int.erase(2,4);
        REQUIRE(vector_int[2] == 6);
        REQUIRE(vector_int.size() == 4);
    }

    SECTION("Swap tests"){
        gsl::vector<int> vector_int_1;
        gsl::vector<int> vector_int_2;
        for (int i = 0;i < 17;i++){
            vector_int_1.push_back(7);
        }
        for (int i = 0;i < 7;i++){
            vector_int_2.push_back(8);
        }
        vector_int_1.swap(vector_int_2);
        REQUIRE(vector_int_1.size() == 7);
        REQUIRE(vector_int_2.size() == 17);
        REQUIRE(vector_int_1[0] == 8);
        REQUIRE(vector_int_2[0] == 7);
    }

    SECTION("Front and back test"){
        gsl::vector<int> vector_int;
        vector_int.push_back(1);
        for (int i = 0;i < 3;i++){
            vector_int.push_back(6);
        }
        vector_int.push_back(7);
        std::cout << vector_int.size();
        REQUIRE(vector_int.front()==1);
        REQUIRE(vector_int.back()==7);
        }
}