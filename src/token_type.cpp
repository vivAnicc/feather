#pragma once
#include <string>

const std::string token_type_name[] = {
    "kw_exit",
    "kw_print",
    "kw_true",
    "kw_false",
    "kw_var",
    "kw_int",
    "kw_char",
    "kw_bool",

    "ident",
    "num_lit",
    "char_lit",

    "paren_open",
    "paren_close",
    "brace_open",
    "brace_close",

    "semi",
    "plus",
    "dash",
    "star",
    "fslash",
    "mod",
    "equals",
    
    "ee",
    "ne",
    "gt",
    "ge",
    "lt",
    "le",
    "or",
    "and",

    "ERROR",
};

enum class token_type : int {
    kw_exit = 0,
    kw_print,
    kw_true,
    kw_false,
    kw_var,
    kw_int,
    kw_char,
    kw_bool,

    ident,
    num_lit,
    char_lit,

    paren_open,
    paren_close,
    brace_open,
    brace_close,

    semi,
    plus,
    dash,
    star,
    fslash,
    mod,
    equals,

    ee,
    ne,
    gt,
    ge,
    lt,
    le,
    _or,
    _and,

    error,
};

const std::string token_to_string(const token_type& type) {
    return token_type_name[int(type)];
}