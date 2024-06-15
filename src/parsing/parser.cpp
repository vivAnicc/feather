#pragma once
#include <vector>
#include <optional>
#include <iostream>
#include "../token.cpp"
#include "statement.cpp"
#include "expression.cpp"
#include "term.cpp"
#include "stmt_return.cpp"
#include "stmt_print.cpp"
#include "term_literal.cpp"

class parser {
    std::vector<token> tokens;
    int idx = 0;

    bool end_of_file() {
        return idx >= tokens.size();
    }

    std::optional<token> peek(int offset = 0) {
        if (idx + offset >= tokens.size())
            return std::nullopt;
        return tokens[idx + offset];
    }

    token next() {
        return tokens[idx++];
    }

    token consume(const token_type& type) {
        if (end_of_file()) {
            std::cerr << "Unexpected end of file. Expected: ";
            std::cerr << token_to_string(type) << std::endl;

            return token(token_type::error, "");
        }

        if (peek().value().type == type) {
            return next();
        }
        
        std::cerr << "Unexpected token: " << token_to_string(peek().value().type);
        std::cerr << ". Expected token: " << token_to_string(type);

        return token(token_type::error, "");
    }

    public:
        parser(std::vector<token> tokens) : tokens (tokens) {}

        std::vector<statement*> parse() {
            std::vector<statement*> result;

            while (!end_of_file()) {
                auto stmt = parse_statement();
                if (stmt.has_value())
                    result.push_back(stmt.value());
            }

            return result;
        }
    
    private:
        std::optional<statement*> parse_statement() {
            token current = peek().value();

            switch (current.type)
            {
            case token_type::kw_return:
                return parse_return_statement();
            case token_type::kw_print:
                return parse_print_statement();
            
            default:
                std::cerr << "Unable to parse statement" << std::endl;
                next();
                return std::nullopt;
            }
        }

        std::optional<expression*> parse_expression() {
            return parse_term();
        }

        std::optional<term*> parse_term() {
            switch (peek().value().type)
            {
            case token_type::num_lit:
                return new term_literal(next());
            
            default:
                return std::nullopt;
            }
        }

        stmt_return* parse_return_statement() {
            token return_token = consume(token_type::kw_return);
            auto expr = parse_expression();
            token semi = consume(token_type::semi);

            return new stmt_return(return_token, expr, semi);
        }

        stmt_print* parse_print_statement() {
            token print_token = consume(token_type::kw_print);
            token open = consume(token_type::paren_open);
            auto expr = parse_expression().value();
            token close = consume(token_type::paren_close);
            token semi = consume(token_type::semi);

            return new stmt_print(print_token, open, expr, close, semi);
        }
};