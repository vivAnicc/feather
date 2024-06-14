const std::string token_type_name[] = {
    "return_token",
    "ident",
    "num_lit",
    "semi",
};

enum class token_type : int {
    return_token = 0,
    ident,
    num_lit,
    semi,
};

const std::string token_to_string(const token_type& type) {
    return token_type_name[int(type)];
}