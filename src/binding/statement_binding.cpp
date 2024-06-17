#pragma once
#include <typeinfo>
#include "binder.cpp"
#include "bound_expression.cpp"
#include "expression_binding.cpp"
#include "bound_scope.cpp"
#include "bound_stmt_exit.cpp"
#include "bound_stmt_expr.cpp"
#include "bound_stmt_block.cpp"
#include "bound_stmt_var_dec.cpp"
#include "bound_expr_call.cpp"
#include "../symbols/function_symbol.cpp"

template<class T>
bound_expression* bind_expression(T* t);

template<class T>
bound_statement* bind_statement(T* t) {
    if (auto stmt = dynamic_cast<stmt_exit*>(t)) {
        return bind_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<stmt_print*>(t)) {
        return bind_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<stmt_exit*>(t)) {
        return bind_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<stmt_block*>(t)) {
        return bind_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<stmt_var_dec*>(t)) {
        return bind_statement(stmt);
    }
    else {
        std::cerr << "Statement node not recognized!    " << typeid(*t).name() << std::endl;
        return nullptr;
    }
}

template<>
bound_statement* bind_statement(stmt_exit* stmt) {
    auto expr = bind_expression(stmt->expr);
    return new bound_stmt_exit(expr);
}

template<>
bound_statement* bind_statement(stmt_block* stmt) {
    std::vector<bound_statement*> statements;

    scope_enter();
    current_scope->var_offset += 8;

    for (const auto& s : stmt->statements) {
        statements.push_back(bind_statement(s));
    }

    auto scope = current_scope;
    scope_leave();

    return new bound_stmt_block(statements, scope);
}

template<>
bound_statement* bind_statement(stmt_print* stmt) {
    auto expr = bind_expression(stmt->expr);

    function_symbol* fun = &function_print_num;
    if (expr->type == &type_bool)
        fun = &function_print_bool;
    else if (expr->type == &type_char)
        fun = &function_print_char;
    
    auto call_expr = new bound_expr_call(fun, { expr });
    return new bound_stmt_expr(call_expr);
}

template<>
bound_statement* bind_statement(stmt_expression* stmt) {
    return new bound_stmt_expr(bind_expression(stmt->expr));
}

template<>
bound_statement* bind_statement(stmt_var_dec* stmt) {
    std::string name = std::get<std::string>(stmt->ident.value.value());
    auto expr = bind_expression(stmt->expr);
    auto var = new variable_symbol(name, expr->type, current_scope->var_offset);

    auto result = current_scope->try_declare(var);
    if (!result) {
        std::cerr << "Variable already declared!    " << name << std::endl;
    }

    return new bound_stmt_var_dec(var, expr);
}