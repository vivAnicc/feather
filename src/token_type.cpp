#pragma once

const std::string token_type_name[] = {
    "keyword_return",
    "ident",
    "num_lit",
    "semi",
    "ERROR",
};

enum class token_type : int {
    keyword_return = 0,
    ident,
    num_lit,
    semi,
    error,
};

const std::string token_to_string(const token_type& type) {
    return token_type_name[int(type)];
}