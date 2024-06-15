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

    if (expr->type == type_int) {
        emit_line(&s, "mov eax, " + std::to_string(std::get<int>(expr->value)));
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
        auto rsi = get_register(RSI, size);
        auto rdi = get_register(RDI, size);
        auto rsp = get_register(RSP, size);
        auto label = get_label("print_loop");

        s = emit_expression(expr->params[0]);
        emit_line(&s, "push 10");
        emit_line(&s, "mov " + r9 + ", 1");
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

    return std::stringstream();
}

template<>
std::stringstream emit_expression(bound_expr_error* expr) {
    std::cerr << "Error expression encountered!" << std::endl;
    return std::stringstream();
}