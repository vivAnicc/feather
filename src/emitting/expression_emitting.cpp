#pragma once
#include "emitting_utils.cpp"
#include "../binding/expression_binding.cpp"
#include "../symbols/function_symbol.cpp"

using operand_lit = std::variant<operand, asm_register*, int, operation, std::string>;

template<class T>
void emit_statement(T* t);
void regenerate_label();
std::string consume_label();
void emit_block_end();
void emit_block_start();

template<class T>
void emit_expression(T* t) {
    if (t == NULL) {
        std::cerr << "Null node encountered!" << std::endl;
        return;
    }
    if (auto expr = dynamic_cast<bound_expr_term*>(t)) {
        return emit_expression(expr);
    }
    else if (auto expr = dynamic_cast<bound_expr_binary*>(t)) {
        return emit_expression(expr);
    }
    else if (auto expr = dynamic_cast<bound_expr_unary*>(t)) {
        return emit_expression(expr);
    }
    else if (auto expr = dynamic_cast<bound_expr_call*>(t)) {
        return emit_expression(expr);
    }
    else if (auto expr = dynamic_cast<bound_expr_error*>(t)) {
        return emit_expression(expr);
    }
    else if (auto expr = dynamic_cast<bound_expr_type*>(t)) {
        return emit_expression(expr);
    }
    else if (auto expr = dynamic_cast<bound_expr_var*>(t)) {
        return emit_expression(expr);
    }
    else if (auto expr = dynamic_cast<bound_expr_stmt*>(t)) {
        return emit_expression(expr);
    }
    else {
        std::cerr << "Bound expression not recognized!" << std::endl;
        return;
    }
}

void emit_set_temp(bound_scope* scope, int temp, int size, operand_lit val) {
    auto ptr = get_size(size);
    emit_instr(opcode::mov, operation{ptr, &RBP, {}, {}, -(scope->var_size + temp) }, val);
    // emit_line(s, "mov " + ptr + " [rbp - " + std::to_string(scope->var_size + temp) + "], " + val);
}

void emit_get_temp(bound_scope* scope, int temp, int size, std::string val) {
    auto ptr = get_size(size);
    emit_instr(opcode::mov, val, operation{ptr, &RBP, {}, {}, -(scope->var_size + temp) });
    // emit_line(s, "mov " + val + ", " + ptr + " [rbp - " + std::to_string(scope->var_size + temp) + "]");
}

template<>
void emit_expression(bound_expr_term* expr) {
    auto rax = get_register(RAX, expr->type->size);

    if (expr->type == &type_int) {
        emit_instr(opcode::mov, rax, std::get<int>(expr->value));
        // emit_line(&s, "mov " + rax + ", " + std::to_string(std::get<int>(expr->value)));
    }
    else if (expr->type == &type_bool) {
        bool val = std::get<bool>(expr->value);
        if (val)
            emit_instr(opcode::mov, rax, 1);
            // emit_line(&s, "mov " + rax + ", 1");
        else
            emit_instr(opcode::mov, rax, 0);
            // emit_line(&s, "mov " + rax + ", 0");
    }
    else if (expr->type == &type_char) {
        int ascii = int(std::get<char>(expr->value));
        emit_instr(opcode::mov, rax, ascii);
        // emit_line(&s, "mov " + rax + ", " + std::to_string(ascii));
    }
}

template<>
void emit_expression(bound_expr_binary* expr) {
    if (expr->op.op == binary_operator::assign) {
        auto lvalue = dynamic_cast<bound_lvalue*>(expr->left);
        emit_instr(opcode::lea, &RAX, lvalue->get_address());
        // emit_line(&s, "lea rax, [" + lvalue->get_address() + "]");
    }
    else {
        emit_expression(expr->left);
    }

    // emit_line(&s, "push rax");
    emit_set_temp(expr->scope, expr->temp, 8, "rax");
    emit_expression(expr->right);
    emit_get_temp(expr->scope, expr->temp, 8, "rcx");
    // emit_line(&s, "pop rcx");
    expr->op.emit();
}

template<>
void emit_expression(bound_expr_unary* expr) {
    emit_expression(expr->operand);
    expr->op.emit();
}

