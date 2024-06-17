#pragma once
#include <optional>
#include <variant>
#include <string>
#include "token_type.cpp"
#include "token_types.cpp"
#include "symbols/type_symbol.cpp"

class token {
    public:
        token_type type;
        token_value value;
        std::string text;

    token (token_type type, std::string text, token_value value = std::nullopt) : 
        type (type), text (text), value (value) {}
};