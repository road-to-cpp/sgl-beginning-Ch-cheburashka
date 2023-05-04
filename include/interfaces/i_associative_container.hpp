//
// Created by MrMam on 01.11.2022.
//

#ifndef GSLIB_I_ASSOCIATIVE_CONTAINER_HPP
#define GSLIB_I_ASSOCIATIVE_CONTAINER_HPP

#include "i_container.hpp"
#include "containers/unordered_map/unordered_map_iterator.hpp"

template<typename Key, typename Value>
struct Bucket {
    Key key;
    Value value;
};

namespace gsl {
    template <typename Key, typename Value>
    class i_associative_container : public i_container<Bucket<Key, Value>> {
    public:

        virtual ~i_associative_container() = default;

        virtual void insert(const Key &key, const Value &value) = 0;

        virtual void emplace(const Key &key, const Value &value) = 0;

        virtual bool contains (const Key &key) const = 0;

        virtual Value &operator[](const Key &key) = 0;

        virtual const Value &operator[](const Key &key) const = 0;

        virtual Value &at(const Key &key) = 0;

        virtual const Value &at(const Key &key) const = 0;

    };
}
#endif //GSLIB_I_ASSOCIATIVE_CONTAINER_HPP
