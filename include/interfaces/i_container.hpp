//
// Created by MrMam on 31.10.2022.
//

#ifndef GSLIB_I_CONTAINTER_HPP
#define GSLIB_I_CONTAINTER_HPP

#include <cstdint>
#include <string>
//#include <vector>
#include "i_iterator.hpp"

namespace gsl {
    template<typename T>
    class i_container {
    public:
        using iterator = i_iterator<T>;
//
        virtual ~i_container() =default;
//
        virtual size_t size() const = 0;
//
        virtual bool empty() const = 0;
//
//        virtual std::string to_string() const = 0;
//
//        virtual iterator begin() = 0;
//
//        virtual iterator end() = 0;
//
//        virtual iterator rbegin() = 0;
//
//        virtual iterator rend() = 0;
//
        virtual void clear() = 0;
    };
}
#endif //GSLIB_I_CONTAINTER_HPP
