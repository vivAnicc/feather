#pragma once
#include <optional>
#include "statement.cpp"
#include "../token.cpp"
#include "expression.cpp"

class stmt_if : public statement {
    public:
        token kw;
        token open;
        expression* expr;
        token close;
        statement* stmt;
        std::optional<token> kw_else;
        std::optional<statement*> stmt_else;

        stmt_if(token kw, token open, expression* expr, token close, statement* stmt, std::optional<token> kw_else, std::optional<statement*> stmt_else)
            : kw (kw), open (open), expr (expr), close (close), stmt (stmt), kw_else (kw_else), stmt_else (stmt_else) {}
        
        bool has_else() {
            return kw_else.has_value() && stmt_else.has_value();
        }
        
        virtual std::vector<node*> get_children() {
            if (has_else())
                return {
                expr,
                stmt,
                stmt_else.value(),
            };
            return {
                expr,
                stmt,
            };
        }

    protected:
        virtual std::vector<token> list_tokens() {
            if (has_else())
                return {
                kw,
                open,
                close,
                kw_else.value(),
            };
            return {
                kw,
                open,
                close,
            };
        }
};