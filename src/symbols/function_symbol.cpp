#pragma once
#include <vector>
#include "symbol.cpp"
#include "parameter_symbol.cpp"

class function_symbol : public symbol {
    public:
        type_symbol return_type;
        std::vector<parameter_symbol> params;

        function_symbol(std::string name, type_symbol return_type, std::vector<parameter_symbol> params)
            : symbol (name), return_type (return_type), params (params) {}
};

function_symbol function_print_num ("print_num", type_void, { parameter_symbol("val", type_int, 0) });
function_symbol function_print_bool ("print_bool", type_void, { parameter_symbol("val", type_bool, 0) });
function_symbol function_print_char ("print_char", type_void, { parameter_symbol("val", type_char, 0) });