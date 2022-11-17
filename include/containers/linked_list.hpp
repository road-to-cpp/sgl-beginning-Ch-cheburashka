//
// Created by MrMam on 01.11.2022.
//

#ifndef GSLIB_LINKED_LIST_HPP
#define GSLIB_LINKED_LIST_HPP

#include <interfaces/i_sequence_container.hpp>
#include <string>

namespace gsl {
    template <typename T>

    class Node{
    public:
        Node *_pNext;
        T _data;
        explicit Node(T data = T(),Node * pNext = nullptr): _data(data), _pNext(pNext){}
    };

    template<typename T>
    class linked_list : public i_sequence_container<T> {
    public:
        explicit linked_list(): _size(0), _head(nullptr){}

        size_t size() const override {
            return _size;
        }

        T &front() override {
            return _head->_data;
        }

        T &front() const override {
            return _head->_data;
        }

        T &back() override {
            Node<T>* current = _head;
            while (current->_pNext != nullptr)
                current = current->_pNext;
            return current->_data;
        }
        T &back() const override {
            Node<T>* current = _head;
            while (current->_pNext != nullptr)
                current = current->_pNext;
            return current->_data;
        }


        T &operator[](size_t i) override {
            int cnt = 0;
            Node<T>* current = _head;
            for (; current->_pNext != nullptr; current = current->_pNext){
                if (i == cnt++)
                    break;
            }
            return current->_data;
        }

        T &operator[](size_t i) const override {
            int cnt = 0;
            Node<T>* current = _head;
            for (; current->_pNext != nullptr; current = current->_pNext){
                if (i == cnt++)
                    break;
            }
            return current->_data;
        }


        void push_back (const T &value) override {
           if (_head == nullptr){
               _head = new Node<T> (value);
           }
           else {
               Node<T>* current = _head;
               while (current->_pNext != nullptr)
                   current = current->_pNext;
               current->_pNext = new Node<T>(value);
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
            Node<T>* current = _head;
            _head = _head->_pNext;
            delete current;
            _size--;
        }

        void insert(const T &value, size_t index) override {
            if (index == 0)
                push_front(value);
            else {
                Node<T>* previous = _head;
                for (size_t i = 0; i < index -1; i++){
                    previous = previous->_pNext;
                }
                Node<T>* new_el = new Node<T> (value,previous->_pNext);
                previous->_pNext = new_el;
            }
            _size++;
        }

        void erase(size_t index) override {
            if (index == 0)
                pop_front();
            else {
                Node<T>* previous = _head;
                for (size_t i = 0; i < index -1; i++){
                    previous = previous->_pNext;
                }
                Node<T>* del_el = previous->_pNext;
                previous->_pNext = del_el->_pNext;
                delete del_el;
            }
            _size--;
        }

        void erase(size_t first, size_t last) override {
            size_t diff = last - first + 1;
            Node<T>* previous = _head;
            for (size_t i = 0; i < first -1; i++){
                previous = previous->_pNext;
            }
            for (size_t i = first;i<=last;i++){
                Node<T>* del_el = previous->_pNext;
                previous->_pNext = del_el->_pNext;
                delete del_el;
            }
            _size = _size - diff;
        }

        void clear () override {
            while (_size)
                pop_front();
        }

        void resize(size_t new_size) override {
            for (int i =0; i < new_size-_size; i++) {
                push_back(T());
            }
            _size = new_size;
        }

        void resize(size_t new_size, const T &value) override {
            for (int i =0; i < new_size-_size; i++) {
                push_back(value);
            }
            _size = new_size;
        }

        bool empty() const override {
            return _size == 0;
        }

        std::string to_string() const override {
            std::string res;
            res.append("[");
            Node<T>* current = _head;
            while (current->_pNext != nullptr){
                res.append(std::to_string(current->_data));
                res.append(", ");
                current = current->_pNext;
            }
            res.append(std::to_string(current->_data));
            res.append("]");
            return res;
        }

        ~linked_list() {
            clear();
        };

        friend std::ostream &operator<<(std::ostream &os, const linked_list &ls) {
            for (int i = 0; i < ls._size; i++) {
                os << ls[i] << " ";
            }
            os << '\n';
            return os;
        }

    private:
        size_t _size;
        Node<T>* _head;
    };

}
#endif //GSLIB_LINKED_LIST_HPP
