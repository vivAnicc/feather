#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer.cpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Incorrect usage. Correct usage:" << std::endl;
        std::cerr << "feather <input.feather>" << std::endl;
    }
    if (argc != 2) {
        std::cerr << "Multiple files not yet supported." << std::endl;
    }

    std::string content;

    {
        std::stringstream stream;
        std::fstream input(argv[1], std::ios::in);
        stream << input.rdbuf();
        content = stream.str();
    }

    std::cout << content << std::endl;
    
    lexer lexer(content);
    std::vector<token> tokens = lexer.lex();

    for (const auto& token : tokens) {
        std::cout << token_to_string(token.type) << " - ";
        std::cout << token.text << std::endl;
    }

    return 0;
}