//
// Created by 79056 on 05.11.2022.
//
#include <iostream>
#include <containers/vector.hpp>
#include <utils/pair.hpp>
#include <string>
#include <unordered_map>

struct test_struct {
    int value = 10;
    bool flag = true;

    bool operator==(test_struct const &other) const {
        return value == other.value && flag == other.flag;
    }

    friend std::ostream &operator<<(std::ostream &os, test_struct const &ts) {
        os << "{ value: " << ts.value << " flag: " << ts.flag << " }";
        return os;
    }
};

template<typename Kt, typename Vt>
class unordered_map {
public:
    unordered_map() {
        _data = std::vector<std::vector<Bucket>>(_capacity);
        _size = 0;
    }

    ~unordered_map() {}

    void insert(Kt const &key, Vt const &value) {
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

    Vt &operator[](Kt const &key) {
        auto hash = _hasher(key);
        auto index = hash % _capacity;

        if (_data[index].empty()) {
            throw std::out_of_range("Key not found");
        } else {
            for (auto &bucket: _data[index]) {
                if (bucket.key == key) {
                    return bucket.value;
                }
            }
            throw std::out_of_range("Key not found");
        }
    }

    struct Bucket {
        Kt key;
        Vt value;
    };
private:
    std::hash<Kt> _hasher;
    std::vector<std::vector<Bucket>> _data;
    size_t _size;
    size_t _capacity = 10;
};


template<typename T>
class binary_tree {
public:
    struct Node {
        T data;
        Node *left = nullptr;
        Node *right = nullptr;
    };

    binary_tree() : _head(nullptr) {}

    ~binary_tree() {
    }

    void insert(T const &value) {
        if (_head == nullptr) {
            _head = new Node{value};
            _size++;
        } else {
            auto current_node = _head;
            while (true) {
                if (value > current_node->data) {
                    if (current_node->left == nullptr) {
                        current_node->left = new Node{value};
                        _size++;
                        break;
                    } else {
                        current_node = current_node->left;
                    }
                } else {
                    if (current_node->right == nullptr) {
                        current_node->right = new Node{value};
                        _size++;
                        break;
                    } else {
                        current_node = current_node->right;
                    }
                }
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, binary_tree<T> const& tree) {}
private:
    size_t _size = 0;
    Node *_head;
};


int main() {

    return 0;
}