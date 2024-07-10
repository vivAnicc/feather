#pragma once
#include "type.cpp"
#include "../token.cpp"

class type_builtin : public type {
    public:
        token ident;

        type_builtin(token ident) : ident (ident) {}

        virtual std::vector<node*> get_children() {
            return {};
        }
    protected:
        virtual std::vector<token> list_tokens() {
            return { ident };
        }
};