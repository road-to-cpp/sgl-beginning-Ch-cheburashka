//
// Created by 79056 on 20.12.2022.
//

#ifndef GSLIB_VECTOR_CONST_ITERATOR_HPP
#define GSLIB_VECTOR_CONST_ITERATOR_HPP

#include <iterator>

namespace gsl {
    template<typename T, typename Alloc>
    class vector;

    template<typename T, typename Alloc>
    class vector_const_iterator : std::iterator<std::input_iterator_tag, T> {
        friend class vector<T,Alloc>;

    protected:
        explicit vector_const_iterator(T const * data) : _data(data) {}

    public:
        virtual ~vector_const_iterator() = default;

        T const &operator*() const { return *_data; }

        T const *operator->() const { return _data; }

        vector_const_iterator &operator++() {
            ++_data;
            return *this;
        }

        vector_const_iterator &operator--() {
            --_data;
            return *this;
        }

        bool operator==(const vector_const_iterator &other) const {
            return _data == other._data;
        }

        bool operator!=(const vector_const_iterator &other) const { return _data != other._data; }


        vector_const_iterator(vector_const_iterator<T,Alloc> const &other) {
            _data = other._data;
        }

    private:
        T const * _data;
    };
}

#endif //GSLIB_VECTOR_CONST_ITERATOR_HPP
