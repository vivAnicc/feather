#pragma once
#include <sstream>
#include <typeinfo>
#include "emitter.cpp"
#include "expression_emitting.cpp"
#include "../binding/statement_binding.cpp"

template<class T>
std::stringstream emit_statement(T* t) {
    if (auto stmt = dynamic_cast<bound_stmt_expr*>(t)) {
        return emit_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<bound_stmt_exit*>(t)) {
        return emit_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<bound_stmt_block*>(t)) {
        return emit_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<bound_stmt_var_dec*>(t)) {
        return emit_statement(stmt);
    }
    else {
        std::cerr << "Bound statement not recognized!    " << typeid(*t).name() << std::endl;
        return std::stringstream();
    }
}

template<>
std::stringstream emit_statement(bound_stmt_expr* stmt) {
    std::stringstream s;

    // the output goes into rax except if it is a pointer, but we dont use them you
    s = emit_expression(stmt->expr);
    // emit_line(&s, "add rsp, " + std::to_string(stmt->expr->type.size));

    return s;
}

template<>
std::stringstream emit_statement(bound_stmt_exit* stmt) {
    std::stringstream s;

    int size = stmt->expr->type->size;
    auto rdi = get_register(RDI, size);
    auto rax = get_register(RAX, size);

    s = emit_expression(stmt->expr);
    emit_line(&s, "mov " + rdi + ", " + rax);
    emit_line(&s, "mov rax, 60");
    emit_line(&s, "syscall");

    return s;
}

template<>
std::stringstream emit_statement(bound_stmt_block* stmt) {
    std::stringstream s;

    emit_line(&s, "push " + STACK_COUNTER);
    emit_line(&s, "mov " + STACK_COUNTER + ", " + STACK_POINTER);
    
    for (const auto& statement : stmt->statements) {
        s << emit_statement(statement).str();
    }

    emit_line(&s, "mov " + STACK_POINTER + ", " + STACK_COUNTER);
    emit_line(&s, "pop " + STACK_COUNTER);

    return s;
}

template<>
std::stringstream emit_statement(bound_stmt_var_dec* stmt) {
    std::stringstream s;

    int size = stmt->var->type->size;
    
    s = emit_expression(stmt->expr);
    clear_register(&s, RAX, size);
    emit_line(&s, "push rax");

    return s;
}