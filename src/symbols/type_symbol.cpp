#pragma once
#include "symbol.cpp"
#include "../token.cpp"

class type_symbol : public symbol {
    public:
        bool is_pointer;
        int size;

        type_symbol(std::string name, int size, bool is_pointer = false)
            : symbol (name), size (size), is_pointer (is_pointer) {}
};

type_symbol type_int = type_symbol("int", 8);
type_symbol type_string = type_symbol("string", 8, true);
type_symbol type_error = type_symbol("?", 0);
type_symbol type_void = type_symbol("void", 8, true);

const type_symbol value_to_type(const lit_value& value) {
    switch (value.index())
    {
    case 0:
        return type_int;
    case 1:
        return type_string;
    
    default:
        return type_error;
    }
}

const int type_to_value_index(const type_symbol& type) {
    if (type == type_int) {
        return 0;
    }
    else if (type == type_string) {
        return 1;
    }
    else return -1;
}