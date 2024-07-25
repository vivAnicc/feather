#pragma once
#include <map>
#include <vector>
#include <optional>
#include <sstream>
#include "../parsing/binary_operator.cpp"
#include "../symbols/type_symbol.cpp"
#include "../emitting/emitting_utils.cpp"
#include "../label.cpp"

class bound_op_binary {
    public:
        binary_operator op;
        type_symbol* left;
        type_symbol* right;
        type_symbol* result;

        bound_op_binary(binary_operator op, type_symbol* left, type_symbol* right, type_symbol* result)
            : op (op), left (left), right (right), result (result) {}

        bound_op_binary(binary_operator op, type_symbol* type, type_symbol* result)
            : bound_op_binary(op, type, type, result) {}

        bound_op_binary(binary_operator op, type_symbol* type)
            : bound_op_binary(op, type, type, type) {}
        
        // left is in RCX, right is in RAX
        void emit() {
            if (op == binary_operator::assign)
                emit_assign();
            else if (left == &type_int && right == &type_int)
                emit_ints();
            else if (left == &type_bool && right == &type_bool)
                emit_bools();
            else if (left == &type_char && right == &type_char)
                emit_chars();
        }

    private:
        void emit_assign() {
            int size = right->size;
            auto rax = get_register(RAX, size);
            auto ptr = get_size(size);

            emit_instr(opcode::mov, operation { ptr, &RCX, {}, {}, {} }, rax);
            // emit_line(s, "mov " + ptr + " [rcx], " + rax);
        }
        void emit_chars() {
            int op_size = left->size;

            auto rax = get_register(RAX, op_size);
            auto rcx = get_register(RCX, op_size);

            auto label_true = get_label("condition_true");
            auto label_end = get_label("condition_end");

            switch (op)
            {
            case binary_operator::equals:
                emit_instr(opcode::cmp, rcx, rax);
                emit_instr(opcode::j, predicate::e, label_true);
                emit_instr(opcode::mov, rax, 0);
                emit_instr(opcode::jmp, label_end);
                emit_label(label_true);
                emit_instr(opcode::mov, rax, 1);
                emit_label(label_end);
                // emit_line(s, "cmp " + rcx + ", " + rax);
                // emit_line(s, "je " + label_true);
                // emit_line(s, "mov " + rax + ", 0");
                // emit_line(s, "jmp " + label_end);
                // emit_line(s, label_true + ":");
                // emit_line(s, "mov " + rax + ", 1");
                // emit_line(s, label_end + ":");
                break;
            case binary_operator::not_equals:
                emit_instr(opcode::cmp, rcx, rax);
                emit_instr(opcode::j, predicate::ne, label_true);
                emit_instr(opcode::mov, rax, 0);
                emit_instr(opcode::jmp, label_end);
                emit_label(label_true);
                emit_instr(opcode::mov, rax, 1);
                emit_label(label_end);
                // emit_line(s, "cmp " + rcx + ", " + rax);
                // emit_line(s, "jne " + label_true);
                // emit_line(s, "mov " + rax + ", 0");
                // emit_line(s, "jmp " + label_end);
                // emit_line(s, label_true + ":");
                // emit_line(s, "mov " + rax + ", 1");
                // emit_line(s, label_end + ":");
                break;
            
            default:
                break;
            }
        }
        void emit_bools() {
            int op_size = left->size;

            auto rax = get_register(RAX, op_size);
            auto rcx = get_register(RCX, op_size);

            auto label_true = get_label("condition_true");
            auto label_end = get_label("condition_end");

            switch (op)
            {
            case binary_operator::equals:
                emit_instr(opcode::cmp, rcx, rax);
                emit_instr(opcode::j, predicate::e, label_true);
                emit_instr(opcode::mov, rax, 0);
                emit_instr(opcode::jmp, label_end);
                emit_label(label_true);
                emit_instr(opcode::mov, rax, 1);
                emit_label(label_end);
                // emit_line(s, "cmp " + rcx + ", " + rax);
                // emit_line(s, "je " + label_true);
                // emit_line(s, "mov " + rax + ", 0");
                // emit_line(s, "jmp " + label_end);
                // emit_line(s, label_true + ":");
                // emit_line(s, "mov " + rax + ", 1");
                // emit_line(s, label_end + ":");
                break;
            case binary_operator::not_equals:
                emit_instr(opcode::cmp, rcx, rax);
                emit_instr(opcode::j, predicate::ne, label_true);
                emit_instr(opcode::mov, rax, 0);
                emit_instr(opcode::jmp, label_end);
                emit_label(label_true);
                emit_instr(opcode::mov, rax, 1);
                emit_label(label_end);
                // emit_line(s, "cmp " + rcx + ", " + rax);
                // emit_line(s, "jne " + label_true);
                // emit_line(s, "mov " + rax + ", 0");
                // emit_line(s, "jmp " + label_end);
                // emit_line(s, label_true + ":");
                // emit_line(s, "mov " + rax + ", 1");
                // emit_line(s, label_end + ":");
                break;
            case binary_operator::logic_or:
                emit_instr(opcode::or_, rax, rcx);
                // emit_line(s, "or " + rax + ", " + rcx);
                break;
            case binary_operator::logic_and:
                emit_instr(opcode::and_, rax, rcx);
                // emit_line(s, "and " + rax + ", " + rcx);
                break;
            
            default:
                break;
            }
        }
        void emit_ints() {
            int op_size = left->size;

            auto rax = get_register(RAX, op_size);
            auto rcx = get_register(RCX, op_size);
            auto rdx = get_register(RDX, op_size);

            auto label_true = get_label("condition_true");
            auto label_end = get_label("condition_end");

            switch (op)
            {
            case binary_operator::add:
                emit_instr(opcode::add, rax, rcx);
                // emit_line(s, "add " + rax + ", " + rcx);
                break;
            case binary_operator::sub:
                emit_instr(opcode::sub, rcx, rax);
                emit_instr(opcode::mov, rax, rcx);
                // emit_line(s, "sub " + rcx + ", " + rax);
                // emit_line(s, "mov " + rax + ", " + rcx);
                break;
            case binary_operator::mul:
                emit_instr(opcode::imul, rcx);
                // emit_line(s, "imul " + rcx);
                break;
            case binary_operator::div:
                emit_instr(opcode::xor_, rdx, rdx);
                emit_instr(opcode::xchg, rcx, rax);
                emit_instr(opcode::idiv, rcx);
                // emit_line(s, "xor " + rdx + ", " + rdx);
                // emit_line(s, "xchg " + rcx + ", " + rax);
                // emit_line(s, "idiv " + rcx);
                break;
            case binary_operator::mod:
                emit_instr(opcode::xor_, rdx, rdx);
                emit_instr(opcode::xchg, rcx, rax);
                emit_instr(opcode::idiv, rcx);
                emit_instr(opcode::mov, rax, rdx);
                // emit_line(s, "xor " + rdx + ", " + rdx);
                // emit_line(s, "xchg " + rcx + ", " + rax);
                // emit_line(s, "idiv " + rcx);
                // emit_line(s, "mov " + rax + ", " + rdx);
                break;
            case binary_operator::equals:
                emit_instr(opcode::cmp, rcx, rax);
                emit_instr(opcode::j, predicate::e, label_true);
                emit_instr(opcode::mov, rax, 0);
                emit_instr(opcode::jmp, label_end);
                emit_label(label_true);
                emit_instr(opcode::mov, rax, 1);
                emit_label(label_end);
                // emit_line(s, "cmp " + rcx + ", " + rax);
                // emit_line(s, "je " + label_true);
                // emit_line(s, "mov " + rax + ", 0");
                // emit_line(s, "jmp " + label_end);
                // emit_line(s, label_true + ":");
                // emit_line(s, "mov " + rax + ", 1");
                // emit_line(s, label_end + ":");
                break;
            case binary_operator::not_equals:
                emit_instr(opcode::cmp, rcx, rax);
                emit_instr(opcode::j, predicate::ne, label_true);
                emit_instr(opcode::mov, rax, 0);
                emit_instr(opcode::jmp, label_end);
                emit_label(label_true);
                emit_instr(opcode::mov, rax, 1);
                emit_label(label_end);
                // emit_line(s, "cmp " + rcx + ", " + rax);
                // emit_line(s, "jne " + label_true);
                // emit_line(s, "mov " + rax + ", 0");
                // emit_line(s, "jmp " + label_end);
                // emit_line(s, label_true + ":");
                // emit_line(s, "mov " + rax + ", 1");
                // emit_line(s, label_end + ":");
                break;
            case binary_operator::greater_than:
                emit_instr(opcode::cmp, rcx, rax);
                emit_instr(opcode::j, predicate::g, label_true);
                emit_instr(opcode::mov, rax, 0);
                emit_instr(opcode::jmp, label_end);
                emit_label(label_true);
                emit_instr(opcode::mov, rax, 1);
                emit_label(label_end);
                // emit_line(s, "cmp " + rcx + ", " + rax);
                // emit_line(s, "jg " + label_true);
                // emit_line(s, "mov " + rax + ", 0");
                // emit_line(s, "jmp " + label_end);
                // emit_line(s, label_true + ":");
                // emit_line(s, "mov " + rax + ", 1");
                // emit_line(s, label_end + ":");
                break;
            case binary_operator::greater_equals:
                emit_instr(opcode::cmp, rcx, rax);
                emit_instr(opcode::j, predicate::ge, label_true);
                emit_instr(opcode::mov, rax, 0);
                emit_instr(opcode::jmp, label_end);
                emit_label(label_true);
                emit_instr(opcode::mov, rax, 1);
                emit_label(label_end);
                // emit_line(s, "cmp " + rcx + ", " + rax);
                // emit_line(s, "jge " + label_true);
                // emit_line(s, "mov " + rax + ", 0");
                // emit_line(s, "jmp " + label_end);
                // emit_line(s, label_true + ":");
                // emit_line(s, "mov " + rax + ", 1");
                // emit_line(s, label_end + ":");
                break;
            case binary_operator::less_than:
                emit_instr(opcode::cmp, rcx, rax);
                emit_instr(opcode::j, predicate::l, label_true);
                emit_instr(opcode::mov, rax, 0);
                emit_instr(opcode::jmp, label_end);
                emit_label(label_true);
                emit_instr(opcode::mov, rax, 1);
                emit_label(label_end);
                // emit_line(s, "cmp " + rcx + ", " + rax);
                // emit_line(s, "jl " + label_true);
                // emit_line(s, "mov " + rax + ", 0");
                // emit_line(s, "jmp " + label_end);
                // emit_line(s, label_true + ":");
                // emit_line(s, "mov " + rax + ", 1");
                // emit_line(s, label_end + ":");
                break;
            case binary_operator::less_equals:
                emit_instr(opcode::cmp, rcx, rax);
                emit_instr(opcode::j, predicate::le, label_true);
                emit_instr(opcode::mov, rax, 0);
                emit_instr(opcode::jmp, label_end);
                emit_label(label_true);
                emit_instr(opcode::mov, rax, 1);
                emit_label(label_end);
                // emit_line(s, "cmp " + rcx + ", " + rax);
                // emit_line(s, "jle " + label_true);
                // emit_line(s, "mov " + rax + ", 0");
                // emit_line(s, "jmp " + label_end);
                // emit_line(s, label_true + ":");
                // emit_line(s, "mov " + rax + ", 1");
                // emit_line(s, label_end + ":");
                break;
            
            default:
                break;
            }
        }
};

