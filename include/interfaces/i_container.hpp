//
// Created by MrMam on 31.10.2022.
//

#ifndef GSLIB_I_CONTAINTER_HPP
#define GSLIB_I_CONTAINTER_HPP

#include <cstdint>
#include <string>
#include <vector>
#include "i_iterator.hpp"

namespace gsl {
    template<typename T>
    class i_container {
    public:
        using iterator = i_iterator<T>;

        virtual ~i_container() =default;

        [[nodiscard]] virtual size_t size() const = 0;

        [[nodiscard]] virtual bool empty() const = 0;

        [[nodiscard]] virtual std::string to_string() const = 0;

//        virtual iterator end() = 0;
//
//        virtual iterator rbegin() = 0;
//
//        virtual iterator rend() = 0;
    };
}
#endif //GSLIB_I_CONTAINTER_HPP
