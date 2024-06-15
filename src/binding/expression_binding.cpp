#pragma once
#include "binder.cpp"
#include "bound_expression.cpp"
#include "bound_expr_term.cpp"
#include "bound_expr_error.cpp"
#include "bound_op_binary.cpp"
#include "bound_expr_binary.cpp"

template<class T>
bound_expression* bind_expression(T* t) {
    if (auto expr = dynamic_cast<expr_binary*>(t)) {
        return bind_expression(expr);
    }
    else if (auto expr = dynamic_cast<term_literal*>(t)) {
        return bind_expression(expr);
    }
    else if (auto expr = dynamic_cast<term_paren*>(t)) {
        return bind_expression(expr);
    }
    else {
        std::cerr << "Expression node not recognized!" << std::endl;
        return nullptr;
    }
}

template<>
bound_expression* bind_expression(expr_binary* expr) {
    auto left = bind_expression(expr->left);

    if (is_error(left)) {
        return new bound_expr_error();
    }

    auto right = bind_expression(expr->right);

    if (is_error(right)) {
        return new bound_expr_error();
    }

    auto op = bind_binary_operator(expr->op, left->type, right->type);

    if (!op.has_value()) {
        return new bound_expr_error();
    }

    return new bound_expr_binary(left, right, op.value());
}

template<>
bound_expression* bind_expression(term_literal* expr) {
    return new bound_expr_term(expr->value, value_to_type(expr->value));
}

template<>
bound_expression* bind_expression(term_paren* expr) {
    return bind_expression(expr->expr);
}