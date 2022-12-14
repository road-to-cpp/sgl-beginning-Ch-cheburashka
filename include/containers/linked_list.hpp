//
// Created by MrMam on 01.11.2022.
//

#ifndef GSLIB_LINKED_LIST_HPP
#define GSLIB_LINKED_LIST_HPP

#include <interfaces/i_sequence_container.hpp>
#include <iostream>
#include <sstream>
#include <utils/exceptions.hpp>

namespace gsl {
    template <typename T>

    class Node{
    public:
        T _data;
        Node *_pNext;
        explicit Node(T data = T(),Node * pNext = nullptr): _data(data), _pNext(pNext){}
    };

    template<typename T>
    class linked_list : public i_sequence_container<T> {
    public:
        explicit linked_list(): _size(0), _head(nullptr), _tail(_head){}

        [[nodiscard]] size_t size() const override {
            return _size;
        }

        T &front() override {
            return _head->_data;
        }

        T &front() const override {
            return _head->_data;
        }

        T &back() override {
            return _tail->_data;
        }
        T &back() const override {
            return _tail->_data;
        }

        T &operator[](size_t i) override {
            if (i >= _size)
                throw gsl::exceptions::out_of_range(i,_size);
            size_t cnt = 0;
            auto *current = _head;
            for (; current != nullptr; current = current->_pNext) {
                if (i == cnt++)
                  break;
            }
            return current->_data;
        }

        const T &operator[](size_t i) const override {
            if (i >= _size)
                throw gsl::exceptions::out_of_range(i,_size);
            size_t cnt = 0;
            auto* current = _head;
            for (; current != nullptr; current = current->_pNext) {
                if (i == cnt++)
                    break;
            }
            return current->_data;
        }

        void push_back (const T &value) override {
           if (_head == nullptr){
               _head = new Node<T> (value);
               _head->_pNext = _tail;
           }
           else {
               auto* current = _head;
               while (current->_pNext != nullptr)
                   current = current->_pNext;
               current->_pNext = _tail = new Node<T>(value);
           }
           _size++;
        }

        void push_front(const T &value) override {
            _head = new Node<T>(value,_head);
            _size++;
        }

        void pop_back() override {
            erase(_size - 1);
        }

        void pop_front() override {
            auto* current = _head;
            _head = _head->_pNext;
            delete current;
            _size--;
        }

        void insert(const T &value, size_t index) override {
            if (index >= _size)
                throw gsl::exceptions::out_of_range(index,_size);
            if (index == 0)
                push_front(value);
            else {
                auto* previous = _head;
                for (size_t i = 0; i < index -1; i++){
                    previous = previous->_pNext;
                }
                auto *new_el = new Node<T> (value,previous->_pNext);
                previous->_pNext = new_el;
            }
            _size++;
        }

        void erase(size_t index) override {
            if (index >= _size)
                throw gsl::exceptions::out_of_range(index,_size);
            if (index == 0)
                pop_front();
            else {
                auto *previous = _head;
                for (size_t i = 0; i < index - 1; i++) {
                    previous = previous->_pNext;
                }
                Node<T> *del_el = previous->_pNext;
                previous->_pNext = del_el->_pNext;
                delete del_el;
            }
            if (index == _size - 1){
                auto* current = _head;
                while (current->_pNext != nullptr)
                    current = current->_pNext;
                _tail = current;
            }
            _size--;
        }

        void erase(size_t first, size_t last) override {
            if (first >= _size)
                throw gsl::exceptions::out_of_range(first,_size);
            if (last >= _size)
                throw gsl::exceptions::out_of_range(last,_size);
            auto* previous = _head;
            for (size_t i = 0; i < first - 1; i++) {
                previous = previous->_pNext;
            }
            for (size_t i = first; i <= last; i++) {
                Node<T> *del_el = previous->_pNext;
                previous->_pNext = del_el->_pNext;
                delete del_el;
            }
            if (last == _size - 1){
                auto* current = _head;
                while (current->_pNext != nullptr)
                    current = current->_pNext;
                _tail = current;
            }
            _size = _size - last + first - 1;
        }

        void clear () override {
            while (_size)
                pop_front();
        }

        void resize(size_t new_size) override {
            if (new_size > _size) {
                size_t diff = new_size - _size;
                for (size_t i = 0; i < diff; i++)
                    push_back(T());
            }
            else {
                size_t diff = _size - new_size;
                for (size_t i = 0; i < diff; i++)
                    pop_back();
            }
            _size = new_size;
        }

        void resize(size_t new_size, const T &value) override {
            if (new_size > _size) {
                size_t diff = new_size - _size;
                for (size_t i = 0; i < diff; i++)
                    push_back(value);
            }
            else {
                size_t diff = _size - new_size;
                for (size_t i = 0; i < diff; i++)
                    pop_back();
                for (size_t i = 0; i < new_size; i++)
                    push_front(value);
            }
            _size = new_size;
        }

        [[nodiscard]] bool empty() const override {
            return _size == 0;
        }

        [[nodiscard]] std::string to_string() const override { // Временная - O(N) Пространственная - O(N)
            std::stringstream res;
            if (_size == 0)
                res << "[]";
            else {
                res << "[";
                auto *current = _head;
                while (current->_pNext != nullptr) {
                    res << current->_data << ", ";
                    current = current->_pNext;
                }
                res << current->_data << "]";
            }
            return res.str();
        }

        void swap (linked_list& other){
            std::swap(_head,other._head);
            std::swap(_size,other._size);
            std::swap(_tail,other._tail);
        }

        ~linked_list() {
            clear();
        };

        friend std::ostream &operator<<(std::ostream &os, const linked_list &ls) {
            os << ls.to_string();
            return os;
        }

