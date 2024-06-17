#pragma once
#include "bound_expression.cpp"
#include "../token.cpp"

class bound_expr_term : public bound_expression {
    public:
        lit_value value;

        bound_expr_term(lit_value value, type_symbol* type) :
            value (value), bound_expression (type) {}

        virtual std::vector<bound_node*> get_children() {
            return {};
        }
};