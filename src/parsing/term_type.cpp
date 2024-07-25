#pragma once
#include "term.cpp"
#include "type.cpp"
#include "../token.cpp"

class term_type : public term {
    public:
        token kw;
        type* t;

        term_type(token kw, type* t) : kw (kw), t (t) {}

        virtual std::vector<node*> get_children() {
            return { t };
        }

    protected:
        virtual std::vector<token> list_tokens() {
            return { kw };
        }
};