    private:
        size_t _size;
        Node<T>* _head;
        Node<T> *_tail;
    };

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename T>
    class Node <T*> {
    public:
        T* _data;
        Node *_pNext;
        explicit Node(T* data = nullptr,Node * pNext = nullptr): _data(data), _pNext(pNext){}
    };

    template<typename T>
    class linked_list <T*>{
    public:
        explicit linked_list(): _size(0), _head(nullptr), _tail(_head){}

        T *operator[](size_t i) {
            if (i >= _size)
                throw gsl::exceptions::out_of_range(i,_size);
            size_t cnt = 0;
            auto *current = _head;
            for (; current != nullptr; current = current->_pNext) {
                if (i == cnt++)
                  break;
            }
            return current->_data;
        }

        T *operator[](size_t i) const {
            if (i >= _size)
                throw gsl::exceptions::out_of_range(i,_size);
            size_t cnt = 0;
            auto *current = _head;
            for (; current != nullptr; current = current->_pNext) {
                if (i == cnt++)
                    break;
            }
            return current->_data;
        }

        [[nodiscard]] size_t size() const {
            return _size;
        }

        [[nodiscard]] bool empty() const {
            return _size == 0;
        }

        T *front() {
            return _head->_data;
        }

        T *front() const  {
            return _head->_data;
        }

        T *back()  {
            return _tail->_data;
        }
        T *back() const  {
            return _tail->_data;
        }

        void push_back (T *value) {
            if (_head == nullptr){
                _head = new Node<T*> (value);
                _head->_pNext = _tail;
            }
            else {
                auto* current = _head;
                while (current->_pNext != nullptr)
                    current = current->_pNext;
                current->_pNext = _tail = new Node<T*>(value);
            }
            _size++;
        }

        void push_front(T *value)  {
            _head = new Node <T*>(value,_head);
            _size++;
        }

        void pop_back() {
            erase(_size - 1);
        }

        void pop_front()  {
            auto* current = _head;
            _head = _head->_pNext;
            delete current;
            _size--;
        }

        void erase(size_t index) {
            if (index >= _size)
                throw gsl::exceptions::out_of_range(index,_size);
            if (index == 0)
                pop_front();
            else {
                auto *previous = _head;
                for (size_t i = 0; i < index - 1; i++) {
                    previous = previous->_pNext;
                }
                Node<T*> *del_el = previous->_pNext;
                previous->_pNext = del_el->_pNext;
                delete del_el;
            }
            if (index == _size - 1){
                auto* current = _head;
                while (current->_pNext != nullptr)
                    current = current->_pNext;
                _tail = current;
            }
            _size--;
        }

        void erase(size_t first, size_t last)  {
            if (first >= _size)
                throw gsl::exceptions::out_of_range(first,_size);
            if (last >= _size)
                throw gsl::exceptions::out_of_range(last,_size);
            auto* previous = _head;
            for (size_t i = 0; i < first -1; i++){
                previous = previous->_pNext;
            }
            for (size_t i = first;i<=last;i++){
                Node<T*>* del_el = previous->_pNext;
                previous->_pNext = del_el->_pNext;
                delete del_el;
            }
            if (last == _size - 1){
                auto* current = _head;
                while (current->_pNext != nullptr)
                    current = current->_pNext;
                _tail = current;
            }
            _size = _size - last + first - 1;
        }

        void clear ()  {
            while (_size)
                pop_front();
        }

        void insert(T *value, size_t index) {
            if (index >= _size)
                throw gsl::exceptions::out_of_range(index,_size);
            if (index == 0)
                push_front(value);
            else {
                auto* previous = _head;
                for (size_t i = 0; i < index -1; i++){
                    previous = previous->_pNext;
                }
                auto *new_el = new Node<T*> (value,previous->_pNext);
                previous->_pNext = new_el;
            }
            _size++;
        }

        [[nodiscard]] std::string to_string() const { // Временная - O(N) Пространственная - O(N)
            std::stringstream res;
            if (_size == 0)
                res << "[]";
            else {
                res << "[";
                auto *current = _head;
                while (current->_pNext != nullptr) {
                    if (current->_data != nullptr) {
                        res << *current->_data << ", ";
                        current = current->_pNext;
                    }
                    else if (current->_data == nullptr) {
                        res << "nullptr, ";
                        current = current->_pNext;
                    }
                }
                if (current->_data != nullptr)
                    res << *current->_data << "]";
                else
                    res << "nullptr]";
            }
            return res.str();
        }


        void resize(size_t new_size)  {
            if (new_size > _size) {
                size_t diff = new_size - _size;
                T* in = nullptr;
                for (size_t i = 0; i < diff; i++)
                    push_back(in);
            }
            else {
                size_t diff = _size - new_size;
                for (size_t i = 0; i < diff; i++)
                    pop_back();
            }
            _size = new_size;
        }

        void resize(size_t new_size, T *value)  {
            if (new_size > _size) {
                size_t diff = new_size - _size;
                for (size_t i = 0; i < diff; i++)
                    push_back(value);
            }
            else {
                size_t diff = _size - new_size;
                for (size_t i = 0; i < diff; i++)
                    pop_back();
                for (size_t i = 0; i < new_size; i++)
                    push_front(value);
            }
            _size = new_size;
        }

        friend std::ostream &operator<<(std::ostream &os, const linked_list &ls) {
            os << ls.to_string();
            return os;
        }

        ~linked_list() {
            clear();
        };

    private:
        size_t _size;
        Node<T *> * _head;
        Node<T *> * _tail;
    };

}
#endif //GSLIB_LINKED_LIST_HPP
