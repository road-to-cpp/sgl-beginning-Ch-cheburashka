//
// Created by 79056 on 19.12.2022.
//

#ifndef GSLIB_LINKED_LIST_ITERATOR_HPP
#define GSLIB_LINKED_LIST_ITERATOR_HPP
#include <iterator>
#include <containers/linked_list.hpp>
namespace gsl {

    template<typename T>
    class linked_list;
    template<typename T>
    class Node;

    template<typename T>
    class linked_list_iterator : std::iterator<std::input_iterator_tag, T> {
        friend class linked_list<T>;
        friend class Node<T>;

    protected:
        explicit linked_list_iterator(Node<T> *data) : _data(data) {}

    public:
        virtual ~linked_list_iterator() = default;

        T &operator*() { return _data->_data; }

        T *operator->() { return &_data->_data; }

        linked_list_iterator &operator++() {
            _data = _data->_pNext;
            return *this;
        }

        linked_list_iterator &operator--() {
            auto* prev = new Node<T>;
            prev->_pNext = _data;
            _data = prev;
            return *this;
        }

        bool operator==(const linked_list_iterator &other) const {
            return _data == other._data;
        }

        bool operator!=(const linked_list_iterator &other) const { return _data != other._data; }


        linked_list_iterator(linked_list_iterator<T> const &other) {
            _data = other._data;
        }

    private:
        Node<T>* _data;
    };

}


#endif //GSLIB_LINKED_LIST_ITERATOR_HPP
