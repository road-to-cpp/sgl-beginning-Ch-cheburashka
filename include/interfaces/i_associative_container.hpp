//
// Created by MrMam on 01.11.2022.
//

#ifndef GSLIB_I_ASSOCIATIVE_CONTAINER_HPP
#define GSLIB_I_ASSOCIATIVE_CONTAINER_HPP

#include "i_container.hpp"
#include "utils/pair.hpp"
#include <containers/map_iterator.hpp>

namespace gsl {
    template<typename K, typename V>
    class i_associative_container : public i_container<pair<K, V>> {
    public:
        using value_type = pair<K, V>;
        using iterator = map_iterator<K, V>;

        virtual ~i_associative_container() = default;

        virtual void insert(const value_type &value) = 0;
//
//        virtual void emplace(const K &key, const V &value) = 0;
//
//        virtual void erase(const iterator  &value) = 0;
//
//        virtual void erase(const iterator &first, const iterator &last) = 0;
//
//        virtual void swap(i_associative_container &other) = 0;
//
//        virtual bool contains (const K &key) const = 0;
//
//        virtual V &operator[](const K &key) = 0;
//
//        virtual const V &operator[](const K &key) const = 0;
//
//        virtual V &at(const K &key) = 0;
//
//        virtual const V &at(const K &key) const = 0;
//
//        virtual iterator find(const K &key) = 0;
    };
}
#endif //GSLIB_I_ASSOCIATIVE_CONTAINER_HPP
