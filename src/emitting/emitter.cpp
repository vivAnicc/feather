#pragma once
#include <vector>
#include <sstream>
#include "../parsing/parser.cpp"

class emitter {
    std::vector<statement*> statements;

    public:
        emitter (std::vector<statement*> statements) : statements (statements) {}
    
    std::string emit() {
        std::stringstream stream;
        
        for (const auto& stmt : statements) {
            stream << stmt->emit_statement();
        }

        return stream.str();
    }
};