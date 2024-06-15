#pragma once
#include "../parsing/parser.cpp"
#include "bound_statement.cpp"
#include "statement_binding.cpp"

class binder {
    std::vector<statement*> statements;

    public:
        binder(std::vector<statement*> statements) : statements (statements) {}

        std::vector<bound_statement*> bind() {
            std::vector<bound_statement*> result;

            for (const auto& stmt : statements) {
                auto res = bind_statement(stmt);
                result.push_back(res);
            }

            return result;
        }
};