#pragma once
#include <optional>
#include "../token.cpp"
#include "statement.cpp"
#include "expression.cpp"
#include <sstream>

class statement_return : public statement {
    public:
        token return_token;
        std::optional<expression*> expr;
        token semi;

        statement_return(token return_token, std::optional<expression*> expr, token semi) :
            return_token (return_token), expr (expr), semi (semi) {}

        virtual std::vector<node*> get_children() {
            if (expr.has_value())
                return { expr.value() };
            return {};
        }

        virtual std::string emit_statement() {
            std::stringstream stream;

            stream << expr.value()->emit_expression();
            stream << "mov rdi, rax" << std::endl;
            stream << "mov rax, 60" << std::endl;
            stream << "syscall" << std::endl;

            return stream.str();
        }
    private:
        virtual std::vector<token> list_tokens() {
            return {
                return_token,
                semi,
            };
        }
};