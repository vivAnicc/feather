#pragma once
#include <sstream>
#include "term.cpp"
#include "../token.cpp"

class term_paren : public term {
    public:
        token open;
        expression* expr;
        token close;

        term_paren(token open, expression* expr, token close) :
            open (open), expr (expr), close (close) {}

        virtual std::vector<node*> get_children() {
            return { expr };
        }

    protected:
        virtual std::vector<token> list_tokens() {
            return {
                open,
                close,
            };
        }
};