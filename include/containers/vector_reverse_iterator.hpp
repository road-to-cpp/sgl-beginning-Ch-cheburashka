//
// Created by 79056 on 20.12.2022.
//

#ifndef GSLIB_VECTOR_REVERSE_ITERATOR_HPP
#define GSLIB_VECTOR_REVERSE_ITERATOR_HPP

#include <iterator>

namespace gsl {
    template<typename T>
    class vector;

    template<typename T>
    class vector_reverse_iterator : std::iterator<std::input_iterator_tag, T> {
        friend class vector<T>;

    protected:
        explicit vector_reverse_iterator(T const * data) : _data(data) {}

    public:
        virtual ~vector_reverse_iterator() = default;

        T const &operator*() const { return *_data; }

        T const *operator->() const { return _data; }

        vector_reverse_iterator &operator++() {
            --_data;
            return *this;
        }

        vector_reverse_iterator &operator--() {
            ++_data;
            return *this;
        }

        bool operator==(const vector_reverse_iterator &other) const {
            return _data == other._data;
        }

        bool operator!=(const vector_reverse_iterator &other) const { return _data != other._data; }


        vector_reverse_iterator(vector_reverse_iterator<T> const &other) {
            _data = other._data;
        }

    private:
        T const * _data;
    };
}


#endif //GSLIB_VECTOR_REVERSE_ITERATOR_HPP
