#pragma once
#include "bound_expression.cpp"
#include "bound_op_binary.cpp"

class bound_expr_binary : public bound_expression {
    public:
        bound_expression* left;
        bound_expression* right;
        bound_op_binary op;
        int temp;
        bound_scope* scope;

        bound_expr_binary(bound_expression* left, bound_expression* right, bound_op_binary op, int temp, bound_scope* scope) :
            bound_expression(op.result), left (left), right (right), op (op), temp (temp), scope (scope) {}

        virtual std::vector<bound_node*> get_children() {
            return {
                left,
                right
            };
        }
};