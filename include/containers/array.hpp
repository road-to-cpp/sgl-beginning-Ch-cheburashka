//
// Created by MrMam on 31.10.2022.
//

#ifndef GSLIB_ARRAY_HPP
#define GSLIB_ARRAY_HPP

#include <interfaces/i_fixed_sized_container.hpp>
#include <iostream>

namespace gsl {
    template <typename T>
   class array : public i_fixed_sized_container<T> {
   public:
       explicit array(size_t size = 0) : _size(size), _data(new T[size]) {}

       array(const array& other) : _size(other._size), _data(new T[other._size]) {
           for (int i = 0; i < _size; i++){
               _data[i] = other._data[i];
           }
       }

       array & operator=(array const &other) {
           if (this != &other) {
               delete[] _data;
               _size = other._size;
               _data = new T[_size];
               for (int i = 0; i < _size; i++) {
                   _data[i] = std::move(other._data[i]);
               }
           }
           return *this;
       }
       void fill (const T& value) override {
           for (size_t i =0;i<_size;i++) {
               _data[i] = value;
           }
       }
       void swap(array& other) {
           std::swap(_data,other._data);
           std::swap(_size, other._size);
       }
       size_t size() const override {
           return _size;
       }

       T * data () const {
           return _data;
       }

       bool empty() const override {
           return _size == 0;
       }

       std::string to_string() const override {
           std::string res;
           res.append("[");
           for (size_t i = 0;i<_size;i++){
               if(i<_size-1){
                   res.append(std::to_string(_data[i]));
                   res.append(", ");
               }
               else
                   res.append(std::to_string(_data[i]));
           }
           res.append("]");
           return res;
       }

       T &front() override {
           return *_data;
       }
       const T &front() const override {
           return *_data;
       }

       const T &back() const override {
           return _data[_size-1];
       }

       T &back() override {
           return _data[_size-1];
       }

       T &operator[](size_t i) {
           return _data[i];
       }

       T &operator[](size_t i) const {
           return _data[i];
       }
       ~array() {
           delete[] _data;
       }
       friend std::ostream &operator<<(std::ostream &os, const array &vec) {
           for (int i = 0; i < vec._size; i++) {
               os << vec._data[i] << " ";
           }
           os << '\n';
           return os;
       }
   private:
       size_t _size;
       T * _data;
   };
}

#endif //GSLIB_ARRAY_HPP
