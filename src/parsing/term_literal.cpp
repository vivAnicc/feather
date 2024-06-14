#pragma once
#include <vector>
#include <sstream>
#include <variant>
#include "term.cpp"
#include "../token.cpp"

class term_literal : public term {
    public:
        token lit;
        lit_value value;

        term_literal(token lit) : lit (lit), value (lit.value.value()) {}

        virtual std::vector<node*> get_children() {
            return {};
        }

        virtual std::string emit_term() {
            std::stringstream stream;

            stream << "mov rax, ";
            switch (value.index())
            {
            case 0:
                stream << std::get<int>(value);
                break;
            case 1:
                stream << std::get<std::string>(value);
                break;
            }

            stream << std::endl;

            return stream.str();
        }
    private:
        virtual std::vector<token> list_tokens() {
            return { lit };
        }
};