#pragma once
#include "variable_symbol.cpp"

class parameter_symbol : public variable_symbol {
    public:
        parameter_symbol(std::string name, type_symbol* type, int ordinal) :
            variable_symbol (name, type, ordinal) {}
};