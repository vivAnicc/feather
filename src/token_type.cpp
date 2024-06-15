#pragma once
#include <string>

const std::string token_type_name[] = {
    "kw_exit",
    "kw_print_num",
    "ident",
    "num_lit",
    "semi",
    "paren_open",
    "paren_close",
    "plus",
    "dash",
    "star",
    "fslash",
    "mod",
    "ERROR",
};

enum class token_type : int {
    kw_exit = 0,
    kw_print_num,
    ident,
    num_lit,
    semi,
    paren_open,
    paren_close,
    plus,
    dash,
    star,
    fslash,
    mod,
    error,
};

const std::string token_to_string(const token_type& type) {
    return token_type_name[int(type)];
}