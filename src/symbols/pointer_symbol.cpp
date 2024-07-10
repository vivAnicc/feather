#pragma once
#include "type_symbol.cpp"
#include <map>

class pointer_symbol : public type_symbol {
    public:
        type_symbol* base;

        pointer_symbol(type_symbol* base)
            : type_symbol(base->name + "*", 8, true), base (base) {}
};

std::map<type_symbol*, pointer_symbol*> ptr_map;
pointer_symbol* pointer(type_symbol* base) {
    if (ptr_map.count(base) == 1) {
        return ptr_map[base];
    }
    auto ptr = new pointer_symbol(base);
    ptr_map[base] = ptr;
    return ptr;
}