//
// Created by 79056 on 13.12.2022.
//

#ifndef GSLIB_STRING_UTILS_HPP
#define GSLIB_STRING_UTILS_HPP


#include "containers/vector.hpp"

namespace gsl::string_utils {
    gsl::vector<std::string> split(std::string const &str, std::string const &delimiter = " ");

    template<typename T>
    std::string join(std::string str, gsl::i_container<T> const &container);

    bool starts_with(std::string const &str, std::string const &prefix);

    bool ends_with(std::string const &str, std::string const &prefix);

    void trim(std::string &str);

    std::string trim(std::string const &str);

    void uppercase(std::string &str);

    std::string uppercase(std::string const &str);

    void lowercase(std::string &str);

    std::string lowercase(std::string const &str);
}

#endif //GSLIB_STRING_UTILS_HPP
