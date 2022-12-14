//
// Created by 79056 on 13.12.2022.
//

#ifndef GSLIB_ARRAY_ITERATOR_HPP
#define GSLIB_ARRAY_ITERATOR_HPP

#include <cstdlib>
#include <interfaces/i_iterator.hpp>

namespace gsl {

    template<typename T, size_t ArrSize>
    class array;

    template<typename T, size_t ArrSize>
    class array_iterator : i_iterator<T> {
        friend class array<T, ArrSize>;

    protected:
        explicit array_iterator(array<T, ArrSize> *data, size_t offset = 0)
                : _data(data), _current_offset(offset) {}

    public:
        virtual ~array_iterator() = default;

        T& operator*() noexcept override { return _data[_current_offset]; }

        T *operator->() noexcept override { return _data + _current_offset; }

        array_iterator& operator++() noexcept override {
            ++_current_offset;
            return *this;
        }

        array_iterator& operator--() noexcept override {
            --_current_offset;
            return *this;
        }

        bool operator==(const array_iterator &other) const noexcept override { return _data == other._data; }

        bool operator!=(const array_iterator &other) const noexcept override { return _data != other._data; }


        array_iterator(array_iterator<T, ArrSize> const &iterator) {
            _data = iterator._data;
            _current_offset = iterator._current_offset;
        }

    private:
        array<T, ArrSize> *_data;
        size_t _current_offset;
    };
}

#endif //GSLIB_ARRAY_ITERATOR_HPP