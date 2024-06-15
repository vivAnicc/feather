#pragma once
#include "node.cpp"

class expression : public node {
    public:
        virtual std::stringstream emit_expression() = 0;
};