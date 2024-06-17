#pragma once
#include "bound_expression.cpp"

class bound_expr_error : public bound_expression {
    public:
        bound_expr_error() : bound_expression(&type_error) {}

        virtual std::vector<bound_node*> get_children() {
            return {};
        }
};