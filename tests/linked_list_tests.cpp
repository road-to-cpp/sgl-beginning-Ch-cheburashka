//
// Created by MrMam on 01.11.2022.
//

#include <containers/linked_list.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("linked_list_tests") {

//    SECTION("Resize tests"){
//        gsl::linked_list<int> ls_int;
//        REQUIRE(ls_int.empty());
//        ls_int.resize(8,5);
//        REQUIRE(ls_int.size()==8);
//        REQUIRE(ls_int[7] == 5);
//    }

    SECTION("Push_back and push_front tests"){
        gsl::linked_list<int> ls_int;
        ls_int.push_back(87);
        ls_int.push_back(96);
        ls_int.push_front(1);
        REQUIRE(ls_int.size()==3);
        REQUIRE(ls_int[2] == 96);
        REQUIRE(ls_int[0] == 1);
    }
//
//    SECTION("Pop_back and pop_front tests"){
//        gsl::linked_list<int> ls_int;
//        for (int i =0;i<4;i++) {
//            ls_int.push_back(1);
//        }
//        ls_int.pop_back();
//        REQUIRE(ls_int.size() == 3);
//        REQUIRE(ls_int[3] == 0);
//        ls_int.pop_front();
//        REQUIRE(ls_int.size() == 2);
//        REQUIRE(ls_int[0] == 0);
//    }
//
//    SECTION("Clear tests"){
//        gsl::linked_list<int> ls_int;
//        for (int i =0;i<4;i++) {
//            ls_int.push_back(1);
//        }
//        ls_int.clear();
//        REQUIRE(ls_int.empty()==true);
//    }
//
//    SECTION("Insert tests") {
//        gsl::linked_list<int> ls_int;
//        ls_int.push_back(1);
//        for (int i = 0;i < 4;i++){
//            ls_int.push_back(6);
//        }
//        ls_int.push_back(7);
//        ls_int.insert(8,2);
//        REQUIRE(ls_int[2] == 8);
//        REQUIRE(ls_int.size() == 7);
//    }
//
//    SECTION("Erase tests"){
//        gsl::linked_list<int> ls_int;
//        ls_int.push_back(1);
//        for (int i = 0;i < 5;i++){
//            ls_int.push_back(6);
//        }
//        ls_int.push_back(7);
//        ls_int.erase(2,4);
//        REQUIRE(ls_int[2] == 6);
//        REQUIRE(ls_int.size() == 4);
//    }
//
//    SECTION("Swap tests"){
//        gsl::linked_list<int> ls_int_1;
//        gsl::linked_list<int> ls_int_2;
//        for (int i = 0;i < 17;i++){
//            ls_int_1.push_back(7);
//        }
//        for (int i = 0;i < 7;i++){
//            ls_int_2.push_back(8);
//        }
//        ls_int_1.swap(ls_int_2);
//        REQUIRE(ls_int_1.size() == 7);
//        REQUIRE(ls_int_2.size() == 17);
//        REQUIRE(ls_int_1[0] == 8);
//        REQUIRE(ls_int_2[0] == 7);
//    }
//
//    SECTION("Front and back test"){
//        gsl::linked_list<int> ls_int;
//        ls_int.push_back(1);
//        for (int i = 0;i < 3;i++){
//            ls_int.push_back(6);
//        }
//        ls_int.push_back(7);
//        REQUIRE(ls_int.front()==1);
//        REQUIRE(ls_int.back()==7);
//    }
}