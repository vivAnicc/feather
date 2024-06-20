#pragma once
#include <vector>
#include "../binding/statement_binding.cpp"
#include "../binding/lowered_block_start.cpp"
#include "../binding/lowered_block_end.cpp"
#include "expression_lowering.cpp"

#define vs std::vector<bound_statement*>

template<class T>
vs lower_statement(T* t) {
    if (t == NULL) {
        std::cerr << "Null node encountered!" << std::endl;
        return { statement_error() };
    }
    if (auto stmt = dynamic_cast<bound_stmt_block*>(t)) {
        return lower_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<bound_stmt_if*>(t)) {
        return lower_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<bound_stmt_function*>(t)) {
        return lower_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<bound_stmt_exit*>(t)) {
        return lower_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<bound_stmt_expr*>(t)) {
        return lower_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<bound_stmt_gotoif*>(t)) {
        return lower_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<bound_stmt_return*>(t)) {
        return lower_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<bound_stmt_var_ass*>(t)) {
        return lower_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<bound_stmt_var_dec*>(t)) {
        return lower_statement(stmt);
    }
    else {
        return { t };
    }
}

template<>
vs lower_statement(bound_stmt_block* stmt) {
    vs v;

    v.push_back(new lowered_block_start);

    for (const auto& s : stmt->statements) {
        auto res = lower_statement(s);
        v.insert(v.end(), res.begin(), res.end());
    }

    v.push_back(new lowered_block_end);

    return v;
}

template<>
vs lower_statement(bound_stmt_if* stmt) {
    auto expr = lower_expression(stmt->expr);
    auto stmts = lower_statement(stmt->stmt);
    auto label_end = get_label("if_end");
    std::string label_else;
    if (stmt->stmt_else.has_value())
        label_else = get_label("if_else");

    vs res;
    bound_statement* gt;
    bound_statement* gt_end;
    if (stmt->stmt_else.has_value()) {
        gt = new bound_stmt_gotoif(label_else, expr, false);
        gt_end = new bound_stmt_goto(label_end);
    }
    else {
        gt = new bound_stmt_gotoif(label_end, expr, false);
    }
    auto stmt_label_end = new bound_stmt_label(label_end);
    bound_statement* stmt_label_else;
    if (stmt->stmt_else.has_value()) {
        stmt_label_else = new bound_stmt_label(label_else);
    }

    res.push_back(gt);
    res.insert(res.end(), stmts.begin(), stmts.end());
    if (stmt->stmt_else.has_value()) {
        res.push_back(gt_end);
        res.push_back(stmt_label_else);
        auto stmts_else = lower_statement(stmt->stmt_else.value());
        res.insert(res.end(), stmts_else.begin(), stmts_else.end());
    }
    res.push_back(stmt_label_end);

    return res;
}

template<>
vs lower_statement(bound_stmt_function* stmt) {
    auto expr = lower_expression(stmt->body);
    auto s = new bound_stmt_function(stmt->function, stmt->params, expr);

    return { s };
}

template<>
vs lower_statement(bound_stmt_exit* stmt) {
    auto expr = lower_expression(stmt->expr);

    return { new bound_stmt_exit(expr) };
}

template<>
vs lower_statement(bound_stmt_expr* stmt) {
    auto expr = lower_expression(stmt->expr);

    return { new bound_stmt_expr(expr) };
}

template<>
vs lower_statement(bound_stmt_gotoif* stmt) {
    auto expr = lower_expression(stmt->expr);

    return { new bound_stmt_gotoif(stmt->label, expr, stmt->comp) };
}

template<>
vs lower_statement(bound_stmt_return* stmt) {
    auto expr = lower_expression(stmt->expr);

    return { new bound_stmt_return(expr) };
}

template<>
vs lower_statement(bound_stmt_var_ass* stmt) {
    auto expr = lower_expression(stmt->expr);

    return { new bound_stmt_var_ass(stmt->var, expr, stmt->offset) };
}

template<>
vs lower_statement(bound_stmt_var_dec* stmt) {
    auto expr = lower_expression(stmt->expr);

    return { new bound_stmt_var_dec(stmt->var, expr) };
}