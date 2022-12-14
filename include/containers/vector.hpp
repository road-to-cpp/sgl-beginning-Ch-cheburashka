//
// Created by MrMam on 31.10.2022.
//

#ifndef GSLIB_VECTOR_HPP
#define GSLIB_VECTOR_HPP
#include <sstream>
#include <interfaces/i_sequence_container.hpp>
#include <interfaces/i_iterator.hpp>
#include <utils/exceptions.hpp>
#include <iostream>
namespace gsl {
    template<typename T>
    class vector : public i_sequence_container<T> {
    public:
        class iterator : public i_iterator<T>{
        public:
            explicit iterator(T* ptr = nullptr): _ptr(ptr){}

            T &operator*() override {
                return *_ptr;
            }
            bool operator==(const iterator &other) const override {
                return this->ptr == other.ptr;
            }
            bool operator!=(const iterator &other) const override {
                return this->ptr != other.ptr;
            }
            iterator &operator++() override {
                _ptr++;
                return *this;
            }
            ~iterator(){
                delete _ptr;
            }
        private:
            T * _ptr;
        };

        explicit vector(size_t size = 0, const T &value = T()) : _size(size), _capacity(size+1), _data(new T[size]) {
            for (size_t i = 0; i < size; i++) {
                _data[i] = value;
            }
        }
        [[nodiscard]] size_t size () const override {
            return _size;
        }
        T * data () const {
            return _data;
        }
        [[nodiscard]] size_t capacity () const {
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
            for (size_t i = 0; i < _size; i++) {
                temp[i] = std::move(_data[i]);
            }
            _capacity = new_size;
            delete[] _data;
            _data = temp;
        }

