//
// Created by 79056 on 28.12.2022.
//

#ifndef GSLIB_UNORDERED_MAP_ITERATOR_HPP
#define GSLIB_UNORDERED_MAP_ITERATOR_HPP

#include <iterator>
#include <utils/pair.hpp>
#include <containers/unordered_map.hpp>



namespace gsl {

    template<typename Key, typename Value>
    class unordered_map;

    template<typename Key, typename Value>
    class unordered_map_iterator : std::iterator<std::input_iterator_tag,Key> {
        friend class unordered_map<Key,Value>;

    protected:
        explicit unordered_map_iterator(typename unordered_map<Key,Value>::Bucket* data) : _data(data) {}

    public:

        unordered_map_iterator &operator++() {
            ++_data;
            return *this;
        }

        unordered_map_iterator &operator--() {
            --_data;
            return *this;
        }

        bool operator==(const unordered_map_iterator &other) const {
            return _data == other._data;
        }

        bool operator!=(const unordered_map_iterator &other) const { return _data != other._data; }


        unordered_map_iterator(unordered_map_iterator<Key,Value> const &other) {
            _data = other._data;
        }

    private:
        typename unordered_map<Key,Value>::Bucket* _data;

    public:
        Value& second = _data->value;
        Key& first = _data->key;
    };

}

#endif //GSLIB_UNORDERED_MAP_ITERATOR_HPP
