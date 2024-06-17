#pragma once
#include "term.cpp"
#include "../token.cpp"

class term_var : public term {
    public:
        token ident;

        term_var(token ident) : ident (ident) {}

        virtual std::vector<node*> get_children() {
            return {};
        }

    protected:
        virtual std::vector<token> list_tokens() {
            return { ident };
        }
};