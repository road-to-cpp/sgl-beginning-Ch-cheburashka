//
// Created by 79056 on 24.12.2022.
//

#ifndef GSLIB_MAP_HPP
#define GSLIB_MAP_HPP

#include <interfaces/i_associative_container.hpp>
#include <containers/map_iterator.hpp>
#include <iostream>

namespace gsl {

    template <typename Key, typename Value>
    class Node {
    public:
        using value_type = pair<Key, Value>;
        value_type _data;
        Node* _parent;
        Node* _left;
        Node* _right;
        explicit Node(value_type data) : _data(data) {}
    };


    template <typename Key, typename Value>
    class map : i_associative_container<Key, Value> {
        using value_type = pair<Key, Value>;
        using iterator = map_iterator<Key, Value>;

    public:
        explicit map () : _size(0), _node(nullptr) {}

        void insert(const value_type &value) override {
            if (_node == nullptr) {
                _node = new Node<Key,Value>(value);
                _size++;
            }
        }

        size_t size() const override {
            return _size;
        }

        bool empty() const override {
            return _size == 0;
        }


        ~map(){}

    private:
        size_t _size;
        Node<Key,Value>* _node;
    };

}


#endif //GSLIB_MAP_HPP
