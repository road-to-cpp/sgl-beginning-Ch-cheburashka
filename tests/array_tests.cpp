//
// Created by MrMam on 31.10.2022.
//

#include <containers/array.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Array Tests") {
    SECTION("Front and back tests"){
        gsl::array<int> array_int(4);
        REQUIRE(array_int.front() == 0);
        for (int i = 0;i<array_int.size();i++){
            array_int[i] = i+1;
        }
        REQUIRE(array_int.front() == 1);
        REQUIRE(array_int.back() == 4);
    }

    SECTION("Fill tests"){
        gsl::array<int> array_int(4);
        for (int i = 0;i<array_int.size();i++){
            array_int[i] = i+1;
        }
        array_int.fill(7);
        REQUIRE(array_int[0] == 7);
        REQUIRE(array_int[3] == 7);
    }

    SECTION("Swap tests"){
        gsl::array<int> array_int(17);
        for (int i = 0;i<array_int.size();i++){
            array_int[i] = 4;
        }
        gsl::array<int>array_int_2(6);
        for (int i =0; i<array_int_2.size();i++){
            array_int_2[i] = 8;
        }
        array_int.swap(array_int_2);
        REQUIRE(array_int.size() == 6);
        REQUIRE(array_int_2.size() == 17);
        REQUIRE(array_int[5] == 8);
        REQUIRE(array_int_2[0] == 4);
    }
}