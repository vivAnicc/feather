#pragma once
#include <sstream>
#include "assembly.cpp"

assembly _asm;

void emit_line(line l) {
    _asm.lines.push_back(l);
}

void emit_label(std::string l) {
    emit_line(line {label{l}});
}

void emit_comment(std::string comment) {
    emit_line(line {comment});
}

void emit_new_line() {
    emit_line(line {false});
}

void emit_instr(instruction i) {
    emit_line(line {i});
}
void emit_instr(opcode code) {
    emit_instr(instruction(code));
}
void emit_instr(opcode code, operand_lit op1) {
    emit_instr(instruction(code, op1));
}
void emit_instr(opcode code, operand_lit op1, operand_lit op2) {
    emit_instr(instruction(code, op1, op2));
}
void emit_instr(opcode code, predicate pred) {
    emit_instr(instruction(code, pred));
}
void emit_instr(opcode code, predicate pred, operand_lit op1) {
    emit_instr(instruction(code, pred, op1));
}
void emit_instr(opcode code, predicate pred, operand_lit op1, operand_lit op2) {
    emit_instr(instruction(code, pred, op1, op2));
}

void clear_reg(asm_register* r) {
    switch (r->size->size)
    {
    case 8:
        break;
    case 4:
        emit_instr(opcode::and_, r->family, -1);
        break;
    case 2:
        emit_instr(opcode::and_, r->family, 0xFFFF);
        break;
    
    default:
        break;
    }
}


// void emit_line(std::stringstream* stream, std::string line) {
//     *stream << line << std::endl;
// }

// #define RAX 0
// #define RCX 1
// #define RDX 2
// #define RBX 3
// #define RSP 4
// #define RBP 5
// #define RSI 6
// #define RDI 7
// #define R8 8
// #define R9 9
// #define R10 10
// #define R11 11
// #define R12 12
// #define R13 13
// #define R14 14
// #define R15 15

#define STACK_REGISTER RSP
#define STACK_POINTER &RSP
#define STACK_COUNTER &RBP
#define HEAP_POINTER &RBX

// std::string get_size(int size) {
//     if (size > 8)
//         return "TOO_BIG";
//     while (size != 1 && size != 2 && size != 4 && size != 8)
//         size++;
//     switch (size)
//     {
//     case 8:
//         return "qword";
//     case 4:
//         return "dword";
//     case 2:
//         return "word";
//     case 1:
//         return "byte";
    
//     default:
//         return "ERROR!";
//     }
// }

// void clear_register(std::stringstream* s, int reg, int size) {
//     std::string r = get_register(reg, 8);

//     switch (size)
//     {
//     case 8:
//         break;
//     case 4:
//         emit_line(s, "and " + r + ", " + "-1");
//         break;
//     case 2:
//         emit_line(s, "and " + r + ", " + "0xFFFF");
//         break;
    
//     default:
//         break;
//     }
// }