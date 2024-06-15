#pragma once
#include "symbol.cpp"

class type_symbol : public symbol {
    public:
        bool is_pointer;
        int size;

        type_symbol(std::string name, int size, bool is_pointer = false)
            : symbol (name), size (size), is_pointer (is_pointer) {}
};

type_symbol type_int = type_symbol("int", 4);