#pragma once
#include "type.cpp"
#include "expression.cpp"
#include "../token.cpp"

class type_expr : public type {
    public:
        token kw;
        token open;
        expression* expr;
        token close;

        type_expr(token kw, token open, expression* expr, token close)
            : kw (kw), open (open), expr (expr), close (close) {}

        virtual std::vector<node*> get_children() {
            return { expr };
        }
    protected:
        virtual std::vector<token> list_tokens() {
            return {
                kw,
                open,
                close,
            };
        }
};