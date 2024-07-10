#pragma once
#include "type.cpp"
#include "../token.cpp"

class type_ident : public type {
    public:
        token type;

        type_ident(token type) : type (type) {}

        virtual std::vector<node*> get_children() {
            return {};
        }

    protected:
        virtual std::vector<token> list_tokens() {
            return { type };
        }
};