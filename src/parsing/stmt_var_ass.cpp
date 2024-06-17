#pragma once
#include "statement.cpp"
#include "../token.cpp"
#include "expression.cpp"

class stmt_var_ass : public statement {
    public:
        token ident;
        token equals;
        expression* expr;
        token semi;
        
        stmt_var_ass(token ident, token equals, expression* expr, token semi)
            : ident (ident), equals (equals), expr (expr), semi (semi) {}
        
        virtual std::vector<node*> get_children() {
            return { expr };
        }
    
    protected:
        virtual std::vector<token> list_tokens() {
            return {
                ident,
                equals,
                semi,
            };
        }
};