//
// Created by MrMam on 31.10.2022.
//

#ifndef GSLIB_I_ITERATOR_HPP
#define GSLIB_I_ITERATOR_HPP

namespace gsl {
    template<typename T>
    class i_iterator {
    public:
        virtual ~i_iterator() = default;

        virtual T &operator*() = 0;

        virtual T &operator->() = 0;

        virtual i_iterator &operator++() = 0;

        virtual i_iterator &operator--() = 0;

        virtual bool operator==(const i_iterator &other) const = 0;

        virtual bool operator!=(const i_iterator &other) const = 0;
    };
}
#endif //GSLIB_I_ITERATOR_HPP
