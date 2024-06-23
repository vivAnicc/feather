#pragma once
#include "../token_type.cpp"
#include <optional>

enum class unary_operator : int {
    ident,
    neg,
    logic_not,
};

const std::optional<unary_operator> token_to_unary_op(const token_type& token) {
    switch (token)
    {
    case token_type::plus:
        return unary_operator::ident;
    case token_type::dash:
        return unary_operator::neg;
    case token_type::_not:
        return unary_operator::logic_not;

    default:
        return std::nullopt;
    }
}