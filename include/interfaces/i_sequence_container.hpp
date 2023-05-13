//
// Created by MrMam on 31.10.2022.
//

#ifndef GSLIB_I_SEQUENCE_CONTAINER_HPP
#define GSLIB_I_SEQUENCE_CONTAINER_HPP

#include "i_referenceable.hpp"

namespace gsl {
    template<typename T, typename Alloc = std::allocator<T>>
    class i_sequence_container : public i_referenceable<T, Alloc> {
    public:
        virtual ~i_sequence_container() = default;

        virtual void push_back(const T &value) = 0;

        virtual void push_front(const T &value) = 0;

        virtual void pop_back() = 0;

        virtual void pop_front() = 0;

        virtual void insert(const T &value, size_t index) = 0;

        virtual void erase(size_t index) = 0;

        virtual void erase(size_t first, size_t last) = 0;

        virtual void resize(size_t new_size) = 0;

        virtual void resize(size_t new_size, const T &value) = 0;

        virtual void clear () = 0;
    };
}
#endif //GSLIB_I_SEQUENCE_CONTAINER_HPP
