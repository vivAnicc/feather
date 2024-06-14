#pragma once
#include "node.cpp"

class statement : public node {
    public:
        virtual std::string emit_statement() = 0; 
};