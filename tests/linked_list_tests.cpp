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

    SECTION("Push_back test") {
        SECTION("integer") {
            gsl::linked_list<int> int_list;
            for (int i = 0; i < 3; ++i)
                int_list.push_back(i);
            REQUIRE(int_list.size() == 3);
            REQUIRE_THROWS_AS(
                    int_list[3],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    int_list.to_string() == "[0, 1, 2]"
            );
        }

        SECTION("custom structure") {
            gsl::linked_list<test_struct> ts_list;
            for (int i = 0; i < 3; ++i) {
                ts_list.push_back(test_struct{});
            }
            REQUIRE(ts_list.size() == 3);
            REQUIRE_THROWS_AS(
                    ts_list[3],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    ts_list.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
        }

        SECTION("pointer") {
            gsl::linked_list<int *> pint_list;
            int* ptr1 = new int (3);
            int* ptr2 = new int (4);
            for (int i = 0; i<2;++i)
                pint_list.push_back(ptr1);
            pint_list.push_back(ptr2);
            REQUIRE(pint_list.size() == 3);
            REQUIRE_THROWS_AS(
                    pint_list[3],
                    gsl::exceptions::out_of_range
            );

            REQUIRE(
                    pint_list.to_string() == "[3, 3, 4]"
            );
            delete ptr1;
            delete ptr2;
        }

        SECTION("custom pointer") {
            gsl::linked_list<test_struct *> pts_list;
            auto *ts = new test_struct (test_struct{});
            for (int i = 0; i < 3; i++) {
                pts_list.push_back(ts);
            }
            REQUIRE(pts_list.size() == 3);
            REQUIRE_THROWS_AS(
                    pts_list[3],
                    gsl::exceptions::out_of_range
            );
                        REQUIRE(
                    pts_list.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
            delete ts;
        }
    }

    SECTION("Push_front test") {
        SECTION("integer") {
            gsl::linked_list<int> int_list;
            for (int i = 0; i < 2; ++i) {
                int_list.push_back(i);
            }
            REQUIRE(int_list.size() == 2);
            int_list.push_front(2);
            REQUIRE(int_list.size() == 3);
            REQUIRE_THROWS_AS(
                    int_list[3],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    int_list.to_string() == "[2, 0, 1]"
            );
        }

        SECTION("custom structure") {
            gsl::linked_list<test_struct> ts_list;
            for (int i = 0; i < 2; ++i) {
                ts_list.push_back(test_struct{});
            }
            REQUIRE(ts_list.size() == 2);
            ts_list.push_front(test_struct{});
            REQUIRE(ts_list.size() == 3);
            REQUIRE_THROWS_AS(
                    ts_list[3],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    ts_list.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
        }

        SECTION("pointer") {
            gsl::linked_list<int *> pint_list;
            int* ptr1 = new int (3);
            int* ptr2 = new int (4);
            for (int i = 0; i<3;++i)
                pint_list.push_back(ptr1);
            REQUIRE(pint_list.size() == 3);
            pint_list.push_front(ptr2);
            REQUIRE(pint_list.size() == 4);
            REQUIRE_THROWS_AS(
                    pint_list[4],
                    gsl::exceptions::out_of_range
            );

            REQUIRE(
                    pint_list.to_string() == "[4, 3, 3, 3]"
            );
            delete ptr1;
            delete ptr2;
        }

        SECTION("custom pointer") {
            gsl::linked_list<test_struct *> pts_list;
            auto *ts = new test_struct (test_struct{});
            for (int i = 0; i < 2; i++) {
                pts_list.push_back(ts);
            }
            REQUIRE(pts_list.size() == 2);
            pts_list.push_front(ts);
            REQUIRE(pts_list.size() == 3);
            REQUIRE_THROWS_AS(
                    pts_list[3],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_list.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
            delete ts;
        }
    }

    SECTION("Pop_back test") {
        SECTION("integer") {
            gsl::linked_list<int> int_list;
            for (int i = 0; i < 3; ++i) {
                int_list.push_back(i);
            }
            REQUIRE(int_list.size() == 3);
            int_list.pop_back();
            REQUIRE(int_list.size() == 2);
            REQUIRE_THROWS_AS(
                    int_list[2],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    int_list.to_string() == "[0, 1]"
            );
        }

        SECTION("custom structure") {
            gsl::linked_list<test_struct> ts_list;
            for (int i = 0; i < 3; ++i) {
                ts_list.push_back(test_struct{});
            }
            REQUIRE(ts_list.size() == 3);
            ts_list.pop_back();
            REQUIRE(ts_list.size() == 2);
            REQUIRE_THROWS_AS(
                    ts_list[2],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    ts_list.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
        }

        SECTION("pointer") {

            gsl::linked_list<int *> pint_list;
            int* ptr1 = new int (3);
            for (int i = 0; i<3;++i)
                pint_list.push_back(ptr1);

            REQUIRE(pint_list.size() == 3);
            pint_list.pop_back();
            REQUIRE_THROWS_AS(
                    pint_list[2],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pint_list.to_string() == "[3, 3]"
            );
            delete ptr1;
        }

        SECTION("custom pointer") {
            gsl::linked_list<test_struct *> pts_list;
            auto *ts = new test_struct (test_struct{});
            for (int i = 0; i < 3; i++) {
                pts_list.push_back(ts);
            }
            REQUIRE(pts_list.size() == 3);
            pts_list.pop_back();
            REQUIRE_THROWS_AS(
                    pts_list[2],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_list.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
            delete ts;
        }
    }

    SECTION("Pop_front test") {
        SECTION("integer") {
            gsl::linked_list<int> int_list;
            for (int i = 0; i < 3; ++i) {
                int_list.push_back(i);
            }
            REQUIRE(int_list.size() == 3);
            int_list.pop_front();
            REQUIRE(int_list.size() == 2);
            REQUIRE_THROWS_AS(
                    int_list[2],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    int_list.to_string() == "[1, 2]"
            );
        }

        SECTION("custom structure") {
            gsl::linked_list<test_struct> ts_list;
            for (int i = 0; i < 3; ++i) {
                ts_list.push_back(test_struct{});
            }
            REQUIRE(ts_list.size() == 3);
            ts_list.pop_front();
            REQUIRE(ts_list.size() == 2);
            REQUIRE_THROWS_AS(
                    ts_list[2],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    ts_list.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
        }

        SECTION("pointer") {
            gsl::linked_list<int *> pint_list;
            int* ptr1 = new int (3);
            for (int i = 0; i<3;++i)
                pint_list.push_back(ptr1);
            REQUIRE(pint_list.size() == 3);
            pint_list.pop_front();
            REQUIRE(pint_list.size() == 2);
            REQUIRE_THROWS_AS(
                    pint_list[2],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pint_list.to_string() == "[3, 3]"
            );
            delete ptr1;
        }

        SECTION("custom pointer") {
            gsl::linked_list<test_struct *> pts_list;
            auto *ts = new test_struct (test_struct{});
            for (int i = 0; i < 3; i++) {
                pts_list.push_back(ts);
            }
            REQUIRE(pts_list.size() == 3);
            pts_list.pop_front();
            REQUIRE_THROWS_AS(
                    pts_list[2],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_list.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
            delete ts;
        }
    }

    SECTION("Resize test (size_t new_size)") {
        SECTION("integer") {
            gsl::linked_list<int> int_list;
            for (int i = 0; i < 3; ++i) {
                int_list.push_back(i);
            }
            REQUIRE(int_list.size() == 3);
            int_list.resize(6);
            REQUIRE(int_list.size() == 6);
            REQUIRE_THROWS_AS(
                    int_list[6],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    int_list.to_string() == "[0, 1, 2, 0, 0, 0]"
            );
        }

        SECTION("custom structure") {
            gsl::linked_list<test_struct> ts_list;
            for (int i = 0; i < 3; ++i) {
                ts_list.push_back(test_struct{});
            }
            REQUIRE(ts_list.size() == 3);
            ts_list.resize(6);
            REQUIRE(ts_list.size() == 6);
            REQUIRE_THROWS_AS(
                    ts_list[6],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    ts_list.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
        }

        SECTION("pointer") {
            gsl::linked_list<int *> pint_list;
            int* ptr1 = new int (3);
            for (int i = 0; i<3;++i)
                pint_list.push_back(ptr1);
            REQUIRE(pint_list.size() == 3);
            pint_list.resize(5);
            REQUIRE(pint_list.size() == 5);
            REQUIRE_THROWS_AS(
                    pint_list[6],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pint_list.to_string() == "[3, 3, 3, nullptr, nullptr]"
            );
            delete ptr1;
        }

        SECTION ("custom pointer"){
            gsl::linked_list<test_struct *> pts_list;
            auto *ts = new test_struct (test_struct{});
            for (int i = 0; i < 3; i++) {
                pts_list.push_back(ts);
            }
            REQUIRE(pts_list.size() == 3);
            pts_list.resize(6);
            REQUIRE(pts_list.size() == 6);
            REQUIRE_THROWS_AS(
                    pts_list[6],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_list.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, nullptr, nullptr, nullptr]"
            );
            delete ts;
        }
    }

    SECTION("Resize test (size_t new_size, const T& value)") {
        SECTION("integer") {
            gsl::linked_list<int> int_list;
            for (int i = 0; i < 3; ++i) {
                int_list.push_back(i);
            }
            REQUIRE(int_list.size() == 3);
            int_list.resize(6,9);
            REQUIRE(int_list.size() == 6);
            REQUIRE_THROWS_AS(
                    int_list[6],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    int_list.to_string() == "[0, 1, 2, 9, 9, 9]"
            );
        }

        SECTION("custom structure") {
            gsl::linked_list<test_struct> ts_list;
            for (int i = 0; i < 3; ++i) {
                ts_list.push_back(test_struct{});
            }
            REQUIRE(ts_list.size() == 3);
            ts_list.resize(6,test_struct{});
            REQUIRE(ts_list.size() == 6);
            REQUIRE_THROWS_AS(
                    ts_list[6],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    ts_list.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
        }

        SECTION("pointer") {
            gsl::linked_list<int *> pint_list;
            int* ptr1 = new int (3);
            for (int i = 0; i<3;++i)
                pint_list.push_back(ptr1);
            REQUIRE(pint_list.size() == 3);
            pint_list.resize(6,ptr1);
            REQUIRE(pint_list.size() == 6);
            REQUIRE_THROWS_AS(
                    pint_list[6],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pint_list.to_string() == "[3, 3, 3, 3, 3, 3]"
            );
            delete ptr1;
        }

        SECTION ("custom pointer") {
            gsl::linked_list<test_struct *> pts_list;
            auto *ts = new test_struct (test_struct{});
            for (int i = 0; i < 3; i++) {
                pts_list.push_back(ts);
            }
            REQUIRE(pts_list.size() == 3);
            pts_list.resize(6,ts);
            REQUIRE(pts_list.size() == 6);
            REQUIRE_THROWS_AS(
                    pts_list[6],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_list.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
            delete ts;
        }
    }

    SECTION("Insert test") {
        SECTION("integer") {
            gsl::linked_list<int> int_list;
            for (int i = 0; i < 3; i++) { int_list.push_back(i); }
            REQUIRE(int_list.size() == 3);
            int_list.insert(67, 1);
            REQUIRE_THROWS_AS(
                    int_list.insert(3, 4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(int_list.size() == 4);
            REQUIRE(
                    int_list.to_string() == "[0, 67, 1, 2]"
            );
        }

        SECTION("custom structure") {
            gsl::linked_list<test_struct> ts_list;
            for (int i = 0; i < 3; i++) { ts_list.push_back(test_struct{}); }
            REQUIRE(ts_list.size() == 3);
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
            int* ptr1 = new int (3);
            int* ptr2 = new int (4);
            for (int i = 0; i<3;++i)
                pint_list.push_back(ptr1);
            REQUIRE(pint_list.size() == 3);
            pint_list.insert(ptr2, 1);
            REQUIRE(pint_list.size() == 4);
            REQUIRE_THROWS_AS(
                    pint_list.insert(ptr2, 4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pint_list.to_string() == "[3, 4, 3, 3]"
            );
            delete ptr1;
            delete ptr2;
        }

        SECTION("custom pointer") {
            gsl::linked_list<test_struct *> pts_list;
            auto *ts = new test_struct (test_struct{});
            for (int i = 0; i < 3; i++) {
                pts_list.push_back(ts);
            }
            REQUIRE(pts_list.size() == 3);
            pts_list.insert(ts, 1);
            REQUIRE(pts_list.size() == 4);
            REQUIRE_THROWS_AS(
                    pts_list.insert(ts, 4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_list.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
            delete ts;
        }
    }

    SECTION("Erase(size_t index) test") {
        SECTION("integer") {
            gsl::linked_list<int> int_list;
            for (int i = 0; i < 4; i++) { int_list.push_back(i); }
            REQUIRE(int_list.size() == 4);
            int_list.erase(1);
            REQUIRE(int_list.size() == 3);
            REQUIRE_THROWS_AS(
                    int_list.erase(3),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    int_list.to_string() == "[0, 2, 3]"
            );
        }

        SECTION("custom structure") {
            gsl::linked_list<test_struct> ts_list;
            for (int i = 0; i < 4; i++) { ts_list.push_back(test_struct{}); }
            REQUIRE(ts_list.size() == 4);
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
            int* ptr1 = new int (3);
            for (int i = 0; i<4;++i)
                pint_list.push_back(ptr1);
            REQUIRE(pint_list.size() == 4);
            pint_list.erase(1);
            REQUIRE(pint_list.size() == 3);
            REQUIRE_THROWS_AS(
                    pint_list.erase(3),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pint_list.to_string() == "[3, 3, 3]"
            );
            delete ptr1;
        }

        SECTION("custom pointer") {
            gsl::linked_list<test_struct *> pts_list;
            auto *ts = new test_struct (test_struct{});
            for (int i = 0; i < 4; i++) {
                pts_list.push_back(ts);
            }
            REQUIRE(pts_list.size() == 4);
            pts_list.erase(1);
            REQUIRE(pts_list.size() == 3);
            REQUIRE_THROWS_AS(
                    pts_list.erase(4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_list.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
            delete ts;
        }
    }

    SECTION("Erase(int first, int last) test") {
        SECTION("integer") {
            gsl::linked_list<int> int_list;
            for (int i = 0; i < 7; i++) { int_list.push_back(i); }
            REQUIRE(int_list.size() == 7);
            int_list.erase(2,4);
            REQUIRE(int_list.size() == 4);
            REQUIRE_THROWS_AS(
                    int_list.erase(1,4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    int_list.to_string() == "[0, 1, 5, 6]"
            );
        }

        SECTION("custom structure") {
            gsl::linked_list<test_struct> ts_list;
            for (int i = 0; i < 7; i++) { ts_list.push_back(test_struct{}); }
            REQUIRE(ts_list.size() == 7);
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
            int* ptr1 = new int (3);
            for (int i = 0; i<7;++i)
                pint_list.push_back(ptr1);
            REQUIRE(pint_list.size() == 7);
            pint_list.erase(2,4);
            REQUIRE(pint_list.size() == 4);
            REQUIRE_THROWS_AS(
                    pint_list.erase(1,4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pint_list.to_string() == "[3, 3, 3, 3]"
            );
            delete ptr1;
        }

        SECTION("custom pointer") {
            gsl::linked_list<test_struct *> pts_list;
            auto *ts = new test_struct (test_struct{});
            for (int i = 0; i < 7; i++) {
                pts_list.push_back(ts);
            }
            REQUIRE(pts_list.size() == 7);
            pts_list.erase(2,4);
            REQUIRE(pts_list.size() == 4);
            REQUIRE_THROWS_AS(
                    pts_list.erase(1,4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_list.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
            delete ts;
        }
    }

    SECTION("Clear test") {
        SECTION("integer"){
            gsl::linked_list<int> int_list;
            for (int i = 0; i < 7; i++) { int_list.push_back(i); }
            REQUIRE(int_list.size() == 7);
            int_list.clear();
            REQUIRE(int_list.empty());
            REQUIRE_THROWS_AS(
                    int_list[1],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    int_list.to_string() == "[]"
            );
        }

        SECTION("custom structure") {
            gsl::linked_list<test_struct> ts_list;
            for (int i = 0; i < 7; i++) { ts_list.push_back(test_struct{}); }
            REQUIRE(ts_list.size() == 7);
            ts_list.clear();
            REQUIRE(ts_list.empty());
            REQUIRE_THROWS_AS(
                    ts_list[1],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    ts_list.to_string() == "[]"
            );
        }

        SECTION("pointer") {
            gsl::linked_list<int *> pint_list;
            int *ptr;
            for (int i = 0; i < 7; i++) {
                ptr = &i;
                pint_list.push_back(ptr);
            }
            REQUIRE(pint_list.size() == 7);
            pint_list.clear();
            REQUIRE(pint_list.empty());
            REQUIRE_THROWS_AS(
                    pint_list[1],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pint_list.to_string() == "[]"
            );
        }

        SECTION ("custom pointer") {
            gsl::linked_list<test_struct *> pts_list;
            test_struct *ts = new test_struct(test_struct{});
            for (int i = 0; i < 7; i++) {
                pts_list.push_back(ts);
            }
            REQUIRE(pts_list.size() == 7);
            pts_list.clear();
            REQUIRE(pts_list.empty());
            REQUIRE_THROWS_AS(
                    pts_list[1],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_list.to_string() == "[]"
            );
        }
    }
}