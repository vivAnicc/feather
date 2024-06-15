#pragma once
#include "../parsing/parser.cpp"

class binder {
    std::vector<statement*> statements;

    public:
        binder(std::vector<statement*> statements) : statements (statements) {}

        
};