#pragma once
#include <variant>
#include <string>
#include <optional>

using lit_value = std::variant<int, std::string, char, bool>;
using token_value = std::optional<lit_value>;