void emit_print(bound_expr_call* expr) {
    if (expr->function == &function_print_num) {
            int size = expr->params[0]->type->size;
        auto r9 = get_register(R9, size);
        auto r10 = get_register(R10, size);
        auto rdx = get_register(RDX, size);
        auto rax = get_register(RAX, size);
        auto rcx = get_register(RCX, size);
        auto rsp = get_register(RSP, size);
        auto label = get_label("print_loop");

        emit_expression(expr->params[0]);

        emit_comment("print start");
        // emit_line(&s, "; print start");

        emit_instr(opcode::push, 10);
        emit_instr(opcode::mov, r9, 8);
        emit_instr(opcode::mov, r10, 10);
        // emit_line(&s, "push 10");
        // emit_line(&s, "mov " + r9 + ", 8");
        // emit_line(&s, "mov " + r10 + ", 10");

        // Check for negative
        auto check = get_label("print_neg");
        emit_instr(opcode::mov, &RCX, &RAX);
        emit_instr(opcode::cmp, rax, 0);
        emit_instr(opcode::j, predicate::ns, check);
        emit_instr(opcode::neg, rax);
        emit_label(check);
        // emit_line(&s, "mov rcx, rax");
        // emit_line(&s, "cmp " + rax + ", 0");
        // emit_line(&s, "jns " + check);
        // emit_line(&s, "neg " + rax);
        // emit_line(&s, check + ":");

        emit_label(label);
        emit_instr(opcode::xor_, rdx, rdx);
        emit_instr(opcode::div, r10);
        emit_instr(opcode::add, rdx, 48);
        clear_reg(rdx);
        emit_instr(opcode::push, &RDX);
        emit_instr(opcode::add, r9, 8);
        emit_instr(opcode::cmp, rax, 0);
        emit_instr(opcode::j, predicate::ne, label);
        // emit_line(&s, label + ":");
        // emit_line(&s, "xor " + rdx + ", " + rdx);
        // emit_line(&s, "div " + r10);
        // emit_line(&s, "add " + rdx + ", 48");
        // clear_register(&s, RDX, size);
        // emit_line(&s, "push rdx");
        // emit_line(&s, "add " + r9 + ", 8");
        // emit_line(&s, "cmp " + rax + ", 0");
        // emit_line(&s, "jne " + label);

        // Finish negative check
        auto check1 = get_label("print_sign");
        emit_instr(opcode::cmp, rcx, 0);
        emit_instr(opcode::j, predicate::ns, check1);
        emit_instr(opcode::push, 45);
        emit_instr(opcode::add, &R9, 8);
        emit_label(check1);
        // emit_line(&s, "cmp " + rcx + ", 0");
        // emit_line(&s, "jns " + check1);
        // emit_line(&s, "push 45");
        // emit_line(&s, "add r9, 8");
        // emit_line(&s, check1 + ":");

        emit_instr(opcode::mov, &RSI, &RSP);
        emit_instr(opcode::mov, &RAX, 1);
        emit_instr(opcode::mov, &RDI, 1);
        emit_instr(opcode::xor_, &RDX, &RDX);
        emit_instr(opcode::mov, rdx, r9);
        emit_instr(opcode::syscall);
        clear_reg(r9);
        emit_instr(opcode::add, &RSP, &R9);
        // emit_line(&s, "mov rsi, rsp");
        // emit_line(&s, "mov rax, 1");
        // emit_line(&s, "mov rdi, 1");
        // emit_line(&s, "xor rdx, rdx");
        // emit_line(&s, "mov " + rdx + ", " + r9);
        // emit_line(&s, "syscall");
        // clear_register(&s, R9, size);
        // emit_line(&s, "add rsp, r9");

        emit_comment("print end");
        // emit_line(&s, "; print end");

    }
    else if (expr->function == &function_print_bool) {
            int size = expr->params[0]->type->size;
        auto rax = get_register(RAX, size);
        auto r9 = get_register(R9, size);
        auto rdx = get_register(RDX, size);
        auto rsp = get_register(RSP, size);
        auto label_true = get_label("print_true");
        auto label_end = get_label("print_end");

        emit_expression(expr->params[0]);

        emit_comment("print start");
        // emit_line(&s, "; print start");

        emit_instr(opcode::push, 10);
        emit_instr(opcode::cmp, rax, 0);
        emit_instr(opcode::j, predicate::ne, label_true);
        // emit_line(&s, "push 10");
        // emit_line(&s, "cmp " + rax + ", 0");
        // emit_line(&s, "jne " + label_true);

        // writing 'false'
        emit_instr(opcode::mov, r9, 48);
        emit_instr(opcode::push, 101);
        emit_instr(opcode::push, 115);
        emit_instr(opcode::push, 108);
        emit_instr(opcode::push, 97);
        emit_instr(opcode::push, 102);
        emit_instr(opcode::jmp, label_end);
        // emit_line(&s, "mov " + r9 + ", 48");
        // emit_line(&s, "push 101");
        // emit_line(&s, "push 115");
        // emit_line(&s, "push 108");
        // emit_line(&s, "push 97");
        // emit_line(&s, "push 102");
        // emit_line(&s, "jmp " + label_end);

        // writing 'true'
        emit_label(label_true);
        emit_instr(opcode::mov, r9, 40);
        emit_instr(opcode::push, 101);
        emit_instr(opcode::push, 117);
        emit_instr(opcode::push, 114);
        emit_instr(opcode::push, 116);
        emit_instr(opcode::jmp, label_end);
        // emit_line(&s, label_true + ":");
        // emit_line(&s, "mov " + r9 + ", 40");
        // emit_line(&s, "push 101");
        // emit_line(&s, "push 117");
        // emit_line(&s, "push 114");
        // emit_line(&s, "push 116");
        // emit_line(&s, label_end + ":");
        //
        emit_instr(opcode::mov, &RSI, &RSP);
        emit_instr(opcode::mov, &RAX, 1);
        emit_instr(opcode::mov, &RDI, 1);
        emit_instr(opcode::xor_, &RDX, &RDX);
        emit_instr(opcode::mov, rdx, r9);
        emit_instr(opcode::syscall);
        clear_reg(r9);
        emit_instr(opcode::add, &RSP, &R9);
        // emit_line(&s, "mov rsi, rsp");
        // emit_line(&s, "mov rax, 1");
        // emit_line(&s, "mov rdi, 1");
        // emit_line(&s, "xor rdx, rdx");
        // emit_line(&s, "mov " + rdx + ", " + r9);
        // emit_line(&s, "syscall");
        // clear_register(&s, R9, size);
        // emit_line(&s, "add rsp, r9");

        emit_comment("print_end");
        // emit_line(&s, "; print end");

    }
    else if (expr->function == &function_print_char) {
            int size = expr->params[0]->type->size;
        auto rax = get_register(RAX, size);
        
        emit_expression(expr->params[0]);

        emit_comment("print_start");
        // emit_line(&s, "; print start");
        
        emit_instr(opcode::push, 10);
        clear_reg(rax);
        emit_instr(opcode::push, &RAX);
        emit_instr(opcode::mov, &RSI, &RSP);
        emit_instr(opcode::mov, &RAX, 1);
        emit_instr(opcode::mov, &RDI, 1);
        emit_instr(opcode::mov, &RDX, 16);
        emit_instr(opcode::syscall);
        emit_instr(opcode::add, &RSP, 16);
        // emit_line(&s, "push 10");
        // clear_register(&s, RAX, size);
        // emit_line(&s, "push rax");
        // emit_line(&s, "mov rsi, rsp");
        // emit_line(&s, "mov rax, 1");
        // emit_line(&s, "mov rdi, 1");
        // emit_line(&s, "mov rdx, 16");
        // emit_line(&s, "syscall");
        // emit_line(&s, "add rsp, 16");

        emit_comment("print end");
        // emit_line(&s, "; print end");

    }

    return void();
}

