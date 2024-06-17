#pragma once
#include <vector>
#include <sstream>
#include "../parsing/parser.cpp"
#include "statement_emitting.cpp"
#include "emitting_utils.cpp"

class emitter {
    std::vector<bound_statement*> statements;

    public:
        emitter (std::vector<bound_statement*> statements) : statements (statements) {}
    
    std::string emit() {
        std::stringstream stream;

        stream << "global _start" << std::endl;
        stream << "_start:" << std::endl;
        
        for (const auto& stmt : statements) {
            // stream << stmt->emit_statement().str();
            stream << emit_statement(stmt).str();
        }

        return stream.str();
    }
};