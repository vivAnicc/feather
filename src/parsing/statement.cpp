#pragma once
#include "node.cpp"

class statement : public node {
    public:
        virtual std::stringstream emit_statement() = 0; 
};