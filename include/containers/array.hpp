//
// Created by MrMam on 31.10.2022.
//

#ifndef GSLIB_ARRAY_HPP
#define GSLIB_ARRAY_HPP

#include <interfaces/i_sequence_container.hpp>

namespace gsl {
    template <typename T>
   class array : public i_sequence_container<T> {

   };

    template <>
    class array<bool> : public i_sequence_container<bool> {

    };
}

#endif //GSLIB_ARRAY_HPP
