#pragma once
#include <string>
#include "bound_statement.cpp"
#include "bound_expression.cpp"
#include "../symbols/function_symbol.cpp"

class bound_stmt_function : public bound_statement {
    public:
        function_symbol* function;
        std::vector<parameter_symbol*> params;
        bound_expression* body;

        bound_stmt_function(function_symbol* function, std::vector<parameter_symbol*> params, bound_expression* body)
            : function (function), params (params), body (body) {}
        
        virtual std::vector<bound_node*> get_children() {
            return { body };
        }
};