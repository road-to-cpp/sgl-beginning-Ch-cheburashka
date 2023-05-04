//
// Created by 79056 on 25.12.2022.
//

#ifndef GSLIB_UNORDERED_MAP_HPP
#define GSLIB_UNORDERED_MAP_HPP

#include "interfaces/i_associative_container.hpp"
#include <vector>
#include "unordered_map_iterator.hpp"
#include <string>
#include "containers/vector/vector.hpp"
#include <list>
#include <algorithm>

namespace gsl {

    template<typename Key, typename Value>
    class unordered_map : i_associative_container<Key, Value> {
    public:
        using iterator = unordered_map_iterator<Key, Value>;

        struct Bucket {
            Key key;
            Value value;
            friend std::ostream &operator<<(std::ostream &os, const Bucket &bucket) {
                os << "key: " << bucket.key << ", value: " << bucket.value;
                return os;
            }
        };

        iterator begin() {
            auto outer_it = std::find_if(
                    _data.begin(), _data.end(), [](auto const &list) {
                        return !list.empty();
                    });
            return iterator(outer_it, outer_it->begin());
        }

        iterator end() {
            return iterator(_data.end(), _data.end()->end());
        }

        unordered_map() {
            _data = std::vector<std::list<Bucket>>(_capacity);
            _size = 0;
        }

        ~unordered_map() = default;

        void insert(Key const &key, Value const &value) override {
            // check if map occupied more than 75% of capacity
            if (double(_size) >= double(_capacity) * 0.75) {
                // resize
                _capacity *= 2;
                std::vector<std::list<Bucket>> new_data(_capacity);
                for (auto &bucket: _data) {
                    for (auto &item: bucket) {
                        size_t index = _hasher(item.key) % _capacity;
                        new_data[index].emplace_back(std::move(item));
                    }
                }
                _data = std::move(new_data);
            }
            auto hash = _hasher(key);
            auto index = hash % _capacity;

            // check if key already exists
            auto found = std::find_if(_data[index].begin(), _data[index].end(),
                                      [&key](const Bucket &bucket) { return bucket.key == key; });

            if (found != _data[index].end()) {
                found->value = value;
                return;
            } else {
                _data[index].push_back(Bucket{key, value});
                _size++;
            }
        }

        Value &operator[](Key const &key) override {
            auto hash = _hasher(key);
            auto index = hash % _capacity;
            if (_data.empty()) {
                throw std::out_of_range("Unordered_map is empty");
            } else {
                for (auto &bucket: _data[index]) {
                    if (bucket.key == key)
                        return bucket.value;
                }
                throw std::out_of_range("Key not found");
            }
        }

        const Value &operator[](const Key &key) const override {
            if (_data.empty())
                throw std::out_of_range("Unordered_map is empty");
            auto hash = _hasher(key);
            auto index = hash % _capacity;

            for (auto &bucket: _data[index]) {
                if (bucket.key == key)
                    return bucket.value;
            }
            throw std::out_of_range("Key not found");
        }

        Value &at(const Key &key) override {
            if (_data.empty())
                throw std::out_of_range("Unordered_map is empty");
            auto hash = _hasher(key);
            auto index = hash % _capacity;

            for (auto &bucket: _data[index]) {
                if (bucket.key == key)
                    return bucket.value;
            }
            throw std::out_of_range("Key not found");
        }

        const Value &at(const Key &key) const override {
            if (_data.empty())
                throw std::out_of_range("Unordered_map is empty");
            auto hash = _hasher(key);
            auto index = hash % _capacity;

            for (auto &bucket: _data[index]) {
                if (bucket.key == key)
                    return bucket.value;
            }
            throw std::out_of_range("Key not found");
        }

        bool contains(const Key &key) const override {
            if (_data.empty())
                throw std::out_of_range("Unordered_map is empty");
            auto hash = _hasher(key);
            auto index = hash % _capacity;

            return (
                    std::find_if(_data[index].begin(), _data[index].end(),
                                 [&key](const Bucket &bucket) { return bucket.key == key; }) !=
                    _data[index].end());
        }

        [[nodiscard]] size_t size() const override { return _size; }

        [[nodiscard]] bool empty() const override { return _size == 0; }

        [[nodiscard]] size_t capacity() const { return _capacity; }

        void swap(unordered_map &other) {
            std::swap(_size, other._size);
            std::swap(_capacity, other._capacity);
            std::swap(_data, other._data);
            std::swap(_hasher, other._hasher);
        }

        void clear() {
            _data.clear();
            _size = 0;
            _capacity = 0;
        }

