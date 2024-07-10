#pragma once
#include "bound_expression.cpp"
#include "../symbols/variable_symbol.cpp"
#include "bound_lvalue.cpp"

class bound_expr_var : public bound_expression, public bound_lvalue {
    public:
        variable_symbol* var;
        bound_scope* scope;

        bound_expr_var(variable_symbol* var, bound_scope* scope) :
            var (var), scope (scope), bound_expression (var->type) {}
        
        virtual std::vector<bound_node*> get_children() {
            return {};
        }

        virtual std::string get_address() {
            return STACK_COUNTER + " - " + std::to_string(scope->get_offset(var) + var->type->size);
        }
};