//
// Created by MrMam on 31.10.2022.
//

#ifndef GSLIB_VECTOR_HPP
#define GSLIB_VECTOR_HPP

#include <interfaces/i_sequence_container.hpp>

namespace gsl {
    template<typename T>
    class vector : i_sequence_container<T> {
    };

    template <>
    class vector<bool> : i_sequence_container<bool> {
    };
}
#endif //GSLIB_VECTOR_HPP
