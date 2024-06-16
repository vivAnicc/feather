#pragma once
#include <sstream>
#include "expression.cpp"
#include "../token.cpp"
#include "binary_operator.cpp"

class expr_binary : public expression {
    public:
        expression* left;
        token op_token;
        expression* right;
        binary_operator op;

        expr_binary(expression* left, token op_token, expression* right, binary_operator op)
            : left (left), op_token (op_token), right (right), op (op) {}

        virtual std::vector<node*> get_children() {
            return {
                left, right
            };
        }

    protected:
        virtual std::vector<token> list_tokens() {
            return { op_token };
        }
};