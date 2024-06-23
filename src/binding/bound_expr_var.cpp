#pragma once
#include "bound_expression.cpp"
#include "../symbols/variable_symbol.cpp"
#include "bound_lvalue.cpp"

class bound_expr_var : public bound_expression, public bound_lvalue {
    public:
        variable_symbol* var;
        int offset;

        bound_expr_var(variable_symbol* var, int offset) :
            var (var), offset (offset), bound_expression (var->type) {}
        
        virtual std::vector<bound_node*> get_children() {
            return {};
        }

        virtual std::string get_address() {
            return STACK_COUNTER + " - " + std::to_string(offset);
        }
};