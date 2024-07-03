#pragma once
#include <variant>
#include <optional>
#include "binder.cpp"
#include "bound_expression.cpp"
#include "bound_expr_term.cpp"
#include "bound_expr_error.cpp"
#include "bound_expr_binary.cpp"
#include "bound_expr_unary.cpp"
#include "bound_expr_type.cpp"
#include "bound_expr_var.cpp"
#include "bound_expr_stmt.cpp"
#include "bound_op_binary.cpp"
#include "bound_stmt_block.cpp"

template<class T>
bound_expression* bind_expression(T* t) {
    if (t == NULL) {
        std::cerr << "Null node encountered!" << std::endl;
        return new bound_expr_error;
    }
    if (auto expr = dynamic_cast<expr_binary*>(t)) {
        return bind_expression(expr);
    }
    else if (auto expr = dynamic_cast<expr_unary*>(t)) {
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
    else if (auto expr = dynamic_cast<term_statement*>(t)) {
        return bind_expression(expr);
    }
    else if (auto expr = dynamic_cast<term_call*>(t)) {
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

    if (expr->op == binary_operator::assign) {
        if (!dynamic_cast<bound_lvalue*>(left)) {
            std::cerr << "Invalid lvalue" << std::endl;
            return new bound_expr_error;
        }
    }

    // Count for push
    current_scope->var_offset += 8;
    auto right = bind_expression(expr->right);
    current_scope->var_offset -= 8;

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
bound_expression* bind_expression(expr_unary* expr) {
    auto operand = bind_expression(expr->operand);

    if (is_error(operand)) {
        return new bound_expr_error;
    }

    auto op = bind_unary_operator(expr->op, operand->type);

    if (!op.has_value()) {
        return new bound_expr_error;
    }

    return new bound_expr_unary(operand, op.value());
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
    int offset = current_scope->get_offset(var) + 8;
    // if (var->is_param()) {
    //     offset = (var->offset * 8) + 8;
    // }
    // else {
    //     offset = current_scope->get_offset(var) + 8;
    // }

    if (var) {
        return new bound_expr_var(var, offset);
    }

    return new bound_expr_error;
}

template<>
bound_expression* bind_expression(term_statement* expr) {
    std::vector<bound_statement*> v;
    type_symbol* type = &type_void;

    scope_enter();

    for (const auto& s : expr->statements) {
        auto bs = bind_statement(s);
        v.push_back(bs);
        bound_node* n;
        if (auto ret = find_return(bs)) {
            type = ret->expr->type;
        }
        // if (auto ret = try_get<bound_stmt_return>(bs)) {
        //    type = ret->expr->type;
        //}
    }

    scope_leave();

    return new bound_expr_stmt(type, v);
}

bound_stmt_return* find_return(bound_node* n) {
    bound_stmt_return* ret;
    if (ret = try_get<bound_stmt_return*>(n))
        return ret;
    if (auto expr = try_get<bound_expr_stmt*>(n))
        return nullptr;
    if (auto stmt = try_get<bound_stmt_block*(n)) {
        for (const auto child : stmt.get_children()) {
            if (ret = find_return(child))
                return ret;
        }
    }
    
    return nullptr;
}

template<>
bound_expression* bind_expression(term_call* expr) {
    std::string name = std::get<std::string>(expr->ident.value.value());
    auto fun = current_scope->get_function(name);
    std::vector<bound_expression*> v;
    for (const auto& param : expr->params) {
        v.push_back(bind_expression(param.expr));
    }

    return new bound_expr_call(fun, v);
}