#pragma once
#include <string>

class symbol {
    public:
        std::string name;

        symbol (std::string name) : name (name) {}

        bool operator==(const symbol& other) {
            return name == other.name;
        }
};

template<class S>
bool operator==(const S& l, const S& r) {
    return symbol(l) == symbol(r);
}

template<class S>
bool operator!=(const S& l, const S& r) {
    return symbol(l) != symbol(r);
}