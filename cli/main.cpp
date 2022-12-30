//
// Created by 79056 on 05.11.2022.
//
#include <iostream>

#include <string>
#include <containers/unordered_map.hpp>
#include <unordered_map>
#include <vector>

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


template<typename T>
class binary_tree {
public:
    struct Node {
        T data;
        Node *left = nullptr;
        Node *right = nullptr;
    };

    binary_tree() : _head(nullptr) {}

    ~binary_tree() = default;

    void insert(T const &value) {
        if (_head == nullptr) {
            _head = new Node{value};
            _size++;
        } else {
            auto current_node = _head;
            while (true) {
                if (value < current_node->data) {
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

    [[nodiscard]] std::string to_string() const  {
        std::stringstream res;
        std::vector<T> vector;
        if (_size == 0)
            res << "[]";
        else {
            res << "[";
            auto *current = _head;
            while (current->left != nullptr) {
                vector.push_back(current->data);
                current = current->left;
            }
            vector.push_back(current->data);
            size_t i = vector.size() - 1;
            for (auto iterator = vector.begin();iterator != vector.end(); iterator++) { res << vector[i--] << ", "; }
            current = _head->right;
            while (current->right != nullptr) {
                res << current->data << ", ";
                current = current->right;
            }
            res << current->data << "]";
        }
        return res.str();
    }

    friend std::ostream& operator<<(std::ostream& os, binary_tree<T> const& tree) {
        os << tree.to_string();
        return os;
    }
private:
    size_t _size = 0;
    Node *_head;
};


int main() {

    gsl::unordered_map<std::string,int> map;

    map.insert("mother", 30);
    map.insert("father", 32);
    map.insert("daughter", 7);
    map.emplace("son", 3);

    auto it = map.find("father");

    std::cout << "iterator (first and second):\n";
    std::cout << it.first << std::endl; // output: "father"
    std::cout << it.second << std::endl << std::endl; // output: 32


    std::cout << "size:\n";
    std::cout << map.size() << std::endl << std::endl; // output: 4

    std::cout << "contains:\n";
    std::cout << map.contains("mother") << std::endl << std::endl; //output: 1

    std::cout << "search:\n";
    std::cout << map["son"] << std::endl; //output: 3
    std::cout << map.at("daughter") << std::endl << std::endl; //output: 7

    std::cout << "empty:\n";
    std::cout << map.empty() << std::endl; //output: 0



    return 0;
}

