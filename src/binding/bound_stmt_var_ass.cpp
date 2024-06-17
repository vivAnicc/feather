#pragma once
#include "bound_statement.cpp"
#include "bound_expression.cpp"
#include "../symbols/variable_symbol.cpp"

class bound_stmt_var_ass : public bound_statement {
    public:
        variable_symbol* var;
        bound_expression* expr;
    
    bound_stmt_var_ass(variable_symbol* var, bound_expression* expr) 
        : var (var), expr (expr) {}
    
    virtual std::vector<bound_node*> get_children() {
        return { expr };
    }
};