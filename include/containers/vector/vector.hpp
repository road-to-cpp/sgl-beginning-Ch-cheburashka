//
// Created by MrMam on 31.10.2022.
//

#ifndef GSLIB_VECTOR_HPP
#define GSLIB_VECTOR_HPP
#include <sstream>
#include "interfaces/i_sequence_container.hpp"
#include "utils/exceptions.hpp"
#include <iostream>
#include "vector_iterator.hpp"
#include "vector_const_iterator.hpp"
#include "vector_reverse_iterator.hpp"
#include <memory>

namespace gsl {
    template<typename T, typename Alloc = std::allocator<T>>
    class vector : public i_sequence_container<T, Alloc> {
    public:
        using AllocTraits = std::allocator_traits<Alloc>;
        using iterator = vector_iterator<T,Alloc>;
        using const_iterator = vector_const_iterator<T,Alloc>;
        using reverse_iterator = vector_reverse_iterator<T,Alloc>;

        explicit vector(size_t size = 0, const T &value = T(), const Alloc& alloc = Alloc()) : _size(size), _capacity(size+1), _data(AllocTraits::allocate(_alloc,_size)), _alloc(alloc) {
            for (size_t i = 0; i < size; i++) {
                AllocTraits::construct(_alloc,_data+i,value);
            }
        }

        vector(const vector& other) : _size(other._size),_capacity(other._capacity) {
            _data = AllocTraits::allocate(_alloc,other._size);
            for (size_t i = 0;i<other._size;i++) {
                  AllocTraits::construct(_alloc,_data+i,other._data[i]);
            }
        }

        [[nodiscard]] size_t size () const override { return _size; }

        T * data () const { return _data; }

        [[nodiscard]] size_t capacity () const { return _capacity; }

        T &front() override { return *_data; }

        const T &front() const override { return *_data; }

        const T &back() const override { return _data[_size-1]; }

        T &back() override { return _data[_size-1]; }

        void reserve (size_t new_cap) {
            T* temp = AllocTraits::allocate(_alloc,new_cap);
            size_t i = 0;
            try {
                for (; i < _size; ++i) {
                    AllocTraits::construct(_alloc,temp+i,_data[i]);
                }
            }
            catch (...) {
                for (size_t j = 0; j < i; ++j) {
                    AllocTraits::destroy(_alloc,temp+j);
                }
                throw;
            }
            for (size_t j = 0; j < _size; ++j) {
                AllocTraits::destroy(_alloc,_data+j);
            }
            AllocTraits::deallocate(_alloc, _data, _capacity);
            _data = temp;
            _capacity = new_cap;
        }

        void resize(size_t new_size) override {
            T* temp = AllocTraits::allocate(_alloc,new_size);
            for (size_t i = 0; i < _size; i++) {
                AllocTraits::construct(_alloc,temp+i,_data[i]);
            }
            for (size_t j = _size; j<new_size;j++){
                AllocTraits::construct(_alloc,temp+j,T());
            }
            for (size_t j = 0; j < _size; ++j) {
                AllocTraits::destroy(_alloc,_data+j);
            }
            AllocTraits::deallocate(_alloc, _data, _capacity);
            _capacity = new_size;
            _data = temp;
        }

        void resize(size_t new_size, const T &value) override {
            T* temp = AllocTraits::allocate(_alloc,new_size);
            for (size_t i = 0; i < _size; i++) {
                AllocTraits::construct(_alloc,temp+i,_data[i]);
            }
            for (size_t j = _size; j<new_size;j++){
                AllocTraits::construct(_alloc,temp+j,value);
            }
            for (size_t j = 0; j < _size; ++j) {
                AllocTraits::destroy(_alloc,_data+j);
            }
            AllocTraits::deallocate(_alloc, _data, _capacity);
            _capacity = new_size;
            _size = new_size;
            _data = temp;
        }

