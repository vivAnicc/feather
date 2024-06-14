#pragma once
#include "expression.cpp"

class term : public expression {
    public:
        virtual std::string emit_term() = 0;
        virtual std::string emit_expression() {
            return emit_term();
        }
};