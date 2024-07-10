#pragma once
#include "type.cpp"
#include "../token.cpp"

class type_deref : public type {
    public:
        type* base;
        token dot;
        token ident;

        type_deref(type* base, token dot, token ident) :
            base (base), dot (dot), ident (ident) {}
        
        virtual std::vector<node*> get_children() {
            return { base };
        }
    protected:
        virtual std::vector<token> list_tokens() {
            return {
                dot,
                ident,
            };
        }
};