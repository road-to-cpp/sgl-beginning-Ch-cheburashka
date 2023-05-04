//
// Created by 79056 on 13.12.2022.
//

#ifndef GSLIB_STRING_UTILS_HPP
#define GSLIB_STRING_UTILS_HPP

#include <vector>
#include <sstream>

namespace gsl::string_utils {
    std::vector<std::string> split(std::string const &str, std::string const &delimiter = " ") {
        std::vector<std::string> strings;
        std::string current;
        for (size_t i = 0; i < str.length(); ++i) {
            if (str.substr(i,delimiter.length()) == delimiter) {
                strings.push_back(current);
                current.clear();
            }
            else
                current += str[i];
        }
        strings.push_back(current);
        return strings;
    }

    template<typename T>
    std::string join(std::string str, std::vector<T> const &container, std::string const &delimiter) {
        std::stringstream res;
        for (size_t i = 0; i < container.size(); ++i) {
            if (i != container.size() - 1)
                res << container[i] << delimiter;
        }
        res << container.back();
        str = res.str();
        return str;
    }

    bool starts_with(std::string const &str, std::string const &prefix) {
        return str.substr(0,prefix.length()) == prefix;
    }

    bool ends_with(std::string const &str, std::string const &prefix) {
        return str.substr(str.length()-prefix.length(),prefix.length()) == prefix;
    }

    void trim(std::string &str) {
        str.erase(0,str.find_first_not_of(' '));
        str.erase(str.find_last_not_of(' ')+1);
    }

    std::string trim(std::string const &str) {
        std::string result = str;
        result.erase(0,result.find_first_not_of(' '));
        result.erase(result.find_last_not_of(' ')+1);
        return result;
    }

    void uppercase(std::string &str) {
        std::string result;
        for (auto& ch : str) {
            if (ch >= 97 && ch <= 123)
                result += ch - 32;
            else
                result += ch;
        }
        str = std::move(result);
    }

    std::string uppercase(std::string const &str) {
        std::string result;
        for (auto& ch : str) {
            if (ch >= 97 && ch <= 123)
                result += ch - 32;
            else
                result += ch;
        }
        return result;
    }

    void lowercase(std::string &str) {
        std::string result;
        for (auto& ch : str) {
            if (ch >= 65 && ch <= 90)
                result += ch + 32;
            else
                result += ch;
        }
        str = std::move(result);
    }

    std::string lowercase(std::string const &str) {
        std::string result;
        for (auto& ch : str) {
            if (ch >= 65 && ch <= 90)
                result += ch + 32;
            else
                result += ch;
        }
        return result;
    }

}

#endif //GSLIB_STRING_UTILS_HPP
