//
// Created by MrMam on 01.11.2022.
//

#ifndef GSLIB_PAIR_HPP
#define GSLIB_PAIR_HPP

#include <utility>

namespace gsl {
    template<typename First, typename Second>
    struct pair {
        First first;
        Second second;

    public:
        pair(First f, Second s) {
            first = f;
            second = s;
        }

        void swap(pair &other) {
            std::swap(first, other.first);
            std::swap(second, other.second);
        }

        bool operator==(const pair &other) const {
            return first == other.first && second == other.second;
        }

        bool operator!=(const pair &other) const {
            return !(*this == other);
        }

        bool operator<(const pair &other) const {
            return first < other.first || (first == other.first && second < other.second);
        }

        bool operator>(const pair &other) const {
            return other < *this;
        }

        bool operator<=(const pair &other) const {
            return !(other < *this);
        }

        bool operator>=(const pair &other) const {
            return !(*this < other);
        }

        pair &operator=(const pair &other) {
            first = other.first;
            second = other.second;
            return *this;
        }

        pair &operator=(pair &&other) noexcept {
            first = std::move(other.first);
            second = std::move(other.second);
            return *this;
        }

        pair(const pair &other) {
            first = other.first;
            second = other.second;
        }

        pair(pair &&other) noexcept {
            first = std::move(other.first);
            second = std::move(other.second);
        }

        pair() = default;

        ~pair() = default;
    };
}

#endif //GSLIB_PAIR_HPP
