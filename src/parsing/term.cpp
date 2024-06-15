#pragma once
#include "expression.cpp"

class term : public expression {
    public:
        virtual std::stringstream emit_term() = 0;
        virtual std::stringstream emit_expression() {
            return emit_term();
        }
};