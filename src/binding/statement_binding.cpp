#pragma once
#include <typeinfo>
#include "binder.cpp"
#include "bound_expression.cpp"
#include "type_binding.cpp"
#include "bound_scope.cpp"
#include "bound_stmt_exit.cpp"
#include "bound_stmt_expr.cpp"
#include "bound_stmt_block.cpp"
#include "bound_stmt_var_dec.cpp"
#include "bound_stmt_label.cpp"
#include "bound_stmt_goto.cpp"
#include "bound_stmt_if.cpp"
#include "bound_stmt_gotoif.cpp"
#include "bound_stmt_function.cpp"
#include "bound_stmt_return.cpp"
#include "bound_expr_call.cpp"
#include "bound_expr_error.cpp"
#include "../symbols/function_symbol.cpp"

template<class T>
bound_expression* bind_expression(T* t);
std::optional<type_symbol*> string_to_type(const std::string& name);

bound_statement* statement_error() {
    return new bound_stmt_expr(new bound_expr_error());
}

template<class T>
bound_statement* bind_statement(T* t) {
    if (t == NULL) {
        std::cerr << "Null node encountered!" << std::endl;
        return statement_error();
    }
    if (auto stmt = dynamic_cast<stmt_exit*>(t)) {
        return bind_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<stmt_print*>(t)) {
        return bind_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<stmt_expression*>(t)) {
        return bind_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<stmt_block*>(t)) {
        return bind_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<stmt_var_dec*>(t)) {
        return bind_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<stmt_label*>(t)) {
        return bind_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<stmt_goto*>(t)) {
        return bind_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<stmt_if*>(t)) {
        return bind_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<stmt_function*>(t)) {
        return bind_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<stmt_return*>(t)) {
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
    // current_scope->var_offset += 8;

    for (const auto& s : stmt->statements) {
        statements.push_back(bind_statement(s));
    }

    auto scope = scope_leave();

    return new bound_stmt_block(statements, scope);
}

template<>
bound_statement* bind_statement(stmt_print* stmt) {
    int t = get_temp_var(8);
    auto expr = bind_expression(stmt->expr);
    remove_temp_var(8);

    function_symbol* fun = &function_print_num;
    if (expr->type == &type_bool)
        fun = &function_print_bool;
    else if (expr->type == &type_char)
        fun = &function_print_char;
    
    auto call_expr = new bound_expr_call(fun, { expr }, t, current_scope);
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
    auto var = new variable_symbol(name, expr->type, current_scope->var_size);

    auto result = current_scope->try_declare(var);
    if (!result) {
        std::cerr << "Variable already declared!    " << name << std::endl;
    }

    return new bound_stmt_var_dec(var, expr);
}

template<>
bound_statement* bind_statement(stmt_label* stmt) {
    auto name = std::get<std::string>(stmt->label.value.value());
    auto label = "_" + name;
    
    return new bound_stmt_label(label);
}

template<>
bound_statement* bind_statement(stmt_goto* stmt) {
    auto name = std::get<std::string>(stmt->label.value.value());
    auto label = "_" + name;

    return new bound_stmt_goto(label);
}

template<>
bound_statement* bind_statement(stmt_if* stmt) {
    auto expr = bind_expression(stmt->expr);
    auto s = bind_statement(stmt->stmt);
    std::optional<bound_statement*> s_else = std::nullopt;
    if (stmt->has_else()) {
        s_else = bind_statement(stmt->stmt_else.value());
    }

    return new bound_stmt_if(expr, s, s_else);
}

template<>
bound_statement* bind_statement(stmt_function* stmt) {
    std::vector<parameter_symbol*> v;
    v.resize(stmt->params.size());

    auto scope = current_scope;
    current_scope = new bound_scope;

    for (int i = 0; i < stmt->params.size(); i++) {
        auto param = stmt->params[i];
        std::string name = std::get<std::string>(param.ident.value.value());
        type_symbol* type = bind_type(param.t);
        v[i] = new parameter_symbol(name, type, i);
        current_scope->try_declare(v[i]);
    }

    // address for return
    // current_scope->var_offset += 8;
    get_temp_var(8);
    
    std::string name = std::get<std::string>(stmt->ident.value.value());

    auto body = bind_expression(stmt->body);
    auto function = new function_symbol(name, body->type, v);
    scope->try_declare(function);

    remove_temp_var(8);
    current_scope = scope;

    return new bound_stmt_function(function, v, body);
}

template<>
bound_statement* bind_statement(stmt_return* stmt) {
    auto expr = bind_expression(stmt->expr);
    return new bound_stmt_return(expr);
}