#pragma once
#include "bound_statement.cpp"
#include "bound_scope.cpp"

class bound_stmt_block : public bound_statement {
    public:
        std::vector<bound_statement*> statements;
        bound_scope* scope;

        bound_stmt_block(std::vector<bound_statement*> statements, bound_scope* scope)
            : statements (statements), scope (scope) {}
        
        virtual std::vector<bound_node*> get_children() {
            return std::vector<bound_node*>(statements.begin(), statements.end());
        }
};