template<>
void emit_expression(bound_expr_call* expr) {
    if (expr->function == &function_print_num ||
        expr->function == &function_print_bool ||
        expr->function == &function_print_char) {
        return emit_print(expr);
    }

    // s = emit_block_start();
    int total_size = 0;
    // emit_set_temp(&s, expr->scope, expr->temp, 8, STACK_COUNTER);
    emit_instr(opcode::push, STACK_COUNTER);
    // emit_line(&s, "push " + STACK_COUNTER);

    for (const auto& param : expr->params) {
        int size = param->type->size;
        auto rax = get_register(RAX, size);
        auto ptr = get_size(size);

        emit_expression(param);
        // clear_register(&s, RAX, size);
        emit_instr(opcode::mov, operation{ ptr, &RSP, {}, {}, -(total_size + size) }, rax);
        // emit_line(&s, "mov " + ptr + " [rsp - " + std::to_string(total_size + size) + "], " + rax);
        // emit_line(&s, "push rax");

        total_size += size;
    }

    emit_instr(opcode::mov, STACK_COUNTER, STACK_POINTER);
    emit_instr(opcode::sub, STACK_POINTER, total_size);
    // emit_line(&s, "mov " + STACK_COUNTER + ", " + STACK_POINTER);
    // emit_line(&s, "sub " + STACK_POINTER + ", " + std::to_string(total_size));
    // emit_line(&s, "mov rbp, rsp");

    emit_instr(opcode::call, function_label(expr->function));
    // emit_line(&s, "call " + function_label(expr->function));
    // emit_line(&s, "add " + STACK_POINTER + ", " + std::to_string(8 * expr->params.size()));
    // emit_block_end();

    // emit_get_temp(&s, expr->scope, expr->temp, 8, STACK_COUNTER);
    emit_instr(opcode::mov, STACK_POINTER, STACK_COUNTER);
    emit_instr(opcode::pop, STACK_COUNTER);
    // emit_line(&s, "mov " + STACK_POINTER + ", " + STACK_COUNTER);
    // emit_line(&s, "pop " + STACK_COUNTER);
}

template<>
void emit_expression(bound_expr_error* expr) {
    std::cerr << "Error expression encountered! (emitting)" << std::endl;
    return void();
}

template<>
void emit_expression(bound_expr_type* expr) {
    // if it isnt a pointer, nothing to do
}

template<>
void emit_expression(bound_expr_var* expr) {
   
    int size = expr->var->type->size;
    auto rax = get_register(RAX, size);
    auto ptr = get_size(size);
    // int offset = expr->var->offset + 8;
    // int offset = expr->offset;

    emit_instr(opcode::mov, rax, expr->get_address());
    // emit_line(&s, "mov " + rax + ", " + ptr + " [" + expr->get_address() + "]");
    // clear_register(&s, RAX, size);
}

template<>
void emit_expression(bound_expr_stmt* expr) {
    regenerate_label();
    for (const auto& stmt : expr->statements) {
        emit_statement(stmt);
    }
    emit_label(consume_label());
    // emit_line(&s, consume_label() + ":");
    emit_block_end();
}