//
// Created by 79056 on 24.12.2022.
//

#ifndef GSLIB_MAP_ITERATOR_HPP
#define GSLIB_MAP_ITERATOR_HPP

#include <iterator>
#include <utils/pair.hpp>
#include <containers/map.hpp>

namespace gsl {
    template<typename Key, typename Value>
    class map;
    template<typename Key, typename Value>
    class Node;

    template<typename Key, typename Value>
    class map_iterator : std::iterator<std::input_iterator_tag,Key> {
        friend class map<Key,Value>;
        friend class Node<Key, Value>;

    protected:
        explicit map_iterator(Node<Key,Value>* data) : _data(data){}

    public:

        virtual ~map_iterator() = default;

    private:
        Node<Key,Value>* _data;
    };

}



#endif //GSLIB_MAP_ITERATOR_HPP
