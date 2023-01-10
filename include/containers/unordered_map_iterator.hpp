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
    class unordered_map_iterator : std::iterator<std::input_iterator_tag, Key> {
        friend class unordered_map<Key, Value>;

    protected:

        unordered_map_iterator(std::vector<std::vector<unordered_map<Key, Value>::Bucket>> &data,
                               size_t current_index = 0, size_t inner_index = 0) : _data(data), _current_index(current_index), _current_inner_index(inner_index) {}

    public:

        unordered_map_iterator &operator++() {
            if (_data.size() <= _current_index) {
                return *this;
            }
            if (_data[_current_index].size() <= _current_inner_index) {
                _current_index++;
                _current_inner_index = 0;
            }
            _current_inner_index++;
            return *this;
        }

        typename unordered_map<Key, Value>::Bucket &operator*() {
            return _data[_current_index][_current_inner_index];
        }

        typename unordered_map<Key, Value>::Bucket &operator->() {
            return _data[_current_index][_current_inner_index];
        }

        bool operator==(const unordered_map_iterator &other) const {
            return _data == other._data;
        }

        bool operator!=(const unordered_map_iterator &other) const { return _data != other._data; }


        unordered_map_iterator(unordered_map_iterator<Key, Value> const &other) {
            _data = other._data;
        }

    private:
        std::vector <std::vector<unordered_map<Key, Value>::Bucket>> &_data;
        size_t _current_index;
        size_t _current_inner_index;

    public:
        Value &second = _data->value;
        Key &first = _data->key;
    };

}

#endif //GSLIB_UNORDERED_MAP_ITERATOR_HPP
