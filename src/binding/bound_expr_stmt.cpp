#pragma once
#include "bound_expression.cpp"
#include "bound_statement.cpp"
#include "../symbols/type_symbol.cpp"

class bound_expr_stmt : public bound_expression {
    public:
        std::vector<bound_statement*> statements;

        bound_expr_stmt(type_symbol* type, std::vector<bound_statement*> statements)
            : bound_expression (type), statements (statements) {}
        
        virtual std::vector<bound_node*> get_children() {
            return std::vector<bound_node*>(statements.begin(), statements.end());
        }
};