#pragma once
#include "statement.cpp"
#include "../token.cpp"

class stmt_goto : public statement {
    public:
        token gt;
        token label;
        token semi;

        stmt_goto(token gt, token label, token semi) :
            gt (gt), label (label), semi (semi) {}
        
        virtual std::vector<node*> get_children() {
            return {};
        }

    protected:
        virtual std::vector<token> list_tokens() {
            return {
                gt,
                label,
                semi,
            };
        }
};