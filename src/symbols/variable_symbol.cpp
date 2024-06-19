#pragma once
#include "symbol.cpp"
#include "type_symbol.cpp"

class variable_symbol : public symbol {
    public:
        type_symbol* type;
        int offset;
    private:
        bool is_parameter;

    public:
        variable_symbol(std::string name, type_symbol* type, int offset, bool param = false)
            : symbol (name), type (type), offset (offset), is_parameter (param) {}
        
        bool is_param() {
            return is_parameter;
        }
};