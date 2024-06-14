#include <optional>
#include <variant>
#include <string>
#include "token_type.cpp"

using token_value = std::optional<std::variant<int, std::string>>;

class token {
    public:
        token_type type;
        token_value value;
        std::string text;

    token (token_type type, std::string text, token_value value = std::nullopt) : 
        type (type), text (text), value (value) {}
};