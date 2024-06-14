#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "token.cpp"

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
                case ';':
                    add_token(token(token_type::semi, std::string{ next() }));
                    continue;
                
                default:
                    break;
                }

                // token is a word (keyword or identifier)
                if (std::isalnum(current())) {
                    std::stringstream stream;

                    do {
                        stream << next();
                    }
                    while (std::isalnum(current()));

                    std::string string = stream.str();

                    // Check if it is a known keyword
                    if (string == "return") {
                        add_token(token(token_type::return_token, string));
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
};