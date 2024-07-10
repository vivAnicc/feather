#pragma once
#include "../binding/expression_binding.cpp"
#include "statement_lowering.cpp"

template<class T>
std::vector<bound_statement*> lower_statement(T* t);

template<class T>
bound_expression* lower_expression(T* t) {
    if (t == NULL) {
        std::cerr << "Null node encountered!" << std::endl;
        return new bound_expr_error;
    }
    if (auto stmt = dynamic_cast<bound_expr_error*>(t)) {
        std::cerr << "Error expression ecountered!" << std::endl;
        return { stmt };
        // return lower_expression(stmt);
    }
    else if (auto stmt = dynamic_cast<bound_expr_stmt*>(t)) {
        return lower_expression(stmt);
    }
    else if (auto stmt = dynamic_cast<bound_expr_binary*>(t)) {
        return lower_expression(stmt);
    }
    else if (auto stmt = dynamic_cast<bound_expr_unary*>(t)) {
        return lower_expression(stmt);
    }
    else if (auto stmt = dynamic_cast<bound_expr_call*>(t)) {
        return lower_expression(stmt);
    }
    else {
        return { t };
    }
}

template<>
bound_expression* lower_expression(bound_expr_stmt* expr) {
    std::vector<bound_statement*> s;

    s.push_back(new lowered_block_start(expr->scope));
    for (const auto& stmt : expr->statements) {
        auto res = lower_statement(stmt);
        s.insert(s.end(), res.begin(), res.end());
    }
    // done in emitting
    // s.push_back(new lowered_block_end);

    return new bound_expr_stmt(expr->type, s, expr->scope);
}

template<>
bound_expression* lower_expression(bound_expr_binary* expr) {
    auto left = lower_expression(expr->left);
    auto right = lower_expression(expr->right);

    return new bound_expr_binary(left, right, expr->op, expr->temp, expr->scope);
}

template<>
bound_expression* lower_expression(bound_expr_unary* expr) {
    auto operand = lower_expression(expr->operand);

    return new bound_expr_unary(operand, expr->op);
}

template<>
bound_expression* lower_expression(bound_expr_call* expr) {
    std::vector<bound_expression*> v;

    for (const auto& e : expr->params) {
        v.push_back(lower_expression(e));
    }

    return new bound_expr_call(expr->function, v, expr->temp, expr->scope);
}