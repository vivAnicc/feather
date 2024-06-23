#pragma once
#include <optional>
#include "../token_type.cpp"

enum class binary_operator : int {
    add,
    sub,
    mul,
    div,
    mod,

    equals,
    not_equals,
    greater_than,
    greater_equals,
    less_than,
    less_equals,
    
    logic_and,
    logic_or,

    assign,
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
    case token_type::ee:
        return binary_operator::equals;
    case token_type::ne:
        return binary_operator::not_equals;
    case token_type::gt:
        return binary_operator::greater_than;
    case token_type::ge:
        return binary_operator::greater_equals;
    case token_type::lt:
        return binary_operator::less_than;
    case token_type::le:
        return binary_operator::less_equals;
    case token_type::_and:
        return binary_operator::logic_and;
    case token_type::_or:
        return binary_operator::logic_or;
    case token_type::equals:
        return binary_operator::assign;
    
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
    case binary_operator::equals:
    case binary_operator::not_equals:
    case binary_operator::greater_than:
    case binary_operator::greater_equals:
    case binary_operator::less_than:
    case binary_operator::less_equals:
        return 4;
    case binary_operator::logic_and:
        return 3;
    case binary_operator::logic_or:
        return 2;
    case binary_operator::assign:
        return 1;
    
    default:
        return 0;
    }
}

const bool bin_op_is_left_assoc(const binary_operator& op) {
    switch (op)
    {
    case binary_operator::assign:
        return false;
        
    default:
        return true;
    }
}