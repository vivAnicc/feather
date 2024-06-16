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
type_symbol type_string = type_symbol("string", 1, true);
type_symbol type_char = type_symbol("char", 1);
type_symbol type_bool = type_symbol("bool", 1);
type_symbol type_error = type_symbol("?", 0);
type_symbol type_void = type_symbol("void", 0, true);

const type_symbol value_to_type(const lit_value& value) {
    switch (value.index())
    {
    case 0:
        return type_int;
    case 1:
        return type_string;
    case 2:
        return type_char;
    case 3:
        return type_bool;
    
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
    else if (type == type_char) {
        return 2;
    }
    else if (type == type_bool) {
        return 3;
    }
    else return -1;
}