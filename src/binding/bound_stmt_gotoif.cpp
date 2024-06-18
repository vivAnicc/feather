#pragma once
#include "bound_statement.cpp"
#include "bound_expression.cpp"

class bound_stmt_gotoif : public bound_statement {
    public:
        std::string label;
        bound_expression* expr;
        bool comp;

        bound_stmt_gotoif(std::string label, bound_expression* expr, bool comp)
            : label (label), expr (expr), comp (comp) {}
        
        virtual std::vector<bound_node*> get_children() {
            return { expr };
        }
};