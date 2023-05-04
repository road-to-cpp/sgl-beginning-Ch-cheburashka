//
// Created by 79056 on 05.11.2022.
//
#include <iostream>
#include <string>
#include "containers/unordered_map/unordered_map.hpp"
#include <utils/string_utils.hpp>
#include <string_view>

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

int main() {

    std::cout << "////////////////---- str_utils ----//////////////////// " << "\n\n";

    std::cout << "ends with:\n";
    if (gsl::string_utils::ends_with("demogorgon","gor"))
        std::cout << "true\n\n";
    else
        std::cout << "false\n\n";

    std::cout << "starts with:\n";
    if (gsl::string_utils::starts_with("demogorgon","dem"))
        std::cout << "true\n\n";
    else
        std::cout << "false\n\n";

    std::cout << "trim:\n";
    std::cout << "|  shishka kaif  |" << "\n|" << gsl::string_utils::trim("  shishka kaif  ") << "|\n\n";

    std::cout << "uppercase:\n";
    std::cout << R"("My Anaconda Don't ..." --- ")" << gsl::string_utils::uppercase("My Anaconda Don't ...") << "\"\n\n";

    std::cout << "lowercase:\n";
    std::cout << R"("You Other Brothers Can't DENY ..." --- ")" << gsl::string_utils::lowercase("You Other Brothers Can't DENY ...") << "\"\n\n";

    std::cout << "split:\n";
    std::string s = "Take care of each other, Slavs brothers!";
    std::cout << s << "\n---\n";
    for (auto &v : gsl::string_utils::split(s," "))
        std::cout << v << "\n";
    std::cout << '\n';

    std::cout << "join:\n";
    std::vector<int> values = {1, 2, 3, 4};
    std::string joined;
    std::cout << gsl::string_utils::join(joined,values,"<") << "\n\n";

    std::vector<std::string> values_s = {"shampun", "smestitel", "germafrodit", "beresa"};
    std::string joined_2;
    std::cout << gsl::string_utils::join(joined_2,values_s,"-") << "\n\n";

    std::cout << "////////////////---- unordered_map ----//////////////////// " << "\n\n";

    gsl::unordered_map<std::string,int> map;

    std::cout << map.capacity() << '\n';
    map.insert("mother", 30);
    map.insert("father", 32);
    map.insert("daughter", 7);
    map.insert("son", 3);
    map.insert("grandma", 67);
    map.insert("shit", 3); // hehe boi
    std::cout << map.capacity() << '\n';

    map.erase("son");

    auto iter = map.find("son");

    if (iter == map.end()) {std::cout << "Not found\n"; } // output: "Not found"

    else {
        std::cout << "iterator (first and second):\n";
        std::cout << (*iter).key << std::endl; // output: "father"
        std::cout << (*iter).value << std::endl << std::endl; // output: 32
    }


    std::cout << "size:\n";
    std::cout << map.size() << std::endl << std::endl; // output: 5

    std::cout << "contains:\n";
    std::cout << map.contains("mother") << std::endl << std::endl; //output: 1

    std::cout << "search:\n";
    std::cout << map.at("daughter") << std::endl << std::endl; //output: 7

    std::cout << "empty:\n";
    std::cout << map.empty() << std::endl << std::endl; //output: 0

    auto iterator = map.begin();
    std::cout << *iterator << std::endl << std::endl; // key: mother, value: 30

    map.insert("mother1", 30);
    map.insert("father2", 32);
    map.insert("daughter3", 7);
    map.insert("son4", 3);
    map.insert("grandma5", 3);
    map.emplace("bullshit",34);


    auto iterat = map.find("bullshit");
    std::cout << "iterat: " << (*iterat).key << " " << (*iterat).value << std::endl;

    std::cout << map;
    return 0;
}

