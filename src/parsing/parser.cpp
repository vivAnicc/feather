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
#include "stmt_label.cpp"
#include "stmt_goto.cpp"
#include "stmt_if.cpp"
#include "stmt_function.cpp"
#include "stmt_return.cpp"
#include "expr_binary.cpp"
#include "expr_unary.cpp"
#include "term_literal.cpp"
#include "term_paren.cpp"
#include "term_type.cpp"
#include "term_var.cpp"
#include "term_statement.cpp"
#include "term_call.cpp"
#include "binary_operator.cpp"
#include "unary_operator.cpp"

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
        std::vector<statement*> parse_statements() {
            std::vector<statement*> statements;

            while (!end_of_file() && peek().value().type != token_type::brace_close) {
                auto stmt = parse_statement();
                statements.push_back(stmt);
            }

            return statements;
        }

        statement* parse_statement() {
            token current = peek().value();

            switch (current.type)
            {
            case token_type::kw_exit:
                return parse_exit_statement();
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
            case token_type::kw_if:
                return parse_if_statement();
            case token_type::kw_function:
                return parse_function_statement();
            case token_type::kw_return:
                return parse_return_statement();
            
            default:
                return parse_expression_statement();
            }
        }

        expression* parse_expression(int min_prec = 0) {
            expression* left;
            auto unary_op = token_to_unary_op(peek().value().type);
            int unary_prec = 7;
            if (unary_op.has_value() && unary_prec >= min_prec) {
                token unary = next();
                int next_prec = unary_prec;
                auto operand = parse_expression(next_prec);
                left = new expr_unary(operand, unary, unary_op.value());
            }
            else {
                left = parse_term().value();
            }

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
            case token_type::kw_void:
                return new term_type(next());
            case token_type::kw_true:
            case token_type::kw_false:
            case token_type::num_lit:
            case token_type::char_lit:
                return new term_literal(next());
            case token_type::paren_open:
                return parse_term_paren();
            case token_type::ident:
                if (peek(1).value().type == token_type::paren_open)
                    return parse_term_call();
                return new term_var(next());
            case token_type::brace_open:
                return parse_term_stmt();
                
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

        term_statement* parse_term_stmt() {
            token open = consume(token_type::brace_open);
            auto stmts = parse_statements();
            token close = consume(token_type::brace_close);

            return new term_statement(open, stmts, close);
        }

        term_call* parse_term_call() {
            token ident = consume(token_type::ident);
            token open = consume(token_type::paren_open);
            std::vector<param> v;
            while (peek().value().type != token_type::paren_close) {
                auto expr = parse_expression();
                if (peek().value().type == token_type::comma) {
                    token comma = consume(token_type::comma);
                    v.push_back(param(expr, comma));
                }
                else {
                    v.push_back(param(expr, std::nullopt));
                    break;
                }
            }
            token close = consume(token_type::paren_close);

            return new term_call(ident, open, v, close);
        }

        stmt_exit* parse_exit_statement() {
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
            auto statements = parse_statements();
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

        stmt_if* parse_if_statement() {
            token kw = consume(token_type::kw_if);
            token open = consume(token_type::paren_open);
            auto expr = parse_expression();
            token close = consume(token_type::paren_close);
            auto stmt = parse_statement();
            std::optional<token> kw_else = std::nullopt;
            std::optional<statement*> stmt_else = std::nullopt;
            if (peek().value().type == token_type::kw_else) {
                kw_else = consume(token_type::kw_else);
                stmt_else = parse_statement();
            }

            return new stmt_if(kw, open, expr, close, stmt, kw_else, stmt_else);
        }

        std::vector<node_parameter> parse_parameter() {
            std::vector<node_parameter> v;

            while (peek().value().type != token_type::paren_close) {
                token type = next();
                token ident = consume(token_type::ident);

                if (peek().value().type == token_type::comma) {
                    token comma = next();
                    v.push_back(node_parameter(type, ident, comma));
                }
                else {
                    v.push_back(node_parameter(type, ident));
                }
            }

            return v;
        }

        stmt_function* parse_function_statement() {
            token function = consume(token_type::kw_function);
            token ident = consume(token_type::ident);
            token open = consume(token_type::paren_open);
            auto params = parse_parameter();
            token close = consume(token_type::paren_close);
            auto expr = parse_expression();
            token semi = consume(token_type::semi);

            return new stmt_function(function, ident, open, params, close, expr, semi);
        }

        stmt_return* parse_return_statement() {
            token kw = consume(token_type::kw_return);
            auto expr = parse_expression();
            token semi = consume(token_type::semi);

            return new stmt_return(kw, expr, semi);
        }
};