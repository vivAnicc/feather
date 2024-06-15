#pragma once
#include <string>

const std::string token_type_name[] = {
    "kw_return",
    "kw_print",
    "ident",
    "num_lit",
    "semi",
    "paren_open",
    "paren_close",
    "ERROR",
};

enum class token_type : int {
    kw_return = 0,
    kw_print,
    ident,
    num_lit,
    semi,
    paren_open,
    paren_close,
    error,
};

const std::string token_to_string(const token_type& type) {
    return token_type_name[int(type)];
}