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
    std::stringstream s;
    s << ";; " << typeid(*t).name() << std::endl;
    if (auto stmt = dynamic_cast<bound_stmt_expr*>(t)) {
        s << emit_statement(stmt).str();
        return s;
    }
    else if (auto stmt = dynamic_cast<bound_stmt_exit*>(t)) {
        s << emit_statement(stmt).str();
        return s;
    }
    else if (auto stmt = dynamic_cast<bound_stmt_block*>(t)) {
        s << emit_statement(stmt).str();
        return s;
    }
    else if (auto stmt = dynamic_cast<bound_stmt_var_dec*>(t)) {
        s << emit_statement(stmt).str();
        return s;
    }
    else if (auto stmt = dynamic_cast<bound_stmt_label*>(t)) {
        s << emit_statement(stmt).str();
        return s;
    }
    else if (auto stmt = dynamic_cast<bound_stmt_goto*>(t)) {
        s << emit_statement(stmt).str();
        return s;
    }
    else if (auto stmt = dynamic_cast<bound_stmt_gotoif*>(t)) {
        s << emit_statement(stmt).str();
        return s;
    }
    else if (auto stmt = dynamic_cast<bound_stmt_function*>(t)) {
        s << emit_statement(stmt).str();
        return s;
    }
    else if (auto stmt = dynamic_cast<bound_stmt_return*>(t)) {
        s << emit_statement(stmt).str();
        return s;
    }
    else if (auto stmt = dynamic_cast<lowered_block_end*>(t)) {
        s << emit_statement(stmt).str();
        return s;
    }
    else if (auto stmt = dynamic_cast<lowered_block_start*>(t)) {
        s << emit_statement(stmt).str();
        return s;
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

std::stringstream emit_block_start(int var_sizes) {
    std::stringstream s;

    emit_line(&s, "push " + STACK_COUNTER);
    emit_line(&s, "mov " + STACK_COUNTER + ", " + STACK_POINTER);
    emit_line(&s, "sub " + STACK_POINTER + ", " + std::to_string(var_sizes));

    return s;
}

template<>
std::stringstream emit_statement(lowered_block_start* stmt) {
    return emit_block_start(stmt->scope->offset());
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
    auto rax = get_register(RAX, size);
    auto ptr = get_size(size);
    
    s = emit_expression(stmt->expr);
    // clear_register(&s, RAX, size);
    emit_line(&s, "mov " + ptr + " [rbp - " + std::to_string(stmt->var->offset + size) + "], " + rax);
    // emit_line(&s, "push rax");

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
    auto label_name = get_label("function_end");
    auto label_end = new bound_stmt_label(label_name);
    auto gt = new bound_stmt_goto(label_name);

    s << emit_statement(gt).str();
    emit_line(&s, label + ":");
    s << emit_expression(stmt->body).str();
    emit_line(&s, "ret");
    s << emit_statement(label_end).str();

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