        void push_back(const T &value) override {
            if (_size >= _capacity){
                 reserve(_capacity * 2);
            }
            AllocTraits::construct(_alloc,_data+_size,value);
            ++_size;
        }

        void push_front(const T &value) override {
            insert(value,0);
        }

        void pop_back () override {
            AllocTraits::destroy(_alloc,_data+_size-1);
            --_size;
        }

        void pop_front() override {
            erase(0);
        }

        void clear () override {
            for (size_t i =_size;i>0;i--){
                pop_back();
            }
        }

        void insert(const T &value, size_t index) override {
            if (index >= _size)
                throw gsl::exceptions::out_of_range(index,_size);
            if (_size >= _capacity){
                reserve(_capacity * 2);
            }
            T* temp = AllocTraits::allocate(_alloc,_capacity);
            for (size_t i = 0; i<index;i++){
                AllocTraits::construct(_alloc,temp+i,_data[i]);
            }
            AllocTraits::construct(_alloc,temp+index,value);
            _size++;
            for (size_t i = index+1;i<_size;i++){
                AllocTraits::construct(_alloc,temp+i,_data[i-1]);
            }
            for (size_t j = 0; j < _size; ++j) {
                AllocTraits::destroy(_alloc,_data+j);
            }
            AllocTraits::deallocate(_alloc, _data, _capacity);
            _data = temp;
        }

        void erase(size_t index) override {
            if (index >= _size)
                throw gsl::exceptions::out_of_range(index,_size);
            T* temp = AllocTraits::allocate(_alloc,_capacity);
            _size--;
            for (size_t i =0;i<index;i++){
                AllocTraits::construct(_alloc,temp+i,_data[i]);
            }
            for (size_t i = index;i<_size;i++) {
                AllocTraits::construct(_alloc, temp + i, _data[i+1]);
            }
            for (size_t j = 0; j < _size; ++j) {
                AllocTraits::destroy(_alloc,_data+j);
            }
            AllocTraits::deallocate(_alloc, _data, _capacity);
            _data = temp;
        }

        void erase(size_t first, size_t last) override {
            if (first >= _size)
                throw gsl::exceptions::out_of_range(first,_size);
            if (last >= _size)
                throw gsl::exceptions::out_of_range(last,_size);
            T* temp = AllocTraits::allocate(_alloc,_capacity);
            size_t dif = last - first + 1;
            _size = _size - dif;
            for (size_t i = 0;i<first;i++){
                AllocTraits::construct(_alloc, temp + i, _data[i]);
            }
            for (size_t i = first;i<_size;i++){
                AllocTraits::construct(_alloc, temp + i, _data[i+dif]);
            }
            for (size_t j = 0; j < _size; ++j) {
                AllocTraits::destroy(_alloc,_data+j);
            }
            AllocTraits::deallocate(_alloc, _data, _capacity);
            _data = temp;
        }

        [[nodiscard]] std::string to_string() const override {
            std::stringstream res;
            if (_size == 0)
                res << "[]";
            else {
                res << "[";
                for (size_t i = 0; i < _size; i++) {
                    if (i < _size - 1) {
                        res << _data[i] << ", ";
                    }
                    else {
                        res << _data[i] << "]";
                    }
                }
            }
            return res.str();
        }
        void swap (vector &other) {
            std::swap(_data, other._data);
            std::swap(_size, other._size);
            std::swap(_capacity, other._capacity);
        }

        [[nodiscard]] bool empty () const override {
            return _size == 0;
        }

        T &operator[](size_t i) override {
            if (i >= _size)
                throw gsl::exceptions::out_of_range(i,_size);
            return _data[i];
        }

        const T &operator[](size_t i) const override {
            if (i >= _size)
                throw gsl::exceptions::out_of_range(i,_size);
            return _data[i];
        }

        iterator begin() {
            return iterator(_data);
        }

        iterator end() {
            return iterator(_data + _size);
        }

        const_iterator cbegin () const {
            return const_iterator(_data);
        }

