#pragma once
#include <string>

const std::string token_type_name[] = {
    "kw_exit",
    "kw_print",
    "kw_true",
    "kw_false",
    "kw_var",
    "kw_function",
    "kw_int",
    "kw_char",
    "kw_bool",
    "kw_void"
    "kw_label",
    "kw_goto",
    "kw_if",
    "kw_else",
    "kw_return",
    "kw_type",
    "kw_new",

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
    "comma",
    "dot",
    
    "ee",
    "ne",
    "gt",
    "ge",
    "lt",
    "le",
    "or",
    "and",
    "not",

    "ERROR",
};

enum class token_type : int {
    kw_exit = 0,
    kw_print,
    kw_true,
    kw_false,
    kw_var,
    kw_function,
    kw_int,
    kw_char,
    kw_bool,
    kw_void,
    kw_label,
    kw_goto,
    kw_if,
    kw_else,
    kw_return,
    kw_type,
    kw_new,

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
    comma,
    dot,

    ee,
    ne,
    gt,
    ge,
    lt,
    le,
    _or,
    _and,
    _not,

    error,
};

const std::string token_to_string(const token_type& type) {
    return token_type_name[int(type)];
}