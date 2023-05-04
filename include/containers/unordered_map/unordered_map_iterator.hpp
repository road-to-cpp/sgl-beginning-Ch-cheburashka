//
// Created by 79056 on 28.12.2022.
//

#ifndef GSLIB_UNORDERED_MAP_ITERATOR_HPP
#define GSLIB_UNORDERED_MAP_ITERATOR_HPP

#include <iterator>
#include "containers/unordered_map/unordered_map.hpp"
#include <list>


namespace gsl {

    template<typename Key, typename Value>
    class unordered_map;

    template<typename Key, typename Value>
    class unordered_map_iterator : std::iterator<std::input_iterator_tag, Key> {
        friend class unordered_map<Key, Value>;

        using Bucket = typename unordered_map<Key, Value>::Bucket;
        using outer_iterator = typename std::vector<std::list<Bucket>>::iterator;
        using inner_iterator = typename std::list<Bucket>::iterator;


    protected:
        explicit unordered_map_iterator(outer_iterator outer_it = nullptr, inner_iterator inner_it = nullptr) :
                _outer_iterator(outer_it), _inner_iterator(inner_it) {}

    public:
        unordered_map_iterator &operator++() {
            if (_inner_iterator != _outer_iterator->end()) {
                _inner_iterator++;
            }
            for (; _outer_iterator->empty(); _outer_iterator++) {}
            _inner_iterator = _outer_iterator->begin();
            return *this;
        }

        typename unordered_map<Key, Value>::Bucket &operator*() {
            return *_inner_iterator;
        }

        typename unordered_map<Key, Value>::Bucket &operator*() const {
            return *_inner_iterator;
        }

        bool operator==(const unordered_map_iterator &other) const {
            return _outer_iterator == other._outer_iterator &&
                   _inner_iterator == other._inner_iterator;
        }

        bool operator!=(const unordered_map_iterator &other) const {
            return !(*this == other);
        }


        unordered_map_iterator(unordered_map_iterator<Key, Value> const &other) {
            _outer_iterator = other._outer_iterator;
            _inner_iterator = other._inner_iterator;
        }

    private:
        outer_iterator _outer_iterator;
        inner_iterator _inner_iterator;
    };

}

#endif //GSLIB_UNORDERED_MAP_ITERATOR_HPP
