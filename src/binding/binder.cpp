#pragma once
#include <optional>
#include "../parsing/parser.cpp"
#include "bound_statement.cpp"
#include "statement_binding.cpp"

class binder {
    std::vector<statement*> statements;

    public:
        binder(std::vector<statement*> statements) : statements (statements) {}

        bound_stmt_block* bind() {
            std::vector<bound_statement*> result;

            auto scope = current_scope;
            scope_enter();
            // current_scope->var_offset += 8;

            for (const auto& stmt : statements) {
                auto res = bind_statement(stmt);
                result.push_back(res);
            }

            scope_leave();
            auto block = new bound_stmt_block(result, scope);

            return block;
        }
};

std::optional<type_symbol*> string_to_type(const std::string& name) {
    if (name == "int")
        return &type_int;
    else if (name == "bool")
        return &type_bool;
    else if (name == "char")
        return &type_char;
    else if (name == "void")
        return &type_void;
    
    return std::nullopt;
}

template<class T2, class T1>
T2* try_get(T1* t) {
    if (t == NULL) {
        return nullptr;
    }
    if (auto res = dynamic_cast<T2*>(t)) {
        return res;
    }
    else {
        return nullptr;
    }
}