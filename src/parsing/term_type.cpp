#pragma once
#include "term.cpp"
#include "../token.cpp"

class term_type : public term {
    public:
        token type;

        term_type(token type) : type (type) {}

        virtual std::vector<node*> get_children() {
            return {};
        }

    protected:
        virtual std::vector<token> list_tokens() {
            return { type };
        }
};