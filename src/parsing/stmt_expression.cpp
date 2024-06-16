#pragma once
#include "expression.cpp"
#include "statement.cpp"
#include "../token.cpp"

class stmt_expression : public statement {
    public:
        expression* expr;
        token semi;

        stmt_expression(expression* expr, token semi) :
            expr (expr), semi (semi) {}
        
        virtual std::vector<node*> get_children() {
            return { expr };
        }
    
    protected:
        virtual std::vector<token> list_tokens() {
            return { semi };
        }
};