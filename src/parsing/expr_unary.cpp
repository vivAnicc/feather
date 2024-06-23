#pragma once
#include "expression.cpp"
#include "../token.cpp"
#include "unary_operator.cpp"

class expr_unary : public expression {
    public:
        expression* operand;
        token op_token;
        unary_operator op;

        expr_unary(expression* operand, token op_token, unary_operator op)
            : operand (operand), op_token (op_token), op (op) {}
        
        virtual std::vector<node*> get_children() {
            return { operand };
        }

    protected:
        virtual std::vector<token> list_tokens() {
            return { op_token };
        }
};