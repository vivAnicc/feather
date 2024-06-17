#pragma once
#include "bound_expression.cpp"
#include "../symbols/variable_symbol.cpp"

class bound_expr_var : public bound_expression {
    public:
        variable_symbol* var;

        bound_expr_var(variable_symbol* var) :
            var (var), bound_expression (var->type) {}
        
        virtual std::vector<bound_node*> get_children() {
            return {};
        }
};