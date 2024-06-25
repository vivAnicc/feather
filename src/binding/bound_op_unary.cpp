#pragma once
#include <map>
#include <vector>
#include <optional>
#include <sstream>
#include "../parsing/unary_operator.cpp"
#include "../symbols/type_symbol.cpp"
#include "../emitting/emitting_utils.cpp"
#include "../label.cpp"

class bound_op_unary {
    public:
        unary_operator op;
        type_symbol* operand;
        type_symbol* result;

        bound_op_unary(unary_operator op, type_symbol* operand, type_symbol* result)
            : op (op), operand (operand), result (result) {}

        bound_op_unary(unary_operator op, type_symbol* operand)
            : op (op), operand (operand), result (operand) {}

        void emit(std::stringstream* s) {
            int size = operand->size;
            auto rax = get_register(RAX, size);
            auto rcx = get_register(RCX, size);

            switch (op)
            {
            case unary_operator::neg:
                emit_line(s, "neg " + rax);
                break;
            case unary_operator::logic_not:
                emit_line(s, "cmp " + rax + ", 0");
                emit_line(s, "mov " + rcx + ", 1");
                emit_line(s, "cmovz " + rax + ", " + rcx);
                emit_line(s, "mov " + rcx + ", 0");
                emit_line(s, "cmovnz " + rax + ", " + rcx);
                break;
            
            default:
                break;
            }
        }
};

auto valid_unary_operator_list = {
    std::make_pair<unary_operator, std::vector<bound_op_unary>> (
        unary_operator::ident,
        {
            bound_op_unary(unary_operator::ident, &type_int),
        }
    ),
    std::make_pair<unary_operator, std::vector<bound_op_unary>> (
        unary_operator::neg,
        {
            bound_op_unary(unary_operator::neg, &type_int),
        }
    ),
    std::make_pair<unary_operator, std::vector<bound_op_unary>> (
        unary_operator::logic_not,
        {
            bound_op_unary(unary_operator::logic_not, &type_bool),
        }
    ),
};
std::map<unary_operator, std::vector<bound_op_unary>> valid_unary_operators (valid_unary_operator_list.begin(), valid_unary_operator_list.end());

std::optional<bound_op_unary> bind_unary_operator(unary_operator op, type_symbol* operand) {
    if (valid_unary_operators.count(op) != 1)
        return std::nullopt;
    
    auto possible = valid_unary_operators[op];

    for (const auto& bound : possible) {
        if (bound.operand == operand)
            return bound;
    }

    return std::nullopt;
}

std::optional<bound_op_unary> bind_unary_operator(unary_operator op, type_symbol* operand, type_symbol* result) {
    if (valid_unary_operators.count(op) != 1)
        return std::nullopt;
    
    auto possible = valid_unary_operators[op];

    for (const auto& bound : possible) {
        if (bound.operand == operand && bound.result == result)
            return bound;
    }

    return std::nullopt;
}