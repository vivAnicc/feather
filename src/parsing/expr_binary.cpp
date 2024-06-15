#pragma once
#include <sstream>
#include "expression.cpp"
#include "../token.cpp"
#include "binary_operator.cpp"

class expr_binary : public expression {
    public:
        expression* left;
        token op_token;
        expression* right;
        binary_operator op;

        expr_binary(expression* left, token op_token, expression* right, binary_operator op)
            : left (left), op_token (op_token), right (right), op (op) {}

        virtual std::vector<node*> get_children() {
            return {
                left, right
            };
        }

        virtual std::stringstream emit_expression() {
            std::stringstream stream;

            stream = left->emit_expression();
            stream << "push rax" << std::endl;
            stream << right->emit_expression().str() << std::endl;
            stream << "pop rcx" << std::endl;

            switch (op)
            {
            case binary_operator::add:
                stream << "add rax, rcx" << std::endl;
                break;
            case binary_operator::sub:
                stream << "sub rcx, rax" << std::endl;
                stream << "mov rax, rcx" << std::endl;
                break;
            case binary_operator::mul:
                stream << "mul rcx" << std::endl;
                break;
            case binary_operator::div:
                stream << "xor rdx, rdx" << std::endl;
                stream << "xchg rcx, rax" << std::endl;
                stream << "div rcx" << std::endl;
                break;
            case binary_operator::mod:
                stream << "xor rdx, rdx" << std::endl;
                stream << "xchg rcx, rax" << std::endl;
                stream << "div rcx" << std::endl;
                stream << "mov rax, rdx" << std::endl;
                break;
            
            default:
                break;
            }

            return stream;
        }

    protected:
        virtual std::vector<token> list_tokens() {
            return { op_token };
        }
};