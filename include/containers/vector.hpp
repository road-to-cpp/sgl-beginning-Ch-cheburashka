//
// Created by MrMam on 31.10.2022.
//

#ifndef GSLIB_VECTOR_HPP
#define GSLIB_VECTOR_HPP

#include <interfaces/i_sequence_container.hpp>
#include <iostream>
namespace gsl {
    template<typename T>
    class vector : i_sequence_container<T> {
    public:

        explicit vector(size_t size = 0, const T &value = T()) : _size(size), _capacity(size+1), _data(new T[size]) {
            for (int i = 0; i < size; i++) {
                _data[i] = value;
            }
        }

        size_t size () const override {
           return _size;
       }
        T * data () {
            return _data;
        }
        size_t capacity () const {
            return _capacity;
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

        void resize(size_t new_size) override {
            T *temp = new T[new_size];
            for (int i = 0; i < _size; i++) {
                temp[i] = std::move(_data[i]);
            }
            _capacity = new_size;
            delete[] _data;
            _data = temp;
        }

        void resize(size_t new_size, const T &value) override {
            T *temp = new T[new_size];
            for (int i = 0; i < _size; i++) {
                temp[i] = std::move(_data[i]);
            }
            for (int j = 0; j<new_size;j++){
                temp[j+_size] = std::move(value);
            }
            _capacity = new_size;
            _size = new_size;
            delete[] _data;
            _data = temp;
        }

        void push_back(const T &value) override {
            if (_size >= _capacity){
                resize(_capacity * 2);
            }
            _data[_size++] = std::move(value);
        }

        void pop_back () override {
            T *temp = new T[_capacity];
            for (int i = 0; i < _size - 1; ++i)
                temp[i] = std::move(_data[i]);
            delete[] _data;
            _data = temp;
            _size--;
        }

        void clear () override {
            for (int i =_size;i>0;i--){
                pop_back();
            }
        }

        void insert(const T &value, size_t index) override {
            T* temp = new T
        }

        bool empty () const override {
            return _size == 0;
        }

         T &operator[](size_t i) {
            return _data[i];
        }

        T &operator[](size_t i) const {
            return _data[i];
        }
        ~vector() {
            delete [] _data;
        }
        friend std::ostream &operator<<(std::ostream &os, const vector &vec) {
            for (int i = 0; i < vec._size; i++) {
                os << vec._data[i] << " ";
            }
            os << '\n';
            return os;
        }
    private:
        size_t _size;
        size_t _capacity;
        T* _data;
    };

    template <>
    class vector<bool> : i_sequence_container<bool> {
    };
}

#endif //GSLIB_VECTOR_HPP
