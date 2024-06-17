#pragma once
#include "symbol.cpp"
#include "type_symbol.cpp"

class variable_symbol : public symbol {
    public:
        type_symbol* type;
        int offset;

        variable_symbol(std::string name, type_symbol* type, int offset)
            : symbol (name), type (type), offset (offset) {}
};