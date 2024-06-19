#pragma once
#include <sstream>
#include <typeinfo>
#include "emitter.cpp"
#include "expression_emitting.cpp"
#include "../binding/bound_stmt_gotoif.cpp"
#include "../binding/statement_binding.cpp"
#include "../binding/lowered_block_start.cpp"
#include "../binding/lowered_block_end.cpp"

std::string current_label;

void regenerate_label() {
    if (current_label == "")
        current_label = get_label("end_label");
}

std::string consume_label() {
    std::string label = current_label;
    current_label = "";
    return label;
}

template<class T>
std::stringstream emit_statement(T* t) {
    if (t == NULL) {
        std::cerr << "Null node encountered!" << std::endl;
        return std::stringstream();
    }
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
    else if (auto stmt = dynamic_cast<bound_stmt_var_ass*>(t)) {
        return emit_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<bound_stmt_label*>(t)) {
        return emit_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<bound_stmt_goto*>(t)) {
        return emit_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<bound_stmt_gotoif*>(t)) {
        return emit_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<bound_stmt_function*>(t)) {
        return emit_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<bound_stmt_return*>(t)) {
        return emit_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<lowered_block_end*>(t)) {
        return emit_statement(stmt);
    }
    else if (auto stmt = dynamic_cast<lowered_block_start*>(t)) {
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

std::stringstream emit_block_start() {
    std::stringstream s;

    emit_line(&s, "push " + STACK_COUNTER);
    emit_line(&s, "mov " + STACK_COUNTER + ", " + STACK_POINTER);

    return s;
}

template<>
std::stringstream emit_statement(lowered_block_start* stmt) {
    return emit_block_start();
}

std::stringstream emit_block_end() {
    std::stringstream s;

    emit_line(&s, "mov " + STACK_POINTER + ", " + STACK_COUNTER);
    emit_line(&s, "pop " + STACK_COUNTER);

    return s;
}

template<>
std::stringstream emit_statement(lowered_block_end* stmt) {
    return emit_block_end();
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

template<>
std::stringstream emit_statement(bound_stmt_var_ass* stmt) {
    std::stringstream s;

    int size = stmt->var->type->size;
    // int offset = stmt->var->offset + 8;
    int offset = stmt->offset;

    s = emit_expression(stmt->expr);
    clear_register(&s, RAX, size);
    emit_line(&s, "mov [" + STACK_COUNTER + " - " + std::to_string(offset) + "], rax");

    return s;
}

template<>
std::stringstream emit_statement(bound_stmt_label* stmt) {
    std::stringstream s;

    emit_line(&s, stmt->name + ":");

    return s;
}

template<>
std::stringstream emit_statement(bound_stmt_goto* stmt) {
    std::stringstream s;

    emit_line(&s, "jmp " + stmt->label);

    return s;
}

template<>
std::stringstream emit_statement(bound_stmt_gotoif* stmt) {
    std::stringstream s;

    int size = stmt->expr->type->size;
    auto rax = get_register(RAX, size);

    s = emit_expression(stmt->expr);
    emit_line(&s, "cmp " + rax + ", 0");
    if (stmt->comp)
        emit_line(&s, "jne " + stmt->label);
    else
        emit_line(&s, "je " + stmt->label);

    return s;
}

template<>
std::stringstream emit_statement(bound_stmt_function* stmt) {
    std::stringstream s;

    std::string label = "function_" + stmt->function->name;

    emit_line(&s, label + ":");
    s << emit_statement(stmt->body).str();
    emit_line(&s, "ret");

    return s;
}

template<>
std::stringstream emit_statement(bound_stmt_return* stmt) {
    std::stringstream s;

    s = emit_expression(stmt->expr);
    regenerate_label();
    emit_line(&s, "jmp " + current_label);

    return s;
}