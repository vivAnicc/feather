#pragma once
#include <variant>
#include "binder.cpp"
#include "bound_expression.cpp"
#include "bound_expr_term.cpp"
#include "bound_expr_error.cpp"
#include "bound_expr_binary.cpp"
#include "bound_expr_type.cpp"
#include"bound_expr_var.cpp"
#include "bound_op_binary.cpp"

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
    else if (auto expr = dynamic_cast<term_type*>(t)) {
        return bind_expression(expr);
    }
    else if (auto expr = dynamic_cast<term_var*>(t)) {
        return bind_expression(expr);
    }
    else {
        std::cerr << "Expression node not recognized!" << std::endl;
        return new bound_expr_error;
    }
}

template<>
bound_expression* bind_expression(expr_binary* expr) {
    auto left = bind_expression(expr->left);

    if (is_error(left)) {
        return new bound_expr_error;
    }

    auto right = bind_expression(expr->right);

    if (is_error(right)) {
        return new bound_expr_error;
    }

    auto op = bind_binary_operator(expr->op, left->type, right->type);

    if (!op.has_value()) {
        return new bound_expr_error;
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

template<>
bound_expression* bind_expression(term_type* expr) {
    auto type_name = std::get<std::string>(expr->type.value.value());
    auto type = string_to_type(type_name);

    if (type.has_value()) {
        return new bound_expr_type(type.value());
    }
    
    return new bound_expr_error;
}

template<>
bound_expression* bind_expression(term_var* expr) {
    auto name = std::get<std::string>(expr->ident.value.value());
    auto var = current_scope->get_variable(name);
    if (var) {
        return new bound_expr_var(var);
    }

    return new bound_expr_error;
}