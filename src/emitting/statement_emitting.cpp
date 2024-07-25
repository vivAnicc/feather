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
void emit_statement(T* t) {
    if (t == NULL) {
        std::cerr << "Null node encountered!" << std::endl;
        return;
    }
    
    emit_comment(typeid(*t).name());
    // s << ";; " << typeid(*t).name() << std::endl;
    if (auto stmt = dynamic_cast<bound_stmt_expr*>(t)) {
        emit_statement(stmt);
        return;
    }
    else if (auto stmt = dynamic_cast<bound_stmt_exit*>(t)) {
        emit_statement(stmt);
        return;
    }
    else if (auto stmt = dynamic_cast<bound_stmt_block*>(t)) {
        emit_statement(stmt);
        find_return;
    }
    else if (auto stmt = dynamic_cast<bound_stmt_var_dec*>(t)) {
        emit_statement(stmt);
        return;
    }
    else if (auto stmt = dynamic_cast<bound_stmt_label*>(t)) {
        emit_statement(stmt);
        return;
    }
    else if (auto stmt = dynamic_cast<bound_stmt_goto*>(t)) {
        emit_statement(stmt);
        return;
    }
    else if (auto stmt = dynamic_cast<bound_stmt_gotoif*>(t)) {
        emit_statement(stmt);
        return;
    }
    else if (auto stmt = dynamic_cast<bound_stmt_function*>(t)) {
        emit_statement(stmt);
        return;
    }
    else if (auto stmt = dynamic_cast<bound_stmt_return*>(t)) {
        emit_statement(stmt);
        return;
    }
    else if (auto stmt = dynamic_cast<lowered_block_end*>(t)) {
        emit_statement(stmt);
        return;
    }
    else if (auto stmt = dynamic_cast<lowered_block_start*>(t)) {
        emit_statement(stmt);
        return;
    }
    else {
        std::cerr << "Bound statement not recognized!    " << typeid(*t).name() << std::endl;
        return;
    }
}

template<>
void emit_statement(bound_stmt_expr* stmt) {
    // the output goes into rax except if it is a pointer, but we dont use them you
    emit_expression(stmt->expr);
    // emit_line(&s, "add rsp, " + std::to_string(stmt->expr->type.size));

    return;
}

template<>
void emit_statement(bound_stmt_exit* stmt) {
    int size = stmt->expr->type->size;
    auto rdi = get_register(RDI, size);
    auto rax = get_register(RAX, size);

    emit_expression(stmt->expr);
    emit_instr(opcode::mov, rdi, rax);
    emit_instr(opcode::mov, &RAX, 60);
    emit_instr(opcode::syscall);
    // emit_line(&s, "mov " + rdi + ", " + rax);
    // emit_line(&s, "mov rax, 60");
    // emit_line(&s, "syscall");

    return;
}

template<>
void emit_statement(bound_stmt_block* stmt) {
    emit_instr(opcode::push, STACK_COUNTER);
    emit_instr(opcode::mov, STACK_COUNTER, STACK_POINTER);
    // emit_line(&s, "push " + STACK_COUNTER);
    // emit_line(&s, "mov " + STACK_COUNTER + ", " + STACK_POINTER);
    
    for (const auto& statement : stmt->statements) {
        emit_statement(statement);
    }

    emit_instr(opcode::mov, STACK_POINTER, STACK_COUNTER);
    emit_instr(opcode::pop, STACK_COUNTER);
    // emit_line(&s, "mov " + STACK_POINTER + ", " + STACK_COUNTER);
    // emit_line(&s, "pop " + STACK_COUNTER);

    return;
}

void emit_block_start(int var_sizes) {
    emit_instr(opcode::push, STACK_COUNTER);
    emit_instr(opcode::mov, STACK_COUNTER, STACK_POINTER);
    emit_instr(opcode::sub, STACK_POINTER, var_sizes);
    // emit_line(&s, "push " + STACK_COUNTER);
    // emit_line(&s, "mov " + STACK_COUNTER + ", " + STACK_POINTER);
    // emit_line(&s, "sub " + STACK_POINTER + ", " + std::to_string(var_sizes));

    return;
}

template<>
void emit_statement(lowered_block_start* stmt) {
    return emit_block_start(stmt->scope->offset());
}

void emit_block_end() {
    emit_instr(opcode::mov, STACK_POINTER, STACK_COUNTER);
    emit_instr(opcode::pop, STACK_COUNTER);
    // emit_line(&s, "mov " + STACK_POINTER + ", " + STACK_COUNTER);
    // emit_line(&s, "pop " + STACK_COUNTER);

    return;
}

template<>
void emit_statement(lowered_block_end* stmt) {
    return emit_block_end();
}

template<>
void emit_statement(bound_stmt_var_dec* stmt) {
    int size = stmt->var->type->size;
    auto rax = get_register(RAX, size);
    auto ptr = get_size(size);
    
    emit_expression(stmt->expr);
    // clear_register(&s, RAX, size);
    emit_instr(opcode::mov, operation { ptr, &RBP, {}, {}, stmt->var->offset + size }, rax);
    // emit_line(&s, "mov " + ptr + " [rbp - " + std::to_string(stmt->var->offset + size) + "], " + rax);
    // emit_line(&s, "push rax");

    return;
}

template<>
void emit_statement(bound_stmt_label* stmt) {
    emit_label(stmt->name);
    // emit_line(&s, stmt->name + ":");

    return;
}

template<>
void emit_statement(bound_stmt_goto* stmt) {
    emit_instr(opcode::jmp, stmt->label);
    // emit_line(&s, "jmp " + stmt->label);

    return;
}

template<>
void emit_statement(bound_stmt_gotoif* stmt) {
    int size = stmt->expr->type->size;
    auto rax = get_register(RAX, size);

    emit_expression(stmt->expr);
    emit_instr(opcode::cmp, rax, 0);
    // emit_line(&s, "cmp " + rax + ", 0");
    if (stmt->comp)
        emit_instr(opcode::j, predicate::ne, stmt->label);
        // emit_line(&s, "jne " + stmt->label);
    else
        emit_instr(opcode::j, predicate::e, stmt->label);
        // emit_line(&s, "je " + stmt->label);

    return;
}

template<>
void emit_statement(bound_stmt_function* stmt) {
    std::string label = function_label(stmt->function);
    auto label_name = get_label("function_end");
    auto label_end = new bound_stmt_label(label_name);
    auto gt = new bound_stmt_goto(label_name);

    emit_statement(gt);
    emit_label(label);
    // emit_line(&s, label + ":");
    emit_expression(stmt->body);
    emit_instr(opcode::ret);
    // emit_line(&s, "ret");
    emit_statement(label_end);

    return;
}

template<>
void emit_statement(bound_stmt_return* stmt) {
    emit_expression(stmt->expr);
    regenerate_label();
    emit_instr(opcode::jmp, current_label);
    // emit_line(&s, "jmp " + current_label);

    return;
}