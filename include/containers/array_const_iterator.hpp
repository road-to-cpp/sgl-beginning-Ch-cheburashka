//
// Created by 79056 on 20.12.2022.
//

#ifndef GSLIB_ARRAY_CONST_ITERATOR_HPP
#define GSLIB_ARRAY_CONST_ITERATOR_HPP

#include <iterator>

namespace gsl {
    template<typename T, size_t ArrSize>
    class array;

    template<typename T, size_t ArrSize>
    class array_const_iterator : std::iterator<std::input_iterator_tag, T> {
        friend class array<T, ArrSize>;

    protected:
        explicit array_const_iterator(T const * data) : _data(data) {}

    public:
        virtual ~array_const_iterator() = default;

        T const &operator*() const { return *_data; }

        T const *operator->() const { return _data; }

        array_const_iterator &operator++() {
            ++_data;
            return *this;
        }

        array_const_iterator &operator--() {
            --_data;
            return *this;
        }

        bool operator==(const array_const_iterator &other) const {
            return _data == other._data;
        }

        bool operator!=(const array_const_iterator &other) const { return _data != other._data; }


        array_const_iterator(array_const_iterator<T, ArrSize> const &other) {
            _data = other._data;
        }

    private:
        T const * _data;
    };
}

#endif //GSLIB_ARRAY_CONST_ITERATOR_HPP
