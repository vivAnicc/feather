#pragma once
#include <optional>
#include "../token.cpp"
#include "statement.cpp"
#include "expression.cpp"
#include <sstream>

class stmt_exit : public statement {
    public:
        token return_token;
        expression* expr;
        token semi;

        stmt_exit(token return_token, expression* expr, token semi) :
            return_token (return_token), expr (expr), semi (semi) {}

        virtual std::vector<node*> get_children() {
            return { expr };
        }

        virtual std::stringstream emit_statement() {
            std::stringstream stream;

            stream = expr->emit_expression();
            stream << "mov rdi, rax" << std::endl;
            stream << "mov rax, 60" << std::endl;
            stream << "syscall" << std::endl;

            return stream;
        }
    protected:
        virtual std::vector<token> list_tokens() {
            return {
                return_token,
                semi,
            };
        }
};