#pragma once
#include "node.cpp"

class expression : public node {
    public:
        virtual std::string emit_expression() = 0;
};