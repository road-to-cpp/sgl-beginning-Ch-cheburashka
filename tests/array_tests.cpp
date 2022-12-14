//
// Created by MrMam on 31.10.2022.
//

#include <iostream>
#include <sstream>


struct test_struct {
    int value = 10;
    bool flag = true;

    bool operator==(test_struct const &other) const {
        return value == other.value && flag == other.flag;
    }

    [[nodiscard]] std::string to_string() const {
        std::stringstream res;
        res << value << " " << flag;
        return res.str();
    }

    friend std::ostream &operator<<(std::ostream &os, test_struct const &ts) {
        os << "{ value: " << ts.value << " flag: " << ts.flag << " }";
        return os;
    }
};

#include <containers/array.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Array Tests") {
    SECTION("Empty tests") {
        SECTION ("integer") {
            gsl::array<int,0> int_array;
            REQUIRE(int_array.empty());
            REQUIRE(int_array.size()==0); // NOLINT(readability-container-size-empty)
            REQUIRE_THROWS_AS(
                    int_array[0],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    int_array.to_string() == "[]"
            );
        }

        SECTION ("custom structure") {
            gsl::array<test_struct,0> ts_array;
            REQUIRE(ts_array.size()==0); // NOLINT(readability-container-size-empty)
            REQUIRE(ts_array.empty());
            REQUIRE_THROWS_AS(
                    ts_array[0],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    ts_array.to_string() == "[]"
            );
        }

        SECTION ("pointer") {
            gsl::array<int*,0> pint_array;
            REQUIRE(pint_array.size()==0); // NOLINT(readability-container-size-empty)
            REQUIRE(pint_array.empty());
            REQUIRE_THROWS_AS(
                    pint_array[0],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pint_array.to_string() == "[]"
            );
        }

        SECTION ("custom pointer") {
            gsl::array<test_struct*,0> pts_array;
            REQUIRE(pts_array.size()==0); // NOLINT(readability-container-size-empty)
            REQUIRE(pts_array.empty());
            REQUIRE_THROWS_AS(
                    pts_array[0],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_array.to_string() == "[]"
            );
        }
    }

    SECTION("Fill test") {
        SECTION ("integer") {
            gsl::array<int,4> int_array;
            REQUIRE(int_array.size()==4);
            int_array.fill(5);
            REQUIRE_THROWS_AS(
                    int_array[4],
                    gsl::exceptions::out_of_range
                    );
            REQUIRE(
                    int_array.to_string() == "[5, 5, 5, 5]"
                    );
        }

        SECTION ("custom structure") {
            gsl::array<test_struct,4> ts_array;
            REQUIRE(ts_array.size()==4);
            ts_array.fill(test_struct{});
            REQUIRE_THROWS_AS(
                    ts_array[4],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    ts_array.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
        }

        SECTION ("pointer") {
            gsl::array<int*,4> pint_array;
            REQUIRE(pint_array.size()==4);
            int* ptr = new int(5);
            pint_array.fill(ptr);
            REQUIRE_THROWS_AS(
                    pint_array[4],
                    gsl::exceptions::out_of_range
                    );
            REQUIRE(
                    pint_array.to_string() == "[5, 5, 5, 5]"
                    );
            delete ptr;
        }

        SECTION ("custom pointer") {
            gsl::array<test_struct*,4> pts_array;
            REQUIRE(pts_array.size()==4);
            auto* ptr = new test_struct (test_struct{});
            pts_array.fill(ptr);
            REQUIRE_THROWS_AS(
                    pts_array[4],
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_array.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
                    );
            delete ptr;
        }
    }

    SECTION("Swap test") {
        SECTION("integer") {
            gsl::array<int,4> int_array_1;
            REQUIRE(int_array_1.size()==4);
            int_array_1.fill(4);

            gsl::array<int,4> int_array_2;
            REQUIRE(int_array_2.size()==4);
            int_array_2.fill(6);

            int_array_1.swap(int_array_2);

            REQUIRE_THROWS_AS(
                    int_array_1[4],
                    gsl::exceptions::out_of_range
            );
            REQUIRE_THROWS_AS(
                    int_array_2[4],
                    gsl::exceptions::out_of_range
            );

            REQUIRE(
                    int_array_1.to_string() == "[6, 6, 6, 6]"
            );

            REQUIRE(
                    int_array_2.to_string() == "[4, 4, 4, 4]"
            );
        }

        SECTION("custom structure") {
            gsl::array<test_struct,4> ts_array_1;
            REQUIRE(ts_array_1.size()==4);
            ts_array_1.fill(test_struct{});

            gsl::array<test_struct,4> ts_array_2;
            REQUIRE(ts_array_2.size()==4);
            ts_array_2.fill(test_struct{});

            ts_array_1.swap(ts_array_2);

            REQUIRE_THROWS_AS(
                    ts_array_1[4],
                    gsl::exceptions::out_of_range
            );
            REQUIRE_THROWS_AS(
                    ts_array_2[4],
                    gsl::exceptions::out_of_range
            );

            REQUIRE(
                    ts_array_1.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );

            REQUIRE(
                    ts_array_2.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
        }

        SECTION("pointer") {
            gsl::array<int*,4> pint_array_1;
            REQUIRE(pint_array_1.size()==4);
            int* ptr_1 = new int(4);
            pint_array_1.fill(ptr_1);

            gsl::array<int*,4> pint_array_2;
            REQUIRE(pint_array_2.size()==4);
            int* ptr_2 = new int(6);
            pint_array_2.fill(ptr_2);

            pint_array_1.swap(pint_array_2);

            REQUIRE_THROWS_AS(
                    pint_array_1[4],
                    gsl::exceptions::out_of_range
            );
            REQUIRE_THROWS_AS(
                    pint_array_2[4],
                    gsl::exceptions::out_of_range
            );

            REQUIRE(
                    pint_array_1.to_string() == "[6, 6, 6, 6]"
            );

            REQUIRE(
                    pint_array_2.to_string() == "[4, 4, 4, 4]"
            );
            delete ptr_1;
            delete ptr_2;
        }

        SECTION("custom pointer") {
            gsl::array<test_struct*,4> pint_array_1;
            REQUIRE(pint_array_1.size()==4);
            auto* ptr_1 = new test_struct(test_struct{});
            pint_array_1.fill(ptr_1);

            gsl::array<test_struct*,4> pint_array_2;
            REQUIRE(pint_array_2.size() == 4);
            auto* ptr_2 = new test_struct(test_struct{});
            pint_array_2.fill(ptr_2);

            pint_array_1.swap(pint_array_2);

            REQUIRE_THROWS_AS(
                    pint_array_1[4],
                    gsl::exceptions::out_of_range
            );
            REQUIRE_THROWS_AS(
                    pint_array_2[4],
                    gsl::exceptions::out_of_range
            );

            REQUIRE(
                    pint_array_1.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );

            REQUIRE(
                    pint_array_2.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
            delete ptr_1;
            delete ptr_2;
        }
    }

    SECTION ("At tests") {
        SECTION("integer") {
            gsl::array<int,4> int_array;
            REQUIRE(int_array.size()==4);
            for (int i = 0; i<4; i++)
                int_array[i] = i;
            REQUIRE(int_array.at(2) == 2);
            REQUIRE_THROWS_AS(
                    int_array.at(4),
                    gsl::exceptions::out_of_range
                    );
            REQUIRE(
                    int_array.to_string() == "[0, 1, 2, 3]"
                    );
        }

        SECTION("custom structure") {
            gsl::array<test_struct,4> ts_array;
            REQUIRE(ts_array.size()==4);
            ts_array.fill(test_struct{});
            test_struct ts_at = ts_array.at(2);
            REQUIRE(ts_at.to_string() == "10 1");
            REQUIRE_THROWS_AS(
                    ts_array.at(4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    ts_array.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
        }

        SECTION("pointer") {
            gsl::array<int*,4> pint_array;
            REQUIRE(pint_array.size()==4);
            int* ptr = new int(5);
            pint_array.fill(ptr);
            REQUIRE(pint_array.at(2) == ptr);
            REQUIRE_THROWS_AS(
                    pint_array.at(4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pint_array.to_string() == "[5, 5, 5, 5]"
            );
            delete ptr;
        }

        SECTION("custom structure") {
            gsl::array<test_struct*,4> pts_array;
            REQUIRE(pts_array.size()==4);
            auto* ptr = new test_struct (test_struct{});
            pts_array.fill(ptr);
            REQUIRE(pts_array.at(2) == ptr);
            REQUIRE_THROWS_AS(
                    pts_array.at(4),
                    gsl::exceptions::out_of_range
            );
            REQUIRE(
                    pts_array.to_string() == "[{ value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }, { value: 10 flag: 1 }]"
            );
            delete ptr;
        }
    }


}