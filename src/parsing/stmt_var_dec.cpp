#pragma once
#include "statement.cpp"
#include "expression.cpp"
#include "../token.cpp"

class stmt_var_dec : public statement {
    public:
        token var;
        token ident;
        token equals;
        expression* expr;
        token semi;

        stmt_var_dec(token var, token ident, token equals, expression* expr, token semi)
            : var (var), ident (ident), equals (equals), expr (expr), semi (semi) {}
        
        virtual std::vector<node*> get_children() {
            return { expr };
        }

    protected:
        virtual std::vector<token> list_tokens() {
            return {
                var,
                ident,
                equals,
                semi,
            };
        }
};