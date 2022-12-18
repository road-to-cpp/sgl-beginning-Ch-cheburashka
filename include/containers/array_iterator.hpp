//
// Created by 79056 on 13.12.2022.
//

#ifndef GSLIB_ARRAY_ITERATOR_HPP
#define GSLIB_ARRAY_ITERATOR_HPP

#include <cstdlib>
#include <iterator>

namespace gsl {
    template<typename T, size_t ArrSize>
    class array;

    template<typename T, size_t ArrSize>
    class array_iterator : std::iterator<std::input_iterator_tag, T> {
        friend class array<T, ArrSize>;

    protected:
        explicit array_iterator(T *data)
                : _data(data) {}

    public:
        virtual ~array_iterator() = default;

        T &operator*() { return *_data; }

        T *operator->() { return _data; }

        array_iterator &operator++() {
            ++_data;
            return *this;
        }

        array_iterator &operator--() {
            --_data;
            return *this;
        }

        bool operator==(const array_iterator &other) const {
            return _data == other._data;
        }

        bool operator!=(const array_iterator &other) const { return _data != other._data; }


        array_iterator(array_iterator<T, ArrSize> const &iterator) {
            _data = iterator._data;
        }

    private:
        T *_data;
    };


    template<typename T, size_t ArrSize>
    class array<T*,ArrSize>;

    template<typename T, size_t ArrSize>
    class array_iterator <T*,ArrSize> : std::iterator<std::input_iterator_tag, T> {
        friend class array<T*, ArrSize>;

    protected:
        explicit array_iterator(T **data)
                : _data(data) {}

    public:
        virtual ~array_iterator() = default;

        T *operator*() { return *_data; }

        T *operator->() { return _data; }

        array_iterator &operator++() {
            ++_data;
            return *this;
        }

        array_iterator &operator--() {
            --_data;
            return *this;
        }

        bool operator==(const array_iterator &other) const {
            return _data == other._data;
        }

        bool operator!=(const array_iterator &other) const { return _data != other._data; }


        array_iterator(array_iterator<T, ArrSize> const &iterator) {
            _data = iterator._data;
        }

    private:
        T **_data;
    };

}


#endif //GSLIB_ARRAY_ITERATOR_HPP