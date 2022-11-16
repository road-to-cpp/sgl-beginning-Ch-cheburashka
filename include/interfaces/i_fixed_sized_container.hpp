//
// Created by 79056 on 14.11.2022.
//

#ifndef GSLIB_I_FIXED_SIZED_CONTAINER_HPP
#define GSLIB_I_FIXED_SIZED_CONTAINER_HPP

#include "i_referenceable.hpp"

namespace gsl {
    template <typename T>
    class i_fixed_sized_container : public i_referenceable<T> {
    public:
        virtual ~i_fixed_sized_container() = default;

        virtual T& at(size_t i) const = 0;

        virtual void fill (const T& value) = 0;
    };

}

#endif //GSLIB_I_FIXED_SIZED_CONTAINER_HPP
