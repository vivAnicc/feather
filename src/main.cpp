#include <iostream>
#include <fstream>
#include <sstream>
#include <typeinfo>
#include <filesystem>
#include "lexing/lexer.cpp"
#include "parsing/parser.cpp"
#include "emitting/emitter.cpp"
#include "binding/binder.cpp"
#include "lowering/lowerer.cpp"

void print_node(node* node) {
    std::cout << typeid(*node).name() << std::endl;

    for (const auto& child : node->get_children()) {
        print_node(child);
    }
}

void print_node(bound_node* node) {
    std::cout << typeid(*node).name() << std::endl;

    for (const auto& child : node->get_children()) {
        print_node(child);
    }
}

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

    lexer lexer(content);
    std::vector<token> tokens = lexer.lex();

    // for (const auto& token : tokens) {
    //     std::cout << token_to_string(token.type) << " - ";
    //     std::cout << token.text << std::endl;
    // }

    parser parser(tokens);
    auto statements = parser.parse();

    // for (const auto& stmt : statements) {
    //     print_node(stmt);
    // }

    // std::cout << std::endl;

    // for (const auto& stmt : statements) {
    //     auto tokens = stmt->get_tokens();

    //     for (const auto& token : tokens) {
    //         std::cout << token_to_string(token.type) << " - ";
    //         std::cout << token.text << std::endl;
    //     }
    // }

    // std::cout << std::endl;

    binder binder(statements);
    auto bound_statement = binder.bind();

    lowerer lowerer(bound_statement);
    auto bound_statements = lowerer.lower();

    // for (const auto& stmt : bound_statements) {
    //     print_node(stmt);
    // }

    emitter emitter(bound_statements);
    std::string emitted = emitter.emit();

    // std::cout << stream.str();

    {
        std::fstream file("./out.asm", std::ios::out);
        file << emitted;
    }

    system("nasm -felf64 out.asm");
    system("ld -o out out.o");

    return 0;
}