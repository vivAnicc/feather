#pragma once
#include "emitter.cpp"
#include "../binding/expression_binding.cpp"
#include "../symbols/function_symbol.cpp"

template<class T>
std::stringstream emit_expression(T* t) {
    if (auto expr = dynamic_cast<bound_expr_term*>(t)) {
        return emit_expression(expr);
    }
    else if (auto expr = dynamic_cast<bound_expr_binary*>(t)) {
        return emit_expression(expr);
    }
    else if (auto expr = dynamic_cast<bound_expr_call*>(t)) {
        return emit_expression(expr);
    }
    else if (auto expr = dynamic_cast<bound_expr_error*>(t)) {
        return emit_expression(expr);
    }
    else {
        std::cerr << "Bound expression not recognized!" << std::endl;
        return std::stringstream();
    }
}

template<>
std::stringstream emit_expression(bound_expr_term* expr) {
    std::stringstream s;

    auto rax = get_register(RAX, expr->type.size);

    if (expr->type == type_int) {
        emit_line(&s, "mov " + rax + ", " + std::to_string(std::get<int>(expr->value)));
    }
    else if (expr->type == type_bool) {
        bool val = std::get<bool>(expr->value);
        if (val)
            emit_line(&s, "mov " + rax + ", 1");
        else
            emit_line(&s, "mov " + rax + ", 0");
    }
    else if (expr->type == type_char) {
        int ascii = int(std::get<char>(expr->value));
        emit_line(&s, "mov " + rax + ", " + std::to_string(ascii));
    }

    return s;
}

template<>
std::stringstream emit_expression(bound_expr_binary* expr) {
    std::stringstream s;

    s = emit_expression(expr->left);
    emit_line(&s, "push " + get_register(RAX, expr->left->type.size));
    s << emit_expression(expr->right).str();
    emit_line(&s, "pop " + get_register(RCX, expr->right->type.size));
    expr->op.emit(&s);

    return s;
}

template<>
std::stringstream emit_expression(bound_expr_call* expr) {
    if (expr->function == function_print_num) {
        std::stringstream s;

        int size = expr->params[0]->type.size;
        auto r9 = get_register(R9, size);
        auto r10 = get_register(R10, size);
        auto rdx = get_register(RDX, size);
        auto rax = get_register(RAX, size);
        auto rsp = get_register(RSP, size);
        auto label = get_label("print_loop");

        s = emit_expression(expr->params[0]);
        emit_line(&s, "push 10");
        emit_line(&s, "mov " + r9 + ", 8");
        emit_line(&s, "mov " + r10 + ", 10");
        emit_line(&s, label + ":");
        emit_line(&s, "xor " + rdx + ", " + rdx);
        emit_line(&s, "div " + r10);
        emit_line(&s, "add " + rdx + ", 48");
        emit_line(&s, "push " + rdx);
        emit_line(&s, "add " + r9 + ", " + std::to_string(size));
        emit_line(&s, "cmp " + rax + ", 0");
        emit_line(&s, "jne " + label);
        emit_line(&s, "mov rsi, rsp");
        emit_line(&s, "mov rax, 1");
        emit_line(&s, "mov rdi, 1");
        emit_line(&s, "xor rdx, rdx");
        emit_line(&s, "mov " + rdx + ", " + r9);
        emit_line(&s, "syscall");
        emit_line(&s, "add " + rsp + ", " + r9);

        return s;
    }
    else if (expr->function == function_print_bool) {
        std::stringstream s;

        int size = expr->params[0]->type.size;
        auto rax = get_register(RAX, size);
        auto r9 = get_register(R9, size);
        auto rdx = get_register(RDX, size);
        auto rsp = get_register(RSP, size);
        auto label_true = get_label("print_true");
        auto label_end = get_label("print_end");

        s = emit_expression(expr->params[0]);
        emit_line(&s, "push 10");
        emit_line(&s, "cmp " + rax + ", 0");
        emit_line(&s, "jne " + label_true);
        // writing 'false'
        emit_line(&s, "mov " + r9 + ", 48");
        emit_line(&s, "push 101");
        emit_line(&s, "push 115");
        emit_line(&s, "push 108");
        emit_line(&s, "push 97");
        emit_line(&s, "push 102");
        emit_line(&s, "jmp " + label_end);
        // writing 'true'
        emit_line(&s, label_true + ":");
        emit_line(&s, "mov " + r9 + ", 40");
        emit_line(&s, "push 101");
        emit_line(&s, "push 117");
        emit_line(&s, "push 114");
        emit_line(&s, "push 116");
        emit_line(&s, label_end + ":");
        //
        emit_line(&s, "mov rsi, rsp");
        emit_line(&s, "mov rax, 1");
        emit_line(&s, "mov rdi, 1");
        emit_line(&s, "xor rdx, rdx");
        emit_line(&s, "mov " + rdx + ", " + r9);
        emit_line(&s, "syscall");
        emit_line(&s, "add " + rsp + ", " + r9);

        return s;
    }
    else if (expr->function == function_print_char) {
        std::stringstream s;

        int size = expr->params[0]->type.size;
        auto rax = get_register(RAX, size);
        auto eax = get_register(RAX, 2);
        
        emit_line(&s, "xor " + eax + ", " + eax);
        s = emit_expression(expr->params[0]);
        emit_line(&s, "push 10");
        emit_line(&s, "push " + eax);
        emit_line(&s, "mov rsi, rsp");
        emit_line(&s, "mov rax, 1");
        emit_line(&s, "mov rdi, 1");
        emit_line(&s, "mov rdx, " + std::to_string(10));
        emit_line(&s, "syscall");
        emit_line(&s, "add rsp, " + std::to_string(10));

        return s;
    }

    return std::stringstream();
}

template<>
std::stringstream emit_expression(bound_expr_error* expr) {
    std::cerr << "Error expression encountered!" << std::endl;
    std::stringstream stream;
    stream.clear();
    return stream;
}