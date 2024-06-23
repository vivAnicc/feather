#pragma once
#include "bound_expression.cpp"
#include "bound_op_unary.cpp"

class bound_expr_unary : public bound_expression {
    public:
        bound_expression* operand;
        bound_op_unary op;

        bound_expr_unary(bound_expression* operand, bound_op_unary op)
            : bound_expression(op.result), operand (operand), op (op) {}
        
        virtual std::vector<bound_node*> get_children() {
            return { operand };
        }
};