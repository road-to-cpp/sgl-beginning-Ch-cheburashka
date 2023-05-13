//
// Created by 79056 on 19.12.2022.
//

#ifndef GSLIB_VECTOR_ITERATOR_HPP
#define GSLIB_VECTOR_ITERATOR_HPP
#include <iterator>

namespace gsl {
    template<typename T, typename Alloc>
    class vector;

    template<typename T, typename Alloc = std::allocator<T>>
    class vector_iterator : std::iterator<std::input_iterator_tag, T> {
        friend class vector<T, Alloc>;

    protected:
        explicit vector_iterator(T *data) : _data(data) {}

    public:
        virtual ~vector_iterator() = default;

        T &operator*() { return *_data; }

        T *operator->() { return _data; }

        vector_iterator &operator++() {
            ++_data;
            return *this;
        }

        vector_iterator &operator--() {
            --_data;
            return *this;
        }

        bool operator==(const vector_iterator &other) const {
            return _data == other._data;
        }

        bool operator!=(const vector_iterator &other) const { return _data != other._data; }


        vector_iterator(vector_iterator<T> const &other) {
            _data = other._data;
        }

    private:
        T *_data;
    };
}


#endif //GSLIB_VECTOR_ITERATOR_HPP