        const_iterator cend() const {
            return const_iterator(_data + _size);
        }

        reverse_iterator rbegin() {
            return reverse_iterator(_data + _size - 1);
        }
        reverse_iterator rend() {
            return reverse_iterator(_data-1);
        }

        ~vector() {
            for (size_t j = 0; j < _size; ++j) {
                AllocTraits::destroy(_alloc,_data+j);
            }
            AllocTraits::deallocate(_alloc, _data, _capacity);
        }
        friend std::ostream &operator<<(std::ostream &os, const vector &vec) {
            os << vec.to_string();
            return os;
        }

    private:
        size_t _size;
        size_t _capacity;
        T* _data;
        Alloc _alloc;
    };

///////////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename T, typename Alloc>
    class vector<T*,Alloc> {
    public:
        using AllocTraits = std::allocator_traits<Alloc>;
        explicit vector(size_t size = 0, T *value = nullptr, Alloc alloc = Alloc()) : _size(size), _capacity(size+1), _data(AllocTraits::allocate(_alloc,_size)), _alloc(alloc) {
            for (size_t i = 0; i < size; i++) {
                AllocTraits::construct(_alloc,_data+i,value);
            }
        }
        [[nodiscard]] size_t size () const { return _size; }

        T ** data () const { return _data; }

        [[nodiscard]] size_t capacity () const { return _capacity; }

        T* front() { return *_data; }

        const T* front() const { return *_data; }

        const T* back() const { return _data[_size-1]; }

        T* back() { return _data[_size-1]; }

        T* operator[](size_t i) {
            if (i >= _size)
                throw gsl::exceptions::out_of_range(i,_size);
            return _data[i];
        }

        T* operator[](size_t i) const {
            if (i >= _size)
                throw gsl::exceptions::out_of_range(i,_size);
            return _data[i];
        }

        void reserve (size_t new_cap) {
            T** temp = AllocTraits::allocate(_alloc,new_cap);
            size_t i = 0;
            try {
                for (; i < _size; ++i) {
                    AllocTraits::construct(_alloc,temp+i,_data[i]);
                }
            }
            catch (...) {
                for (size_t j = 0; j < i; ++j) {
                    AllocTraits::destroy(_alloc,temp+j);
                }
                throw;
            }
            for (size_t j = 0; j < _size; ++j) {
                AllocTraits::destroy(_alloc,_data+j);
            }
            AllocTraits::deallocate(_alloc, _data, _capacity);
            _data = temp;
            _capacity = new_cap;
        }

        void resize(size_t new_size) {
            T** temp = AllocTraits::allocate(_alloc,new_size);
            for (size_t i = 0; i < _size; i++) {
                AllocTraits::construct(_alloc,temp+i,_data[i]);
            }
            for (size_t j = _size; j<new_size;j++){
                AllocTraits::construct(_alloc,temp+j,nullptr);
            }
            for (size_t j = 0; j < _size; ++j) {
                AllocTraits::destroy(_alloc,_data+j);
            }
            AllocTraits::deallocate(_alloc, _data, _capacity);
            _capacity = new_size;
            _data = temp;
        }

        void resize(size_t new_size, T* value)  {
            T** temp = AllocTraits::allocate(_alloc,new_size);
            for (size_t i = 0; i < _size; i++) {
                AllocTraits::construct(_alloc,temp+i,_data[i]);
            }
            for (size_t j = _size; j<new_size;j++){
                AllocTraits::construct(_alloc,temp+j,value);
            }
            for (size_t j = 0; j < _size; ++j) {
                AllocTraits::destroy(_alloc,_data+j);
            }
            AllocTraits::deallocate(_alloc, _data, _capacity);
            _capacity = new_size;
            _size = new_size;
            _data = temp;
        }

        void push_back(T* value) {
            if (_size >= _capacity){
                resize(_capacity * 2);
            }
            AllocTraits::construct(_alloc,_data+_size,value);
            _size++;
        }

