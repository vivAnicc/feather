#pragma once
#include "type.cpp"
#include "../token.cpp"

class type_ptr : public type {
    public:
        type* base;
        token star;

        type_ptr(type* base, token star) : base (base), star (star) {}

        virtual std::vector<node*> get_children() {
            return { base };
        }
    protected:
        virtual std::vector<token> list_tokens() {
            return { star };
        }
};