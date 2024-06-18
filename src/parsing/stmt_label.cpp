#pragma once
#include "statement.cpp"
#include "../token.cpp"

class stmt_label : public statement {
    public:
        token kw;
        token label;
        token semi;

        stmt_label(token kw, token label, token semi)
            : kw (kw), label (label), semi (semi) {}
        
        virtual std::vector<node*> get_children() {
            return {};
        }

    protected:
        virtual std::vector<token> list_tokens() {
            return {
                kw,
                label,
                semi,
            };
        }
};