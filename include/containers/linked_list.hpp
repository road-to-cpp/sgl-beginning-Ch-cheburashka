//
// Created by MrMam on 01.11.2022.
//

#ifndef GSLIB_LINKED_LIST_HPP
#define GSLIB_LINKED_LIST_HPP

#include <interfaces/i_sequence_container.hpp>

namespace gsl {
    template<typename T>
    class linked_list : public i_sequence_container<T> {

    };
}
#endif //GSLIB_LINKED_LIST_HPP
