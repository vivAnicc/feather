#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "../token.cpp"

class lexer {
    std::string content;

    int idx = 0;

    bool end_of_file() {
        return idx >= content.length();
    }

    char current() {
        return content[idx];
    }

    char next() {
        return content[idx++];
    }

    char peek() {
        return content[idx + 1];
    }

    public:
        lexer (std::string& content) : content(content) {}

        std::vector<token> lex() {
            std::vector<token> tokens;

            auto add_token = [&](token token) 
            {
                tokens.push_back(token);
            };

            while (!end_of_file()) {

                // Skip whitespaces
                while (std::isspace(current())) {
                    next();
                }

                // token is a number
                if (std::isdigit(current())) {
                    std::stringstream num_stream;

                    do {
                        num_stream << next();
                    }
                    while (std::isdigit(current()));

                    std::string num_string = num_stream.str();
                    int num = std::stoi(num_string);

                    add_token(token(token_type::num_lit, num_string, num));
                    continue;
                }

                // check if it is a recognisable symbol
                switch (current())
                {
                case '\'':
                    add_token(lex_char());
                    continue;
                case ';':
                    add_token(token(token_type::semi, std::string{ next() }));
                    continue;
                case '(':
                    add_token(token(token_type::paren_open, std::string{ next() }));
                    continue;
                case ')':
                    add_token(token(token_type::paren_close, std::string{ next() }));
                    continue;
                case '{':
                    add_token(token(token_type::brace_open, std::string{ next() }));
                    continue;
                case '}':
                    add_token(token(token_type::brace_close, std::string{ next() }));
                    continue;
                case '+':
                    add_token(token(token_type::plus, std::string{ next() }));
                    continue;
                case '-':
                    add_token(token(token_type::dash, std::string{ next() }));
                    continue;
                case '*':
                    add_token(token(token_type::star, std::string{ next() }));
                    continue;
                case '/':
                    add_token(token(token_type::fslash, std::string{ next() }));
                    continue;
                case '%':
                    add_token(token(token_type::mod, std::string{ next() }));
                    continue;
                case ',':
                    add_token(token(token_type::comma, std::string{ next() }));
                    continue;
                case '.':
                    add_token(token(token_type::dot, std::string{ next() }));
                    continue;
                case '=':
                    if (peek() == '=')
                        add_token(token(token_type::ee, std::string { next() + "" + next() }));
                    else
                        add_token(token(token_type::equals, std::string { next() }));
                    continue;
                case '>':
                    if (peek() == '=')
                        add_token(token(token_type::ge, std::string { next() + "" + next() }));
                    else
                        add_token(token(token_type::gt, std::string { next() }));
                    continue;
                case '<':
                    if (peek() == '=')
                        add_token(token(token_type::le, std::string { next() + "" + next() }));
                    else
                        add_token(token(token_type::lt, std::string { next() }));
                    continue;
                case '!':
                    if (peek() == '=')
                        add_token(token(token_type::ne, std::string { next() + "" + next() }));
                    else
                        add_token(token(token_type::_not, std::string { next() }));
                    continue;
                case '&':
                    if (peek() == '&') {
                        add_token(token(token_type::_and, std::string { next() + "" + next() }));
                        continue;
                    }
                case '|':
                    if (peek() == '|') {
                        add_token(token(token_type::_or, std::string { next() + "" + next() }));
                        continue;
                    }
                
                default:
                    break;
                }

                // token is a word (keyword or identifier)
                if (std::isalnum(current()) || current() == '_') {
                    std::stringstream stream;

                    do {
                        stream << next();
                    }
                    while (std::isalnum(current()) || current() == '_');

                    std::string string = stream.str();

                    // Check if it is a known keyword
                    if (string == "exit") {
                        add_token(token(token_type::kw_exit, string));
                    }
                    else if (string == "print") {
                        add_token(token(token_type::kw_print, string));
                    }
                    else if (string == "label") {
                        add_token(token(token_type::kw_label, string));
                    }
                    else if (string == "goto") {
                        add_token(token(token_type::kw_goto, string));
                    }
                    else if (string == "if") {
                        add_token(token(token_type::kw_if, string));
                    }
                    else if (string == "else") {
                        add_token(token(token_type::kw_else, string));
                    }
                    else if (string == "true") {
                        add_token(token(token_type::kw_true, string, true));
                    }
                    else if (string == "false") {
                        add_token(token(token_type::kw_false, string, false));
                    }
                    else if (string == "var") {
                        add_token(token(token_type::kw_var, string));
                    }
                    else if (string == "function") {
                        add_token(token(token_type::kw_function, string));
                    }
                    else if (string == "return") {
                        add_token(token(token_type::kw_return, string));
                    }
                    else if (string == "type") {
                        add_token(token(token_type::kw_type, string));
                    }
                    else if (string == "new") {
                        add_token(token(token_type::kw_new, string));
                    }
                    else if (string == "int") {
                        add_token(token(token_type::kw_int, string, "int"));
                    }
                    else if (string == "char") {
                        add_token(token(token_type::kw_char, string, "char"));
                    }
                    else if (string == "bool") {
                        add_token(token(token_type::kw_bool, string, "bool"));
                    }
                    else if (string == "void") {
                        add_token(token(token_type::kw_void, string, "void"));
                    }
                    // not a keyword
                    else {
                        add_token(token(token_type::ident, string, string));
                    }

                    continue;
                }
                
                // Reached the end without identifing the character
                std::cerr << "Unknown character: " << next() << std::endl;
            }

            return tokens;
        }

    private:
        token lex_char() {
            std::stringstream text;

            text << next();
            auto c = next();
            text << c << next();

            return token(token_type::char_lit, text.str(), c);
        }
};