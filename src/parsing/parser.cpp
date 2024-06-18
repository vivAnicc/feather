#pragma once
#include <vector>
#include <optional>
#include <iostream>
#include "../token.cpp"
#include "statement.cpp"
#include "expression.cpp"
#include "term.cpp"
#include "stmt_exit.cpp"
#include "stmt_print.cpp"
#include "stmt_expression.cpp"
#include "stmt_block.cpp"
#include "stmt_var_dec.cpp"
#include "stmt_var_ass.cpp"
#include "stmt_label.cpp"
#include "stmt_goto.cpp"
#include "expr_binary.cpp"
#include "term_literal.cpp"
#include "term_paren.cpp"
#include "term_type.cpp"
#include "term_var.cpp"
#include "binary_operator.cpp"

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
                result.push_back(stmt);
            }

            return result;
        }
    
    private:
        statement* parse_statement() {
            token current = peek().value();

            switch (current.type)
            {
            case token_type::kw_exit:
                return parse_return_statement();
            case token_type::kw_print:
                return parse_print_statement();
            case token_type::kw_var:
                return parse_var_dec_statement();
            case token_type::brace_open:
                return parse_block_statement();
            case token_type::kw_label:
                return parse_label_statement();
            case token_type::kw_goto:
                return parse_goto_statement();
            case token_type::ident:
                if (peek(1).value().type == token_type::equals)
                    return parse_var_ass_statement();
            
            default:
                return parse_expression_statement();
            }
        }

        expression* parse_expression(int min_prec = 0) {
            expression* left;
            left = parse_term().value();

            while (true)
            {
                auto bin = token_to_bin_op(peek().value().type);
                int prec = 0;
                if (bin.has_value())
                    prec = bin_op_prec(bin.value());

                if (!bin.has_value() || prec < min_prec)
                    break;
                
                token op_token = next();
                int next_min_prec;
                if (bin_op_is_left_assoc(bin.value()))
                    next_min_prec = prec + 1;
                else next_min_prec = prec;
                expression* right = parse_expression(next_min_prec);
                left = new expr_binary(left, op_token, right, bin.value());
            }

            return left;
        }

        std::optional<term*> parse_term() {
            switch (peek().value().type)
            {
            case token_type::kw_bool:
            case token_type::kw_int:
            case token_type::kw_char:
                return new term_type(next());
            case token_type::kw_true:
            case token_type::kw_false:
            case token_type::num_lit:
            case token_type::char_lit:
                return new term_literal(next());
            case token_type::paren_open:
                return parse_term_paren();
            case token_type::ident:
                return new term_var(next());
                
            default:
                return std::nullopt;
            }
        }

        term_paren* parse_term_paren() {
            token open = consume(token_type::paren_open);
            auto expr = parse_expression();
            token close = consume(token_type::paren_close);
            return new term_paren(open, expr, close);
        }

        stmt_exit* parse_return_statement() {
            token return_token = consume(token_type::kw_exit);
            auto expr = parse_expression();
            token semi = consume(token_type::semi);

            return new stmt_exit(return_token, expr, semi);
        }

        stmt_print* parse_print_statement() {
            token print_token = consume(token_type::kw_print);
            token open = consume(token_type::paren_open);
            auto expr = parse_expression();
            token close = consume(token_type::paren_close);
            token semi = consume(token_type::semi);

            return new stmt_print(print_token, open, expr, close, semi);
        }

        stmt_expression* parse_expression_statement() {
            auto expr = parse_expression();
            token semi = consume(token_type::semi);
            return new stmt_expression(expr, semi);
        }

        stmt_block* parse_block_statement() {
            token open = consume(token_type::brace_open);
            std::vector<statement*> statements;

            while (!end_of_file() && peek().value().type != token_type::brace_close) {
                auto stmt = parse_statement();
                statements.push_back(stmt);
            }

            token close = consume(token_type::brace_close);

            return new stmt_block(open, statements, close);
        }

        stmt_var_dec* parse_var_dec_statement() {
            token var = consume(token_type::kw_var);
            token ident = consume(token_type::ident);
            token equals = consume(token_type::equals);
            auto expr = parse_expression();
            token semi = consume(token_type::semi);

            return new stmt_var_dec(var, ident, equals, expr, semi);
        }

        stmt_var_ass* parse_var_ass_statement() {
            token ident = consume(token_type::ident);
            token equals = consume(token_type::equals);
            auto expr = parse_expression();
            token semi = consume(token_type::semi);

            return new stmt_var_ass(ident, equals, expr, semi);
        }

        stmt_label* parse_label_statement() {
            token kw = consume(token_type::kw_label);
            token label = consume(token_type::ident);
            token semi = consume(token_type::semi);

            return new stmt_label(kw, label, semi);
        }

        stmt_goto* parse_goto_statement() {
            token gt = consume(token_type::kw_goto);
            token label = consume(token_type::ident);
            token semi = consume(token_type::semi);

            return new stmt_goto(gt, label, semi);
        }
};