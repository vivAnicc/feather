#pragma once
#include "statement.cpp"
#include "expression.cpp"
#include "../token.cpp"

class stmt_return : public statement {
    public:
        token kw;
        expression* expr;
        token semi;

        stmt_return (token kw, expression* expr, token semi)
            : kw (kw), expr (expr), semi (semi) {}
        
        virtual std::vector<node*> get_children() {
            return { expr };
        }

    protected:
        virtual std::vector<token> list_tokens() {
            return {
                kw,
                semi,
            };
        }
};