#pragma once
#include <sstream>
#include <vector>
#include <variant>
#include <optional>
#include "operand.cpp"
#include "opcode.cpp"
#include "predicate.cpp"

using operand_lit = std::variant<operand, asm_register*, int, operation, std::string>;

class instruction {
    private:
        static operand to_operand(operand_lit lit) {
            switch(lit.index()) {
                case 0:
                    return std::get<operand>(lit);
                case 1:
                    return operand(std::get<asm_register*>(lit));
                case 2:
                    return operand(std::get<int>(lit));
                case 3:
                    return operand(std::get<operation>(lit));
                case 4:
                    return operand(std::get<std::string>(lit));
            }

            return operand("ERROR!");
        }
    public:
        opcode code;
        std::optional<predicate> pred;
        std::vector<operand> operands;

        std::string to_string() {
            std::string s = opcode_to_string(code);
            if (pred.has_value())
                s += pred_to_string(pred.value());
            s += " ";

            for (size_t i = 0; i < operands.size(); i++) {
                if (i != 0)
                    s += ", ";
                s += operands[i].to_string();
            }
            
            return s;
        }

        instruction(opcode code, std::optional<predicate> pred, std::vector<operand> operands)
            : code (code), pred (pred), operands (operands) {}
        
        instruction(opcode code) : code (code), operands({}) {}
        instruction(opcode code, operand_lit op1) : code (code), operands({to_operand(op1)}) {}
        instruction(opcode code, operand_lit op1, operand_lit op2) : code (code), operands({to_operand(op1), to_operand(op2)}) {}
        instruction(opcode code, predicate pred) : code (code), pred (pred), operands({}) {}
        instruction(opcode code, predicate pred, operand_lit op1) : code (code), pred (pred), operands({to_operand(op1)}) {}
        instruction(opcode code, predicate pred, operand_lit op1, operand_lit op2) : code (code), pred (pred), operands({to_operand(op1), to_operand(op2)}) {}
};