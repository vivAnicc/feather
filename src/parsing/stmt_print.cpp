#pragma once
#include <vector>
#include <sstream>
#include "statement.cpp"
#include "../token.cpp"
#include "expression.cpp"

class stmt_print : public statement {
    public:
        token print_token;
        token open_token;
        expression* expr;
        token close_token;
        token semi;

        stmt_print(token print_token, token open_token, expression* expr, token close_token, token semi)
            : print_token (print_token), open_token (open_token), expr (expr), close_token (close_token), semi (semi) {}

        virtual std::vector<node*> get_children() {
            return { expr };
        }

        virtual std::stringstream emit_statement() {
            std::stringstream stream = expr->emit_expression();
            
            stream << "add rax, 48" << std::endl;
            stream << "push 10" << std::endl;
            stream << "push rax" << std::endl;
            stream << "mov rsi, rsp" << std::endl;
            stream << "mov rax, 1" << std::endl;
            stream << "mov rdi, 1" << std::endl;
            stream << "mov rdx, 9" << std::endl;
            stream << "syscall" << std::endl;
            stream << "add rsp, 9" << std::endl;

            return stream;
        }

    protected:
        virtual std::vector<token> list_tokens() {
            return {
                print_token,
                open_token,
                close_token,
                semi,
            };
        }
};