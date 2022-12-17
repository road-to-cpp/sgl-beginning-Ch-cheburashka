//
// Created by MrMam on 31.10.2022.
//

#ifndef GSLIB_ARRAY_HPP
#define GSLIB_ARRAY_HPP

#include <interfaces/i_fixed_sized_container.hpp>
#include <iostream>
#include <sstream>
#include <containers/array_iterator.hpp>
#include <utils/exceptions.hpp>

namespace gsl {
    template <typename T, size_t Size>
   class array : public i_fixed_sized_container<T> {
   public:
       using iterator = array_iterator<T,Size>;

       void fill (const T& value) override {
           for (size_t i =0;i<Size;i++) {
               _data[i] = value;
           }
       }
       void swap(array& other) {
           std::swap(_data,other._data);
       }
       [[nodiscard]] size_t size() const override {
           return Size;
       }

       T * data () const {
           return _data;
       }

       [[nodiscard]] bool empty() const override {
           return Size == 0;
       }

       [[nodiscard]] std::string to_string() const override {
           std::stringstream res;
           res << "[";
           for (size_t i = 0;i<Size;i++){
               if(i<Size-1){
                   res << _data[i];
                   res << ", ";
               }
               else
                   res << _data[i];
           }
           res << "]";
           return res.str();
       }

       T &front() override {
           return *_data;
       }
       const T &front() const override {
           return *_data;
       }

       const T &back() const override {
           return _data[Size-1];
       }

       T &back() override {
           return _data[Size-1];
       }

       T &operator[](size_t i) override {
           if (i >= Size)
               throw gsl::exceptions::out_of_range(i,Size);
           return _data[i];
       }

       const T & operator[] (size_t i) const override {
           if (i >= Size)
               throw gsl::exceptions::out_of_range(i,Size);
           return _data[i];
       }

       T& at(size_t i) override {
           if (i >= Size)
               throw gsl::exceptions::out_of_range(i,Size);
           return _data[i];
       }

       const T &at(size_t i) const override {
           if (i >= Size)
               throw gsl::exceptions::out_of_range(i,Size);
           return _data[i];
       }

       friend std::ostream &operator<<(std::ostream &os, const array &arr) {
           os << arr.to_string();
           return os;
       }

       iterator begin () {
           return iterator(_data);
       }

       iterator end() {
           return iterator(_data + Size);
       }

   private:
       T _data[Size];
   };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    template <typename T, size_t Size>
    class array <T*,Size> {
    public:
        using iterator = array_iterator<T,Size>;

        array(){}

        void fill (T* value) {
            for (size_t i =0;i<Size;i++) {
                _data[i] = value;
            }
        }
        void swap(array& other) {
            std::swap(_data,other._data);
        }

        [[nodiscard]] size_t size() const  {
            return Size;
        }

        T ** data () const {
            return _data;
        }

        [[nodiscard]] bool empty() const  {
            return Size == 0;
        }

        [[nodiscard]] std::string to_string() const  {
            std::stringstream res;
            res << "[";
            for (size_t i = 0;i<Size;i++){
                if(i<Size-1){
                    res << *_data[i];
                    res << ", ";
                }
                else
                    res << *_data[i];
            }
            res << "]";
            return res.str();
        }

        T *front()  {
            return *_data;
        }
        const T *front() const  {
            return *_data;
        }

        const T *back() const  {
            return _data[Size-1];
        }

        T *back()  {
            return _data[Size-1];
        }

        T *operator[](size_t i)  {
            if (i >= Size)
                throw gsl::exceptions::out_of_range(i,Size);
            return _data[i];
        }

        const T *operator[] (size_t i) const  {
            if (i >= Size)
                throw gsl::exceptions::out_of_range(i,Size);
            return _data[i];
        }

        T* at(size_t i) {
            if (i >= Size)
                throw gsl::exceptions::out_of_range(i,Size);
            return _data[i];
        }

        const T *at(size_t i) const  {
            return _data[i];
        }

        friend std::ostream &operator<<(std::ostream &os, const array &arr) {
            os << arr.to_string();
            return os;
        }
    private:
        T* _data[Size];
    };
}

#endif //GSLIB_ARRAY_HPP