        void resize(size_t new_size, const T &value) override {
            T *temp = new T[new_size];
            for (size_t i = 0; i < _size; i++) {
                temp[i] = std::move(_data[i]);
            }
            for (size_t j = _size; j<new_size;j++){
                temp[j] = std::move(value);
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

        void push_front(const T &value) override {
            if (_size >= _capacity){
                resize(_capacity * 2);
            }
            T* temp = new T[_capacity];
            temp[0] = value;
            for (size_t i = 0; i<_size; i++){
                temp[i+1] = _data[i];
            }
            delete [] _data;
            _data = temp;
            _size++;
        }

        void pop_back () override {
            T *temp = new T[_capacity];
            for (size_t i = 0; i < _size - 1; ++i)
                temp[i] = std::move(_data[i]);
            delete[] _data;
            _data = temp;
            _size--;
        }

        void pop_front() override {
            T *temp = new T[_capacity];
            for (size_t i =1; i<_size;i++){
                temp[i-1] = _data[i];
            }
            delete [] _data;
            _data = temp;
            _size--;
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
                resize(_capacity * 2);
            }
            T* temp = new T [_capacity];
            for (size_t i = 0; i<index;i++){
                temp [i] = std::move(_data[i]);
            }
            temp[index] = std::move(value);
            _size++;
            for (size_t i = index+1;i<_size;i++){
                temp[i] = std::move(_data[i-1]);
            }
            delete [] _data;
            _data = temp;
        }

        void erase(size_t index) override {
            if (index >= _size)
                throw gsl::exceptions::out_of_range(index,_size);
            T* temp = new T [_capacity];
            _size--;
            for (size_t i =0;i<index;i++){
                temp[i] = std::move(_data[i]);
            }
            for (size_t i = index;i<_size;i++){
                temp[i] = std::move(_data[i+1]);
            }
            delete [] _data;
            _data = temp;
        }

        void erase(size_t first, size_t last) override {
            if (first >= _size)
                throw gsl::exceptions::out_of_range(first,_size);
            if (last >= _size)
                throw gsl::exceptions::out_of_range(last,_size);
            T* temp = new T [_capacity];
            size_t dif = last - first + 1;
            _size = _size - dif;
            for (size_t i = 0;i<first;i++){
                temp[i] = std::move(_data[i]);
            }
            for (size_t i = first;i<_size;i++){
                temp[i] = std::move(_data[i+dif]);
            }
            delete [] _data;
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
        void swap (vector &other, bool optimised = true) {

            if (optimised){
                std::swap(_data, other._data);
                std::swap(_size, other._size);
                std::swap(_capacity, other._capacity);
            }
            else {
                T *temp_1 = new T[other._capacity];
                T *temp_2 = new T[_capacity];
                for (size_t i = 0; i < other._capacity; i++) {
                    temp_1[i] = std::move(other._data[i]);
                }
                for (size_t i = 0; i < _capacity; i++) {
                    temp_2[i] = std::move(_data[i]);
                }

                delete[] _data;
                delete[] other._data;

                _data = temp_1;
                other._data = temp_2;

                size_t tmp_size = _size;
                _size = other._size;
                other._size = tmp_size;

                size_t tmp_capacity = _capacity;
                _capacity = other._capacity;
                other._capacity = tmp_capacity;
            }

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


        ~vector() {
            delete [] _data;
        }
        friend std::ostream &operator<<(std::ostream &os, const vector &vec) {
            os << vec.to_string();
            return os;
        }

    private:
        size_t _size;
        size_t _capacity;
        T* _data;
    };

///////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    class vector<T*> {
    public:
        explicit vector(size_t size = 0, T *value = nullptr) : _size(size), _capacity(size+1), _data(new T*[size]) {
            for (size_t i = 0; i < size; i++) {
                _data[i] = value;
            }
        }
        [[nodiscard]] size_t size () const {
            return _size;
        }
        T ** data () const {
            return _data;
        }
        [[nodiscard]] size_t capacity () const {
            return _capacity;
        }

        T* front() {
            return *_data;
        }
        const T* front() const {
            return *_data;
        }

        const T* back() const {
            return _data[_size-1];
        }

        T* back() {
            return _data[_size-1];
        }

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

        void resize(size_t new_size) {
            T** temp = new T*[new_size];
            for (size_t i = 0; i < _size; i++) {
                temp[i] = std::move(_data[i]);
            }
            _capacity = new_size;
            delete[] _data;
            _data = temp;
        }

        void resize(size_t new_size, T* value)  {
            T** temp = new T*[new_size];
            for (size_t i = 0; i < _size; i++) {
                temp[i] = std::move(_data[i]);
            }
            for (size_t j = _size; j<new_size;j++){
                temp[j] = std::move(value);
            }
            _capacity = new_size;
            _size = new_size;
            delete[] _data;
            _data = temp;
        }

        void push_back(T* value) {
            if (_size >= _capacity){
                resize(_capacity * 2);
            }
            _data[_size++] = std::move(value);
        }

        void push_front(T* value) {
            if (_size >= _capacity){
                resize(_capacity * 2);
            }
            T** temp = new T*[_capacity];
            temp[0] = value;
            for (size_t i = 0; i<_size; i++){
                temp[i+1] = _data[i];
            }
            delete [] _data;
            _data = temp;
            _size++;
        }

        void pop_back () {
            T** temp = new T*[_capacity];
            for (size_t i = 0; i < _size - 1; ++i)
                temp[i] = std::move(_data[i]);
            delete[] _data;
            _data = temp;
            _size--;
        }

        void pop_front() {
            T** temp = new T*[_capacity];
            for (size_t i =1; i<_size;i++){
                temp[i-1] = _data[i];
            }
            delete [] _data;
            _data = temp;
            _size--;
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
            T** temp = new T* [_capacity];
            for (size_t i = 0; i<index;i++){
                temp [i] = std::move(_data[i]);
            }
            temp[index] = std::move(value);
            _size++;
            for (size_t i = index+1;i<_size;i++){
                temp[i] = std::move(_data[i-1]);
            }
            delete [] _data;
            _data = temp;
        }

        void erase(size_t index) {
            if (index >= _size)
                throw gsl::exceptions::out_of_range(index,_size);
            T** temp = new T* [_capacity];
            _size--;
            for (size_t i =0;i<index;i++){
                temp[i] = std::move(_data[i]);
            }
            for (size_t i = index;i<_size;i++){
                temp[i] = std::move(_data[i+1]);
            }
            delete [] _data;
            _data = temp;
        }

        void erase(size_t first, size_t last) {
            if (first >= _size)
                throw gsl::exceptions::out_of_range(first,_size);
            if (last >= _size)
                throw gsl::exceptions::out_of_range(last,_size);
            T** temp = new T* [_capacity];
            size_t dif = last - first + 1;
            _size = _size - dif;
            for (size_t i = 0;i<first;i++){
                temp[i] = std::move(_data[i]);
            }
            for (size_t i = first;i<_size;i++){
                temp[i] = std::move(_data[i+dif]);
            }
            delete [] _data;
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
            delete [] _data;
        }
    private:
        size_t _size;
        size_t _capacity;
        T** _data;
    };

    template <>
    class vector<bool> : i_sequence_container<bool> {
    };
}

#endif //GSLIB_VECTOR_HPP