        void erase(const Key &key) {
            auto hash = _hasher(key);
            auto index = hash % _capacity;

            _data[index].erase(std::remove_if(_data[index].begin(), _data[index].end(),
                                              [&key](const Bucket &bucket) { return bucket.key == key; }),_data[index].end());
            --_size;
        }

        void erase(const iterator &it) {
            auto hash = _hasher((*it).key);
            auto index = hash % _capacity;

            _data[index].erase(std::remove_if(_data[index].begin(), _data[index].end(),
                                              [&it](const Bucket &bucket) { return bucket.key == (*it).key; }),_data[index].end());
            --_size;
        }

        void emplace(const Key &key, const Value &value) override {
            if (double(_size) >= double(_capacity) * 0.75) {
                _capacity *= 2;
                std::vector<std::list<Bucket>> new_data(_capacity);
                for (auto &bucket: _data) {
                    for (auto &item: bucket) {
                        size_t index = _hasher(item.key) % _capacity;
                        new_data[index].emplace_back(std::move(item));
                    }
                }
                _data = std::move(new_data);
            }
            auto hash = _hasher(key);
            auto index = hash % _capacity;

            auto found = std::find_if(_data[index].begin(), _data[index].end(),
                                      [&key](const Bucket &bucket) { return bucket.key == key; });

            if (found != _data[index].end()) {
                found->value = value;
                return;
            } else {
                _data[index].emplace_back(Bucket{std::move(key),value});
                _size++;
            }
        }

        template<typename ...Args>
        void emplace(Key const &key, Args &&... args) {
            if (double(_size) >= double(_capacity) * 0.75) {
                _capacity *= 2;
                std::vector<std::list<Bucket>> new_data(_capacity);
                for (auto &bucket: _data) {
                    for (auto &item: bucket) {
                        size_t index = _hasher(item.key) % _capacity;
                        new_data[index].emplace_back(std::move(item));
                    }
                }
                _data = std::move(new_data);
            }
            auto hash = _hasher(key);
            auto index = hash % _capacity;

            auto found = std::find_if(_data[index].begin(), _data[index].end(),
                                      [&key](const Bucket &bucket) { return bucket.key == key; });

            Value value = Value(std::forward<Args>(args)...);

            if (found != _data[index].end()) {
                found->value = value;
                return;
            } else {
                _data[index].emplace_back(Bucket{std::move(key),value});
                _size++;
            }
        }

        template<typename ...Args>
        void emplace(Key &&key, Args &&... args) {
            if (double(_size) >= double(_capacity) * 0.75) {
                _capacity *= 2;
                std::vector<std::list<Bucket>> new_data(_capacity);
                for (auto &bucket: _data) {
                    for (auto &item: bucket) {
                        size_t index = _hasher(item.key) % _capacity;
                        new_data[index].emplace_back(std::move(item));
                    }
                }
                _data = std::move(new_data);
            }
            auto hash = _hasher(key);
            auto index = hash % _capacity;

            auto found = std::find_if(_data[index].begin(), _data[index].end(),
                                      [&key](const Bucket &bucket) { return bucket.key == key; });

            Value value = Value(std::forward<Args>(args)...);

            if (found != _data[index].end()) {
                found->value = value;
                return;
            } else {
                _data[index].emplace_back(Bucket{std::move(key),value});
                _size++;
            }
        }

        iterator find(const Key &key) {
            if (_data.empty())
                throw std::out_of_range("Unordered_map is empty");
            auto hash = _hasher(key);
            auto index = hash % _capacity;

            auto found = std::find_if(_data[index].begin(), _data[index].end(),
                                      [&key](const Bucket &bucket) { return bucket.key == key; });
            if (found != _data[index].end()) {
                return iterator(_data.begin() + index, found);
            }
            return end();
        }

        [[nodiscard]] std::string to_string() const override {
            std::stringstream res;
            if (_size == 0)
                res << "{}";
            else {
                res << "{";
                for (size_t i = 0; i < _data.size(); ++i) {
                    for (auto j = _data[i].begin(); j != _data[i].end(); ++j) {
                        if (i + 1 == _data.size()) {
                            res << (*j).key << ":" << (*j).value;
                        } else {
                            res << (*j).key << ":" << (*j).value << ", ";
                        }
                    }
                }
            }
            res << "}";
            return res.str();
        }

        friend std::ostream& operator<<(std::ostream &os, const unordered_map& u_map) {
            os << u_map.to_string();
            return os;
        }
    private:
        std::hash<Key> _hasher;
        std::vector<std::list<Bucket>> _data;
        size_t _size;
        size_t _capacity = 1;

    };
}

#endif //GSLIB_UNORDERED_MAP_HPP
