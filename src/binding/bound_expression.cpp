#pragma once
#include "bound_node.cpp"
#include "../symbols/type_symbol.cpp"

class bound_expression : public bound_node {
    public:
        type_symbol type;
        
        bound_expression(type_symbol type) : type (type) {}
};