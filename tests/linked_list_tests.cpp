//
// Created by MrMam on 01.11.2022.
//

#include <containers/linked_list.hpp>
#include <catch2/catch_test_macros.hpp>

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

TEST_CASE("linked_list_tests") {
    SECTION("Empty test") {
        SECTION("integer") {
            gsl::linked_list<int> int_list;
            REQUIRE(int_list.empty());
            REQUIRE(int_list.size() == 0); // NOLINT(readability-container-size-empty)
            REQUIRE_THROWS_AS(
                    int_list[1] == 150,
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    int_list.to_string() == "[]"
            );
        }

        SECTION("custom structure") {
            gsl::linked_list<test_struct> ts_list;
            REQUIRE(ts_list.empty());
            REQUIRE(ts_list.size() == 0); // NOLINT(readability-container-size-empty)
            REQUIRE_THROWS_AS(
                    ts_list[1] == test_struct{},
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    ts_list.to_string() == "[]"
            );
        }

        SECTION("pointer") {
            gsl::linked_list<int *> pint_list;
            REQUIRE(pint_list.empty());
            REQUIRE(pint_list.size() == 0); // NOLINT(readability-container-size-empty)
            REQUIRE_THROWS_AS(
                    *pint_list[1] == 0,
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pint_list.to_string() == "[]"
            );
        }

        SECTION("custom pointer") {
            gsl::linked_list<test_struct *> pts_list;
            REQUIRE(pts_list.empty());
            REQUIRE(pts_list.size() == 0); // NOLINT(readability-container-size-empty)
            REQUIRE_THROWS_AS(
                    *pts_list[1] == test_struct{},
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_list.to_string() == "[]"
            );
        }
    }

    SECTION("Insert tests") {
        SECTION("integer") {
            gsl::linked_list<int> int_list;
            for (int i = 0; i < 3; i++) { int_list.push_back(1); }
            REQUIRE(int_list.size() == 3); // NOLINT(readability-container-size-empty)
            int_list.insert(2, 1);
            REQUIRE_THROWS_AS(
                    int_list.insert(3, 4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(int_list.size() == 4);
            REQUIRE(
                    int_list.to_string() == "[1, 2, 1, 1]"
            );
        }

        SECTION("custom structure") {
            gsl::linked_list<test_struct> ts_list;
            for (int i = 0; i < 3; i++) { ts_list.push_back(test_struct{}); }
            REQUIRE(ts_list.size() == 3); // NOLINT(readability-container-size-empty)
            ts_list.insert(test_struct{}, 1);
            REQUIRE_THROWS_AS(
                    ts_list.insert(test_struct{}, 4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(ts_list.size() == 4);
            REQUIRE(
                    ts_list.to_string() ==
                    "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
        }

        SECTION("pointer") {
            gsl::linked_list<int *> pint_list;
            int *ptr;
            for (int i = 0; i < 3; i++) {
                ptr = &i;
                pint_list.push_back(ptr);
            }
            REQUIRE(pint_list.size() == 3); // NOLINT(readability-container-size-empty)
            pint_list.insert(ptr, 1);
            REQUIRE(pint_list.size() == 4);
            REQUIRE_THROWS_AS(
                    pint_list.insert(ptr, 4),
                    gsl::exceptions::out_of_range
            );
//            REQUIRE(
//                    pint_list.to_string() == "[]"
//            );
        }

        SECTION("custom pointer") {
            gsl::linked_list<test_struct *> pts_list;
            test_struct *ts;
            for (int i = 0; i < 3; i++) {
                test_struct testStruct;
                ts = &testStruct;
                pts_list.push_back(ts);
            }
            REQUIRE(pts_list.size() == 3); // NOLINT(readability-container-size-empty)
            pts_list.insert(ts, 1);
            REQUIRE(pts_list.size() == 4);
            REQUIRE_THROWS_AS(
                    pts_list.insert(ts, 4),
                    gsl::exceptions::out_of_range
            );
//            REQUIRE(
//                    pts_list.to_string() == "[]"
//            );
        }
    }

    SECTION("Erase(int index) tests") {
        SECTION("integer") {
            gsl::linked_list<int> int_list;
            for (int i = 0; i < 4; i++) { int_list.push_back(1); }
            REQUIRE(int_list.size() == 4); // NOLINT(readability-container-size-empty)
            int_list.erase(1);
            REQUIRE(int_list.size() == 3);
            REQUIRE_THROWS_AS(
                    int_list.erase(3),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    int_list.to_string() == "[1, 1, 1]"
            );
        }

        SECTION("custom structure") {
            gsl::linked_list<test_struct> ts_list;
            for (int i = 0; i < 4; i++) { ts_list.push_back(test_struct{}); }
            REQUIRE(ts_list.size() == 4); // NOLINT(readability-container-size-empty)
            ts_list.erase(1);
            REQUIRE(ts_list.size() == 3);
            REQUIRE_THROWS_AS(
                    ts_list.erase(3),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    ts_list.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
        }

        SECTION("pointer") {
            gsl::linked_list<int *> pint_list;
            int *ptr;
            for (int i = 0; i < 4; i++) {
                ptr = &i;
                pint_list.push_back(ptr);
            }
            REQUIRE(pint_list.size() == 4); // NOLINT(readability-container-size-empty)
            pint_list.erase(1);
            REQUIRE(pint_list.size() == 3);
            REQUIRE_THROWS_AS(
                    pint_list.erase(3),
                    gsl::exceptions::out_of_range
            );
//            REQUIRE(
//                    pint_list.to_string() == "[]"
//            );
        }

        SECTION("custom pointer") {
            gsl::linked_list<test_struct *> pts_list;
            test_struct *ts;
            for (int i = 0; i < 4; i++) {
                test_struct testStruct;
                ts = &testStruct;
                pts_list.push_back(ts);
            }
            REQUIRE(pts_list.size() == 4); // NOLINT(readability-container-size-empty)
            pts_list.erase(1);
            REQUIRE(pts_list.size() == 3);
            REQUIRE_THROWS_AS(
                    pts_list.erase(4),
                    gsl::exceptions::out_of_range
            );
//            REQUIRE(
//                    pts_list.to_string() == "[]"
//            );
        }
    }

    SECTION("Erase(int first, int last) tests") {
        SECTION("integer") {
            gsl::linked_list<int> int_list;
            for (int i = 0; i < 7; i++) { int_list.push_back(1); }
            REQUIRE(int_list.size() == 7); // NOLINT(readability-container-size-empty)
            int_list.erase(2,4);
            REQUIRE(int_list.size() == 4);
            REQUIRE_THROWS_AS(
                    int_list.erase(1,4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    int_list.to_string() == "[1, 1, 1, 1]"
            );
        }

        SECTION("custom structure") {
            gsl::linked_list<test_struct> ts_list;
            for (int i = 0; i < 7; i++) { ts_list.push_back(test_struct{}); }
            REQUIRE(ts_list.size() == 7); // NOLINT(readability-container-size-empty)
            ts_list.erase(2,4);
            REQUIRE(ts_list.size() == 4);
            REQUIRE_THROWS_AS(
                    ts_list.erase(1,4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    ts_list.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
        }

        SECTION("pointer") {
            gsl::linked_list<int *> pint_list;
            int *ptr;
            for (int i = 0; i < 7; i++) {
                ptr = &i;
                pint_list.push_back(ptr);
            }
            REQUIRE(pint_list.size() == 7); // NOLINT(readability-container-size-empty)
            pint_list.erase(2,4);
            REQUIRE(pint_list.size() == 4);
            REQUIRE_THROWS_AS(
                    pint_list.erase(1,4),
                    gsl::exceptions::out_of_range
            );
//            REQUIRE(
//                    pint_list.to_string() == "[]"
//            );
        }

        SECTION("custom pointer") {
            gsl::linked_list<test_struct *> pts_list;
            test_struct *ts;
            for (int i = 0; i < 7; i++) {
                test_struct testStruct;
                ts = &testStruct;
                pts_list.push_back(ts);
            }
            REQUIRE(pts_list.size() == 7); // NOLINT(readability-container-size-empty)
            pts_list.erase(2,4);
            REQUIRE(pts_list.size() == 4);
            REQUIRE_THROWS_AS(
                    pts_list.erase(1,4),
                    gsl::exceptions::out_of_range
            );
//            REQUIRE(
//                    pts_list.to_string() == "[]"
//            );
        }
    }


}