#pragma once
#include <optional>
#include "bound_statement.cpp"
#include "bound_expression.cpp"

class bound_stmt_if : public bound_statement {
    public:
        bound_expression* expr;
        bound_statement* stmt;
        std::optional<bound_statement*> stmt_else;

        bound_stmt_if(bound_expression* expr, bound_statement* stmt, std::optional<bound_statement*> stmt_else)
            : expr (expr), stmt (stmt), stmt_else (stmt_else) {}
        
        virtual std::vector<bound_node*> get_children() {
            if (stmt_else.has_value())
                return {
                expr, 
                stmt,
                stmt_else.value(),
            };
            return {
                expr, 
                stmt,
            };
        }
};