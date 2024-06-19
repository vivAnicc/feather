#pragma once
#include "bound_statement.cpp"
#include "bound_expression.cpp"

class bound_stmt_return : public bound_statement {
    public:
        bound_expression* expr;

        bound_stmt_return(bound_expression* expr) : expr (expr) {}

        virtual std::vector<bound_node*> get_children() {
            return { expr };
        }
};