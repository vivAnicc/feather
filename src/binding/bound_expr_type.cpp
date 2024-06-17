#pragma once
#include "bound_expression.cpp"
#include "../symbols/type_symbol.cpp"

class bound_expr_type : public bound_expression {
    public:
        bound_expr_type(type_symbol* type) : bound_expression (type) {}

        virtual std::vector<bound_node*> get_children() {
            return {};
        }
};