#pragma once
#include <optional>
#include "../token_type.cpp"

enum class binary_operator : int {
    add,
    sub,
    mul,
    div,
    mod,
};

const std::optional<binary_operator> token_to_bin_op(const token_type& token) {
    switch (token)
    {
    case token_type::plus:
        return binary_operator::add;
    case token_type::dash:
        return binary_operator::sub;
    case token_type::star:
        return binary_operator::mul;
    case token_type::fslash:
        return binary_operator::div;
    case token_type::mod:
        return binary_operator::mod;
    
    default:
        return std::nullopt;
    }
}

const int bin_op_prec(const binary_operator& op) {
    switch (op)
    {
    case binary_operator::mul:
    case binary_operator::div:
    case binary_operator::mod:
        return 6;
    case binary_operator::add:
    case binary_operator::sub:
        return 5;
    
    default:
        return 0;
    }
}

const bool bin_op_is_left_assoc(const binary_operator& op) {
    switch (op)
    {
    case binary_operator::mul:
    case binary_operator::div:
    case binary_operator::mod:
    case binary_operator::add:
    case binary_operator::sub:
        return false;
    
    default:
        return false;
    }
}