auto valid_binary_operator_list = {
    std::make_pair<binary_operator, std::vector<bound_op_binary>> (
        binary_operator::add,
        {
            bound_op_binary(binary_operator::add, &type_int),
            bound_op_binary(binary_operator::add, &type_string),
        }
    ),
    std::make_pair<binary_operator, std::vector<bound_op_binary>> (
        binary_operator::sub,
        {
            bound_op_binary(binary_operator::sub, &type_int),
        }
    ),
    std::make_pair<binary_operator, std::vector<bound_op_binary>> (
        binary_operator::mul,
        {
            bound_op_binary(binary_operator::mul, &type_int),
        }
    ),
    std::make_pair<binary_operator, std::vector<bound_op_binary>> (
        binary_operator::div,
        {
            bound_op_binary(binary_operator::div, &type_int),
        }
    ),
    std::make_pair<binary_operator, std::vector<bound_op_binary>> (
        binary_operator::mod,
        {
            bound_op_binary(binary_operator::mod, &type_int),
        }
    ),
    std::make_pair<binary_operator, std::vector<bound_op_binary>> (
        binary_operator::logic_and,
        {
            bound_op_binary(binary_operator::logic_and, &type_bool),
        }
    ),
    std::make_pair<binary_operator, std::vector<bound_op_binary>> (
        binary_operator::logic_or,
        {
            bound_op_binary(binary_operator::logic_or, &type_bool),
        }
    ),
    std::make_pair<binary_operator, std::vector<bound_op_binary>> (
        binary_operator::greater_than,
        {
            bound_op_binary(binary_operator::greater_than, &type_int, &type_bool),
        }
    ),
    std::make_pair<binary_operator, std::vector<bound_op_binary>> (
        binary_operator::greater_equals,
        {
            bound_op_binary(binary_operator::greater_equals, &type_int, &type_bool),
        }
    ),
    std::make_pair<binary_operator, std::vector<bound_op_binary>> (
        binary_operator::less_than,
        {
            bound_op_binary(binary_operator::less_than, &type_int, &type_bool),
        }
    ),
    std::make_pair<binary_operator, std::vector<bound_op_binary>> (
        binary_operator::less_equals,
        {
            bound_op_binary(binary_operator::less_equals, &type_int, &type_bool),
        }
    ),
};
std::map<binary_operator, std::vector<bound_op_binary>> valid_binary_operators (valid_binary_operator_list.begin(), valid_binary_operator_list.end());

std::optional<bound_op_binary> bind_binary_operator(binary_operator op, type_symbol* left, type_symbol* right) {
    if (op == binary_operator::assign || op == binary_operator::equals || op == binary_operator::not_equals) {
        if (left == right)
            return bound_op_binary(op, left);
    }

    if (valid_binary_operators.count(op) != 1)
        return std::nullopt;
    
    auto possible = valid_binary_operators[op];

    for (const auto& bound : possible) {
        if (bound.left == left && bound.right == right)
            return bound;
    }

    return std::nullopt;
}

std::optional<bound_op_binary> bind_binary_operator(binary_operator op, type_symbol* left, type_symbol* right, type_symbol* result) {
    if (op == binary_operator::assign) {
        if (left == right && left == result)
            return bound_op_binary(op, left);
    }
    if (op == binary_operator::equals || op == binary_operator::not_equals) {
        if (left == right && result == &type_bool)
            return bound_op_binary(op, left, result);
    }

    if (valid_binary_operators.count(op) != 1)
        return std::nullopt;
    
    auto possible = valid_binary_operators[op];

    for (const auto& bound : possible) {
        if (bound.left == left && bound.right == right && bound.result == result)
            return bound;
    }

    return std::nullopt;
}