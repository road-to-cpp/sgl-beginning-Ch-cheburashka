//
// Created by 79056 on 25.12.2022.
//

#ifndef GSLIB_UNORDERED_MAP_HPP
#define GSLIB_UNORDERED_MAP_HPP

#include <interfaces/i_associative_container.hpp>
#include <vector>
#include <containers/unordered_map_iterator.hpp>
#include <utils/pair.hpp>
#include <string>
#include <containers/vector.hpp>

namespace gsl {

    template<typename Key, typename Value>
    class unordered_map : i_associative_container<Key, Value> {
    public:
        using iterator = unordered_map_iterator<Key,Value>;

        struct Bucket {
            Key key;
            Value value;

            friend std::ostream &operator<<(std::ostream &os, const Bucket &bucket) {
                os << "key: " << bucket.key << ", value: " << bucket.value;
                return os;
            }
        };

        unordered_map() {
            _data = std::vector<std::vector<Bucket>>(_capacity);
            _size = 0;
        }

        ~unordered_map() = default;

        void insert(Key const &key, Value const &value) override {
            auto hash = _hasher(key);
            auto index = hash % _capacity;
            if (_data[index].empty()) {
                _data[index].push_back(Bucket{key, value});
                _size++;
            } else {
                for (auto &bucket: _data[index]) {
                    if (bucket.key == key) {
                        bucket.value = value;
                        return;
                    }
                }
                _data[index].push_back(Bucket{key, value});
                _size++;
            }
        }

        Value &operator[](Key const &key) override{
            auto hash = _hasher(key);
            auto index = hash % _capacity;
            if (_data[index].empty()) {
                throw std::out_of_range("Map is empty");
            } else {
                for (auto &bucket: _data[index]) {
                    if (bucket.key == key)
                        return bucket.value;
                }
                throw std::out_of_range("Key not found");
            }
        }

        const Value &operator[](const Key &key) const override {
            auto hash = _hasher(key);
            auto index = hash % _capacity;
            if (_data[index].empty()) {
                throw std::out_of_range("Map is empty");
            } else {
                for (auto &bucket: _data[index]) {
                    if (bucket.key == key)
                        return bucket.value;
                }
                throw std::out_of_range("Key not found");
            }
        }

        Value &at(const Key &key) override {
            auto hash = _hasher(key);
            auto index = hash % _capacity;
            if (_data[index].empty())
                throw std::out_of_range("Map is empty");
            else {
                for (auto &bucket: _data[index]) {
                    if (bucket.key == key)
                        return bucket.value;
                }
                throw std::out_of_range("Key not found");
            }
        }

        const Value &at(const Key &key) const override {
            auto hash = _hasher(key);
            auto index = hash % _capacity;
            if (_data[index].empty())
                throw std::out_of_range("Map is empty");
            else {
                for (auto &bucket: _data[index]) {
                    if (bucket.key == key)
                        return bucket.value;
                }
                throw std::out_of_range("Key not found");
            }
        }

        bool contains(const Key &key) const override {
            auto hash = _hasher(key);
            auto index = hash % _capacity;

            if (_data[index].empty())
                throw std::out_of_range("Key not found");
            else {
                for (auto &bucket: _data[index]) {
                    if (bucket.key == key)
                        return true;
                }
                return false;
            }
        }

        [[nodiscard]] size_t size() const override { return _size; }

        [[nodiscard]] bool empty() const override {return _size == 0;}

        void swap (unordered_map& other) {
            std::swap(_size, other._size);
            std::swap(_capacity, other._capacity);
            std::swap(_data, other._data);
            std::swap(_hasher, other._hasher);
        }

        void emplace(const Key &key, const Value &value) override {
            auto hash = _hasher(key);
            auto index = hash % _capacity;

            if (_data[index].empty()) {
                _data[index].emplace_back(Bucket{key, value});
                _size++;
            }
            else {
                for (auto &bucket: _data[index]) {
                    if (bucket.key == key) {
                        bucket.value = value;
                        return;
                    }
                }
                _data[index].emplace_back(Bucket{key, value});
                _size++;
            }
        }

        iterator find(const Key& key) {
            auto hash = _hasher(key);
            auto index = hash % _capacity;

            if (_data[index].empty())
                throw std::out_of_range("Key not found");
            else {
                for (auto &bucket: _data[index]) {
                    if (bucket.key == key)
                        return iterator(&bucket);
                }
            }
        }

    private:
        std::hash<Key> _hasher;
        std::vector<std::vector<Bucket>> _data;
        size_t _size;
        size_t _capacity = 10;
    };
}

#endif //GSLIB_UNORDERED_MAP_HPP
