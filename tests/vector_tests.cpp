//
// Created by MrMam on 31.10.2022.
//

#include <containers/vector.hpp>
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

    [[nodiscard]] std::string to_string() const {
        std::ostringstream res;
        res << value << " " << flag;
        return res.str();
    }
};

TEST_CASE("vector_tests") {
    SECTION("Empty test") {
        SECTION("integer") {
            gsl::vector<int> int_vector;
            REQUIRE(int_vector.empty());
            REQUIRE(int_vector.size() == 0); // NOLINT(readability-container-size-empty)
            REQUIRE(int_vector.capacity() == 1);
            REQUIRE_THROWS_AS(
                    int_vector[1],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    int_vector.to_string() == "[]"
            );
        }
        SECTION("custom structure") {
            gsl::vector<test_struct> ts_vector;
            REQUIRE(ts_vector.empty());
            REQUIRE(ts_vector.size() == 0); // NOLINT(readability-container-size-empty)
            REQUIRE(ts_vector.capacity() == 1);
            REQUIRE_THROWS_AS(
                    ts_vector[1],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    ts_vector.to_string() == "[]"
            );
        }
        SECTION("pointer") {
            gsl::vector<int *> pint_vector;
            REQUIRE(pint_vector.empty());
            REQUIRE(pint_vector.size() == 0); // NOLINT(readability-container-size-empty)
            REQUIRE(pint_vector.capacity() == 1);
            REQUIRE_THROWS_AS(
                    *pint_vector[1],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pint_vector.to_string() == "[]"
            );
        }
        SECTION("custom pointer") {
            gsl::vector<test_struct *> pts_vector;
            REQUIRE(pts_vector.empty());
            REQUIRE(pts_vector.size() == 0); // NOLINT(readability-container-size-empty)
            REQUIRE(pts_vector.capacity() == 1);
            REQUIRE_THROWS_AS(
                    *pts_vector[1],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_vector.to_string() == "[]"
            );
        }
    }

    SECTION("Push_back test") {
        SECTION("integer") {
            gsl::vector<int> int_vector;
            for (int i = 0; i < 3; i++)
                int_vector.push_back(i);
            REQUIRE(int_vector.size() == 3);
            REQUIRE_THROWS_AS(
                    int_vector[3],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    int_vector.to_string() == "[0, 1, 2]"
            );
        }
        SECTION("custom structure") {
            gsl::vector<test_struct> ts_vector;
            for (int i = 0; i < 3; i++)
                ts_vector.push_back(test_struct{});
            REQUIRE(ts_vector.size() == 3);
            REQUIRE_THROWS_AS(
                    ts_vector[3],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    ts_vector.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
        }
        SECTION("pointer") {
            gsl::vector<int *> pint_vector;
            int *ptr1 = new int(3);
            int *ptr2 = new int(4);
            for (int i = 0; i < 2; ++i)
                pint_vector.push_back(ptr1);
            pint_vector.push_back(ptr2);
            REQUIRE(pint_vector.size() == 3);
            REQUIRE_THROWS_AS(
                    pint_vector[3],
                    gsl::exceptions::out_of_range
            );

            REQUIRE(
                    pint_vector.to_string() == "[3, 3, 4]"
            );
            delete ptr1;
            delete ptr2;
        }

        SECTION("custom pointer") {
            gsl::vector<test_struct *> pts_vector;
            auto *ts = new test_struct(test_struct{});
            for (int i = 0; i < 3; i++) {
                pts_vector.push_back(ts);
            }
            REQUIRE(pts_vector.size() == 3);
            REQUIRE_THROWS_AS(
                    pts_vector[3],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_vector.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
            delete ts;
        }

    }

    SECTION("Push_front test") {
        SECTION("integer") {
            gsl::vector<int> int_vector;
            for (int i = 0; i < 2; ++i) {
                int_vector.push_back(i);
            }
            REQUIRE(int_vector.size() == 2);
            int_vector.push_front(2);
            REQUIRE(int_vector.size() == 3);
            REQUIRE_THROWS_AS(
                    int_vector[3],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    int_vector.to_string() == "[2, 0, 1]"
            );
        }

        SECTION("custom structure") {
            gsl::vector<test_struct> ts_vector;
            for (int i = 0; i < 2; ++i) {
                ts_vector.push_back(test_struct{});
            }
            REQUIRE(ts_vector.size() == 2);
            ts_vector.push_front(test_struct{});
            REQUIRE(ts_vector.size() == 3);
            REQUIRE_THROWS_AS(
                    ts_vector[3],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    ts_vector.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
        }

        SECTION("pointer") {
            gsl::vector<int *> pint_vector;
            int *ptr1 = new int(3);
            int *ptr2 = new int(4);
            for (int i = 0; i < 3; ++i)
                pint_vector.push_back(ptr1);
            REQUIRE(pint_vector.size() == 3);
            pint_vector.push_front(ptr2);
            REQUIRE(pint_vector.size() == 4);
            REQUIRE_THROWS_AS(
                    pint_vector[4],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pint_vector.to_string() == "[4, 3, 3, 3]"
            );
            delete ptr1;
            delete ptr2;
        }

        SECTION("custom pointer") {
            gsl::vector<test_struct *> pts_vector;
            auto *ts = new test_struct(test_struct{});
            for (int i = 0; i < 2; i++) {
                pts_vector.push_back(ts);
            }
            REQUIRE(pts_vector.size() == 2);
            pts_vector.push_front(ts);
            REQUIRE(pts_vector.size() == 3);
            REQUIRE_THROWS_AS(
                    pts_vector[3],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_vector.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
            delete ts;
        }
    }

    SECTION ("Pop_back test") {
        SECTION ("integer") {
            gsl::vector<int> int_vector;
            for (int i = 0; i < 3; ++i)
                int_vector.push_back(i);
            REQUIRE(int_vector.size() == 3);
            int_vector.pop_back();
            REQUIRE(int_vector.size() == 2);
            REQUIRE_THROWS_AS(
                    int_vector[2],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    int_vector.to_string() == "[0, 1]"
            );
        }
        SECTION ("custom structure") {
            gsl::vector<test_struct> ts_vector;
            for (int i = 0; i < 3; i++)
                ts_vector.push_back(test_struct{});
            REQUIRE(ts_vector.size() == 3);
            ts_vector.pop_back();
            REQUIRE(ts_vector.size() == 2);
            REQUIRE_THROWS_AS(
                    ts_vector[2],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    ts_vector.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
        }
        SECTION ("pointer") {
            gsl::vector<int *> pint_vector;
            int *ptr1 = new int(3);
            for (int i = 0; i < 3; ++i)
                pint_vector.push_back(ptr1);
            REQUIRE(pint_vector.size() == 3);
            pint_vector.pop_back();
            REQUIRE_THROWS_AS(
                    pint_vector[2],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pint_vector.to_string() == "[3, 3]"
            );
            delete ptr1;
        }
        SECTION("custom pointer") {
            gsl::vector<test_struct *> pts_vector;
            auto *ts = new test_struct(test_struct{});
            for (int i = 0; i < 3; i++) {
                pts_vector.push_back(ts);
            }
            REQUIRE(pts_vector.size() == 3);
            pts_vector.pop_back();
            REQUIRE_THROWS_AS(
                    pts_vector[2],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_vector.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
            delete ts;
        }
    }

    SECTION ("Pop_front test") {
        SECTION ("integer") {
            gsl::vector<int> int_vector;
            for (int i = 0; i < 3; i++)
                int_vector.push_back(i);
            REQUIRE(int_vector.size() == 3);
            int_vector.pop_front();
            REQUIRE(int_vector.size() == 2);
            REQUIRE_THROWS_AS(
                    int_vector[2],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    int_vector.to_string() == "[1, 2]"
            );
        }
        SECTION ("custom structure") {
            gsl::vector<test_struct> ts_vector;
            for (int i = 0; i < 3; ++i) {
                ts_vector.push_back(test_struct{});
            }
            REQUIRE(ts_vector.size() == 3);
            ts_vector.pop_front();
            REQUIRE(ts_vector.size() == 2);
            REQUIRE_THROWS_AS(
                    ts_vector[2],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    ts_vector.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
        }
        SECTION ("pointer") {
            gsl::vector<int *> pint_vector;
            int *ptr1 = new int(3);
            for (int i = 0; i < 3; ++i)
                pint_vector.push_back(ptr1);
            REQUIRE(pint_vector.size() == 3);
            pint_vector.pop_front();
            REQUIRE(pint_vector.size() == 2);
            REQUIRE_THROWS_AS(
                    pint_vector[2],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pint_vector.to_string() == "[3, 3]"
            );
            delete ptr1;
        }
        SECTION ("custom pointer") {
            gsl::vector<test_struct *> pts_vector;
            auto *ts = new test_struct(test_struct{});
            for (int i = 0; i < 3; i++) {
                pts_vector.push_back(ts);
            }
            REQUIRE(pts_vector.size() == 3);
            pts_vector.pop_front();
            REQUIRE_THROWS_AS(
                    pts_vector[2],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_vector.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
            delete ts;
        }
    }

    SECTION ("Resize test (size_t new_size)") {
        SECTION ("integer") {
            gsl::vector<int> int_vector;
            for (int i = 0; i < 3; ++i) {
                int_vector.push_back(i);
            }
            int_vector.resize(6);
            REQUIRE(int_vector.size() == 3);
            REQUIRE(int_vector.capacity() == 6);
            REQUIRE_THROWS_AS(
                    int_vector[6],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    int_vector.to_string() == "[0, 1, 2]"
            );
        }

        SECTION ("custom structure") {
            gsl::vector<test_struct> ts_vector;
            for (int i = 0; i < 3; ++i)
                ts_vector.push_back(test_struct{});
            ts_vector.resize(6);
            REQUIRE(ts_vector.size() == 3);
            REQUIRE(ts_vector.capacity() == 6);
            REQUIRE_THROWS_AS(
                    ts_vector[6],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    ts_vector.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
        }

        SECTION ("pointer") {
            gsl::vector<int *> pint_vector;
            int *ptr1 = new int(3);
            for (int i = 0; i < 3; ++i)
                pint_vector.push_back(ptr1);
            pint_vector.resize(6);
            REQUIRE(pint_vector.size() == 3);
            REQUIRE(pint_vector.capacity() == 6);
            REQUIRE_THROWS_AS(
                    pint_vector[6],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pint_vector.to_string() == "[3, 3, 3]"
            );
            delete ptr1;
        }

        SECTION ("custom pointer") {
            gsl::vector<test_struct *> pts_vector;
            auto *ts = new test_struct(test_struct{});
            for (int i = 0; i < 3; i++) {
                pts_vector.push_back(ts);
            }
            pts_vector.resize(6);
            REQUIRE(pts_vector.size() == 3);
            REQUIRE(pts_vector.capacity() == 6);
            REQUIRE_THROWS_AS(
                    pts_vector[6],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_vector.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
            delete ts;
        }
    }

    SECTION ("Resize test (size_t new_size, const T& value") {
        SECTION("integer") {
            gsl::vector<int> int_vector;
            for (int i = 0; i < 3; ++i) {
                int_vector.push_back(i);
            }
            REQUIRE(int_vector.size() == 3);
            int_vector.resize(6, 9);
            REQUIRE(int_vector.size() == 6);
            REQUIRE_THROWS_AS(
                    int_vector[6],
                    gsl::exceptions::out_of_range
                );
            REQUIRE(int_vector.to_string() == "[0, 1, 2, 9, 9, 9]"
                );
        }

        SECTION("custom structure") {
            gsl::vector<test_struct> ts_vector;
            for (int i = 0; i < 3; ++i) {
                ts_vector.push_back(test_struct{});
            }
            REQUIRE(ts_vector.size() == 3);
            ts_vector.resize(6, test_struct{});
            REQUIRE(ts_vector.size() == 6);
            REQUIRE_THROWS_AS(
                    ts_vector[6],
                    gsl::exceptions::out_of_range
                    );
            REQUIRE(
                    ts_vector.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
                    );
        }
        SECTION("pointer") {
            gsl::vector<int *> pint_vector;
            int *ptr1 = new int(3);
            for (int i = 0; i < 3; ++i)
                pint_vector.push_back(ptr1);
            REQUIRE(pint_vector.size() == 3);
            pint_vector.resize(6, ptr1);
            REQUIRE(pint_vector.size() == 6);
            REQUIRE_THROWS_AS(
                    pint_vector[6],
                    gsl::exceptions::out_of_range
                    );
            REQUIRE(
                    pint_vector.to_string() == "[3, 3, 3, 3, 3, 3]"
                    );
            delete ptr1;
        }

        SECTION ("custom pointer") {
            gsl::vector<test_struct *> pts_vector;
            auto *ts = new test_struct(test_struct{});
            for (int i = 0; i < 3; i++) {
                pts_vector.push_back(ts);
            }
            REQUIRE(pts_vector.size() == 3);
            pts_vector.resize(6, ts);
            REQUIRE(pts_vector.size() == 6);
            REQUIRE_THROWS_AS(
                    pts_vector[6],
                    gsl::exceptions::out_of_range
                    );
            REQUIRE(
                    pts_vector.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
                    );
            delete ts;
        }
    }

    SECTION("Insert test") {
        SECTION("integer") {
            gsl::vector<int> int_vector;
            for (int i = 0; i < 3; i++) { int_vector.push_back(i); }
            REQUIRE(int_vector.size() == 3);
            int_vector.insert(67, 1);
            REQUIRE_THROWS_AS(
                    int_vector.insert(3, 4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(int_vector.size() == 4);
            REQUIRE(
                    int_vector.to_string() == "[0, 67, 1, 2]"
            );
        }

        SECTION("custom structure") {
            gsl::vector<test_struct> ts_vector;
            for (int i = 0; i < 3; i++) { ts_vector.push_back(test_struct{}); }
            REQUIRE(ts_vector.size() == 3);
            ts_vector.insert(test_struct{}, 1);
            REQUIRE_THROWS_AS(
                    ts_vector.insert(test_struct{}, 4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(ts_vector.size() == 4);
            REQUIRE(
                    ts_vector.to_string() ==
                    "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
        }

        SECTION("pointer") {
            gsl::vector<int *> pint_vector;
            int* ptr1 = new int (3);
            int* ptr2 = new int (4);
            for (int i = 0; i<3;++i)
                pint_vector.push_back(ptr1);
            REQUIRE(pint_vector.size() == 3);
            pint_vector.insert(ptr2, 1);
            REQUIRE(pint_vector.size() == 4);
            REQUIRE_THROWS_AS(
                    pint_vector.insert(ptr2, 4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pint_vector.to_string() == "[3, 4, 3, 3]"
            );
            delete ptr1;
            delete ptr2;
        }

        SECTION("custom pointer") {
            gsl::vector<test_struct *> pts_vector;
            auto *ts = new test_struct (test_struct{});
            for (int i = 0; i < 3; i++) {
                pts_vector.push_back(ts);
            }
            REQUIRE(pts_vector.size() == 3);
            pts_vector.insert(ts, 1);
            REQUIRE(pts_vector.size() == 4);
            REQUIRE_THROWS_AS(
                    pts_vector.insert(ts, 4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_vector.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
            delete ts;
        }
    }

    SECTION ("Erase test(size_t index)") {
        SECTION("integer") {
            gsl::vector<int> int_vector;
            for (int i = 0; i < 4; i++) { int_vector.push_back(i); }
            REQUIRE(int_vector.size() == 4);
            int_vector.erase(1);
            REQUIRE(int_vector.size() == 3);
            REQUIRE_THROWS_AS(
                    int_vector.erase(3),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    int_vector.to_string() == "[0, 2, 3]"
            );
        }

        SECTION("custom structure") {
            gsl::vector<test_struct> ts_vector;
            for (int i = 0; i < 4; i++) { ts_vector.push_back(test_struct{}); }
            REQUIRE(ts_vector.size() == 4);
            ts_vector.erase(1);
            REQUIRE(ts_vector.size() == 3);
            REQUIRE_THROWS_AS(
                    ts_vector.erase(3),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    ts_vector.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
        }

        SECTION("pointer") {
            gsl::vector<int *> pint_vector;
            int* ptr1 = new int (3);
            for (int i = 0; i<4;++i)
                pint_vector.push_back(ptr1);
            REQUIRE(pint_vector.size() == 4);
            pint_vector.erase(1);
            REQUIRE(pint_vector.size() == 3);
            REQUIRE_THROWS_AS(
                    pint_vector.erase(3),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pint_vector.to_string() == "[3, 3, 3]"
            );
            delete ptr1;
        }

        SECTION("custom pointer") {
            gsl::vector<test_struct *> pts_vector;
            auto *ts = new test_struct (test_struct{});
            for (int i = 0; i < 4; i++) {
                pts_vector.push_back(ts);
            }
            REQUIRE(pts_vector.size() == 4);
            pts_vector.erase(1);
            REQUIRE(pts_vector.size() == 3);
            REQUIRE_THROWS_AS(
                    pts_vector.erase(4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_vector.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
            delete ts;
        }
    }

    SECTION ("Erase test(size_t first, size_t last)") {
        SECTION("integer") {
            gsl::vector<int> int_vector;
            for (int i = 0; i < 7; i++) { int_vector.push_back(i); }
            REQUIRE(int_vector.size() == 7);
            int_vector.erase(2, 4);
            REQUIRE(int_vector.size() == 4);
            REQUIRE_THROWS_AS(
                    int_vector.erase(1, 4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    int_vector.to_string() == "[0, 1, 5, 6]"
            );
        }

        SECTION("custom structure") {
            gsl::vector<test_struct> ts_vector;
            for (int i = 0; i < 7; i++) { ts_vector.push_back(test_struct{}); }
            REQUIRE(ts_vector.size() == 7);
            ts_vector.erase(2, 4);
            REQUIRE(ts_vector.size() == 4);
            REQUIRE_THROWS_AS(
                    ts_vector.erase(1, 4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    ts_vector.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
        }

        SECTION("pointer") {
            gsl::vector<int *> pint_vector;
            int* ptr1 = new int (3);
            for (int i = 0; i<7;++i)
                pint_vector.push_back(ptr1);
            REQUIRE(pint_vector.size() == 7);
            pint_vector.erase(2,4);
            REQUIRE(pint_vector.size() == 4);
            REQUIRE_THROWS_AS(
                    pint_vector.erase(1,4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pint_vector.to_string() == "[3, 3, 3, 3]"
            );
            delete ptr1;
        }

        SECTION("custom pointer") {
            gsl::vector<test_struct *> pts_vector;
            auto *ts = new test_struct (test_struct{});
            for (int i = 0; i < 7; i++) {
                pts_vector.push_back(ts);
            }
            REQUIRE(pts_vector.size() == 7);
            pts_vector.erase(2, 4);
            REQUIRE(pts_vector.size() == 4);
            REQUIRE_THROWS_AS(
                    pts_vector.erase(1, 4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_vector.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
            delete ts;
        }
    }

    SECTION ("Clear test") {
        SECTION("integer"){
            gsl::vector<int> int_vector;
            for (int i = 0; i < 7; i++) { int_vector.push_back(i); }
            REQUIRE(int_vector.size() == 7);
            int_vector.clear();
            REQUIRE(int_vector.empty());
            REQUIRE_THROWS_AS(
                    int_vector[1],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    int_vector.to_string() == "[]"
            );
        }

        SECTION("custom structure") {
            gsl::vector<test_struct> ts_vector;
            for (int i = 0; i < 7; i++) { ts_vector.push_back(test_struct{}); }
            REQUIRE(ts_vector.size() == 7);
            ts_vector.clear();
            REQUIRE(ts_vector.empty());
            REQUIRE_THROWS_AS(
                    ts_vector[1],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    ts_vector.to_string() == "[]"
            );
        }

        SECTION("pointer") {
            gsl::vector<int *> pint_vector;
            int *ptr = new int(7);
            for (int i = 0; i < 7; i++) {
                pint_vector.push_back(ptr);
            }
            REQUIRE(pint_vector.size() == 7);
            pint_vector.clear();
            REQUIRE(pint_vector.empty());
            REQUIRE_THROWS_AS(
                    pint_vector[1],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pint_vector.to_string() == "[]"
            );
        }

        SECTION ("custom pointer") {
            gsl::vector<test_struct *> pts_vector;
            auto *ts = new test_struct(test_struct{});
            for (int i = 0; i < 7; i++) {
                pts_vector.push_back(ts);
            }
            REQUIRE(pts_vector.size() == 7);
            pts_vector.clear();
            REQUIRE(pts_vector.empty());
            REQUIRE_THROWS_AS(
                    pts_vector[1],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_vector.to_string() == "[]"
            );
        }
    }

    SECTION ("Iterator test") {
        SECTION ("integer") {
            gsl::vector<int> int_vector;
            for (size_t i = 0; i<5; ++i) {int_vector.push_back(i); }
            REQUIRE(int_vector.size() == 5);
            size_t i = 0;
            for (auto it = int_vector.begin(); it != int_vector.end(); ++it) {
                REQUIRE(*it == i);
                i++;
            }
            REQUIRE (int_vector.to_string() == "[0, 1, 2, 3, 4]");

            std::ostringstream test_out;
            for (auto it = int_vector.begin(); it != int_vector.end(); ++it) {
                test_out << *it << " ";
            }
            REQUIRE(test_out.str() == "0 1 2 3 4 ");
        }
        SECTION ("custom structure") {
            gsl::vector<test_struct> ts_vector;
            for (int i = 0; i < 5; i++) { ts_vector.push_back(test_struct{}); }
            REQUIRE(ts_vector.size() == 5);
            size_t i = 0;
            for (auto it = ts_vector.begin(); it != ts_vector.end(); ++it) {
                REQUIRE(it->to_string() == "10 1");
            }
            REQUIRE(
                    ts_vector.to_string() ==
                    "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );

            std::ostringstream test_out;
            for (auto it = ts_vector.begin(); it != ts_vector.end(); ++it) {
                test_out << *it << " ";
            }
            REQUIRE(test_out.str() ==
                    "{ value: 10 flag: 1 } { value: 10 flag: 1 } { value: 10 flag: 1 } { value: 10 flag: 1 } { value: 10 flag: 1 } ");
        }
    }
}