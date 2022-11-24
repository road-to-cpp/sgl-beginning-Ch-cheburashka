//
// Created by Никита on 22.11.2022.
//

#ifndef GSLIB_EXCEPTIONS_HPP
#define GSLIB_EXCEPTIONS_HPP

#include <exception>
#include <sstream>

namespace gsl::exceptions {

    class gsl_exception : public std::exception {
    public:

        virtual ~gsl_exception() = default;

        [[nodiscard]] const char *what() const noexcept override {
            return "GSL Exception";
        }
    };

    class out_of_range : public gsl_exception {
    public:
        out_of_range(size_t index, size_t actual_size) {
            std::stringstream ss;
            ss << "GSL::out_of_range requested index: " << std::to_string(index) << " with actual size: "
               << std::to_string(actual_size);
            _message = ss.str();
        }

        ~out_of_range() override = default;

        [[nodiscard]] const char *what() const noexcept override {
            return _message.c_str();
        }

    private:
        std::string _message;
    };
}
#endif //GSLIB_EXCEPTIONS_HPP
