//
// Created by 79056 on 16.11.2022.
//

#ifndef GSLIB_I_REFERENCEABLE_HPP
#define GSLIB_I_REFERENCEABLE_HPP

#include "i_container.hpp"

namespace gsl {
    template<typename T>
    class i_referenceable : public i_container<T> {
    public:
        virtual T &back() = 0;

        virtual const T &back() const = 0;

        virtual T &front() = 0;

        virtual const T &front() const = 0;

        virtual T &operator[](size_t i) = 0;

        virtual const T &operator[](size_t i) const = 0;
    };
}

#endif //GSLIB_I_REFERENCEABLE_HPP
