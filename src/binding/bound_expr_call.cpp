#pragma once
#include <vector>
#include "bound_expression.cpp"
#include "../symbols/function_symbol.cpp"

class bound_expr_call : public bound_expression {
    public:
        std::vector<bound_expression*> params;
        function_symbol* function;
        int temp;
        bound_scope* scope;

        bound_expr_call(function_symbol* function, std::vector<bound_expression*> params, int temp, bound_scope* scope) :
            bound_expression (function->return_type), function (function), params (params), temp (temp), scope (scope) {}

        virtual std::vector<bound_node*> get_children() {
            return std::vector<bound_node*>(params.begin(), params.end());
        }
};