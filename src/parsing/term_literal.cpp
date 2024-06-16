#pragma once
#include <vector>
#include <sstream>
#include <variant>
#include "term.cpp"
#include "../token.cpp"

class term_literal : public term {
    public:
        token lit;
        lit_value value;

        term_literal(token lit) : lit (lit), value (lit.value.value()) {}

        virtual std::vector<node*> get_children() {
            return {};
        }

    protected:
        virtual std::vector<token> list_tokens() {
            return { lit };
        }
};