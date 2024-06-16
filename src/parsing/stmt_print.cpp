#pragma once
#include <vector>
#include <sstream>
#include "statement.cpp"
#include "../token.cpp"
#include "expression.cpp"
#include "../label.cpp"

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