        void push_front(T* value) {
            insert(value,0);
        }

        void pop_back () {
            AllocTraits::destroy(_alloc,_data+_size-1);
            --_size;
        }

        void pop_front() {
            erase(0);
        }

        void clear () {
            for (size_t i =_size;i>0;i--){
                pop_back();
            }
        }

        void insert (T* value, size_t index) {
            if (index >= _size)
                throw gsl::exceptions::out_of_range(index,_size);
            if (_size >= _capacity){
                resize(_capacity * 2);
            }
            T** temp = AllocTraits::allocate(_alloc,_capacity);
            for (size_t i = 0; i<index;i++){
                AllocTraits::construct(_alloc,temp+i,_data[i]);
            }
            AllocTraits::construct(_alloc,temp+index,value);
            _size++;
            for (size_t i = index+1;i<_size;i++){
                AllocTraits::construct(_alloc,temp+i,_data[i-1]);
            }
            for (size_t j = 0; j < _size; ++j) {
                AllocTraits::destroy(_alloc,_data+j);
            }
            AllocTraits::deallocate(_alloc, _data, _capacity);
            _data = temp;
        }

        void erase(size_t index) {
            if (index >= _size)
                throw gsl::exceptions::out_of_range(index,_size);
            T** temp = AllocTraits::allocate(_alloc,_capacity);
            _size--;
            for (size_t i =0;i<index;i++){
                AllocTraits::construct(_alloc,temp+i,_data[i]);
            }
            for (size_t i = index;i<_size;i++) {
                AllocTraits::construct(_alloc, temp + i, _data[i+1]);
            }
            for (size_t j = 0; j < _size; ++j) {
                AllocTraits::destroy(_alloc,_data+j);
            }
            AllocTraits::deallocate(_alloc, _data, _capacity);
            _data = temp;
        }

        void erase(size_t first, size_t last) {
            if (first >= _size)
                throw gsl::exceptions::out_of_range(first,_size);
            if (last >= _size)
                throw gsl::exceptions::out_of_range(last,_size);
            T** temp = AllocTraits::allocate(_alloc,_capacity);
            size_t dif = last - first + 1;
            _size = _size - dif;
            for (size_t i = 0;i<first;i++){
                AllocTraits::construct(_alloc, temp + i, _data[i]);
            }
            for (size_t i = first;i<_size;i++){
                AllocTraits::construct(_alloc, temp + i, _data[i+dif]);
            }
            for (size_t j = 0; j < _size; ++j) {
                AllocTraits::destroy(_alloc,_data+j);
            }
            AllocTraits::deallocate(_alloc, _data, _capacity);
            _data = temp;
        }

        [[nodiscard]] std::string to_string() const {
            std::stringstream res;
            if (_size == 0)
                res << "[]";
            else {
                res << "[";
                for (size_t i = 0; i < _size; i++) {
                    if (i < _size - 1) {
                        res << *_data[i];
                        res << ", ";
                    } else
                        res << *_data[i];
                }
                res << "]";
            }
            return res.str();
        }

        void swap (vector &other) {
            std::swap(_data, other._data);
            std::swap(_size, other._size);
            std::swap(_capacity, other._capacity);
        }

        [[nodiscard]] bool empty () const {
            return _size == 0;
        }

        friend std::ostream &operator<<(std::ostream &os, const vector &vec) {
            os << vec.to_string();
            return os;
        }

        ~vector() {
            for (size_t j = 0; j < _size; ++j) {
                AllocTraits::destroy(_alloc,_data+j);
            }
            AllocTraits::deallocate(_alloc, _data, _capacity);
        }
    private:
        size_t _size;
        size_t _capacity;
        T** _data;
        Alloc _alloc;
    };

    template <>
    class vector<bool> : i_sequence_container<bool> {
    };
}

#endif //GSLIB_VECTOR_HPP
