#pragma once
#include <map>
#include <vector>
#include <optional>
#include <sstream>
#include "../parsing/binary_operator.cpp"
#include "../symbols/type_symbol.cpp"
#include "../emitting/emitting_utils.cpp"

class bound_op_binary {
    public:
        binary_operator op;
        type_symbol left;
        type_symbol right;
        type_symbol result;

        bound_op_binary(binary_operator op, type_symbol left, type_symbol right, type_symbol result)
            : op (op), left (left), right (right), result (result) {}

        bound_op_binary(binary_operator op, type_symbol type, type_symbol result)
            : bound_op_binary(op, type, type, result) {}

        bound_op_binary(binary_operator op, type_symbol type)
            : bound_op_binary(op, type, type, type) {}
        
        // left is in RCX, right is in RAX
        void emit(std::stringstream* s) {
            if (left == type_int && right == type_int && result == type_int)
                emit_ints(s);
        }

    private:
        void emit_ints(std::stringstream* s) {
            int size = result.size;

            auto rax = get_register(RAX, size);
            auto rcx = get_register(RCX, size);
            auto rdx = get_register(RDX, size);

            switch (op)
            {
            case binary_operator::add:
                emit_line(s, "add " + rax + ", " + rcx);
                break;
            case binary_operator::sub:
                emit_line(s, "sub " + rcx + ", " + rax);
                emit_line(s, "mov " + rax + ", " + rcx);
                break;
            case binary_operator::mul:
                emit_line(s, "mul " + rcx);
                break;
            case binary_operator::div:
                emit_line(s, "xor " + rdx + ", " + rdx);
                emit_line(s, "xchg " + rcx + ", " + rax);
                emit_line(s, "div " + rcx);
                break;
            case binary_operator::mod:
                emit_line(s, "xor " + rdx + ", " + rdx);
                emit_line(s, "xchg " + rcx + ", " + rax);
                emit_line(s, "div " + rcx);
                emit_line(s, "mov " + rax + ", " + rdx);
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
            bound_op_binary(binary_operator::add, type_int),
            bound_op_binary(binary_operator::add, type_string),
        }
    ),
    std::make_pair<binary_operator, std::vector<bound_op_binary>> (
        binary_operator::sub,
        {
            bound_op_binary(binary_operator::sub, type_int),
        }
    ),
    std::make_pair<binary_operator, std::vector<bound_op_binary>> (
        binary_operator::mul,
        {
            bound_op_binary(binary_operator::mul, type_int),
        }
    ),
    std::make_pair<binary_operator, std::vector<bound_op_binary>> (
        binary_operator::div,
        {
            bound_op_binary(binary_operator::div, type_int),
        }
    ),
    std::make_pair<binary_operator, std::vector<bound_op_binary>> (
        binary_operator::mod,
        {
            bound_op_binary(binary_operator::mod, type_int),
        }
    ),
};
std::map<binary_operator, std::vector<bound_op_binary>> valid_binary_operators (valid_binary_operator_list.begin(), valid_binary_operator_list.end());

std::optional<bound_op_binary> bind_binary_operator(binary_operator op, type_symbol left, type_symbol right) {
    if (valid_binary_operators.count(op) != 1)
        return std::nullopt;
    
    auto possible = valid_binary_operators[op];

    for (const auto& bound : possible) {
        if (bound.left == left && bound.right == right)
            return bound;
    }

    return std::nullopt;
}

std::optional<bound_op_binary> bind_binary_operator(binary_operator op, type_symbol left, type_symbol right, type_symbol result) {
    if (valid_binary_operators.count(op) != 1)
        return std::nullopt;
    
    auto possible = valid_binary_operators[op];

    for (const auto& bound : possible) {
        if (bound.left == left && bound.right == right && bound.result == result)
            return bound;
    }

    return std::nullopt;
}