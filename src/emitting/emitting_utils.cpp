#pragma once
#include <sstream>

void emit_line(std::stringstream* stream, std::string line) {
    *stream << line << std::endl;
}

#define RAX 0
#define RCX 1
#define RDX 2
#define RBX 3
#define RSP 4
#define RBP 5
#define RSI 6
#define RDI 7
#define R8 8
#define R9 9
#define R10 10
#define R11 11
#define R12 12
#define R13 13
#define R14 14
#define R15 15

#define STACK_REGISTER RSP
#define STACK_POINTER std::string("rsp")
#define STACK_COUNTER std::string("rbp")

std::string get_register(int num, int size) {
    switch (num)
    {
    case 0:
        switch (size)
        {
        case 8:
            return "rax";
        case 4:
            return "eax";
        case 2:
            return "ax";
        case 1:
            return "al";
        }
        break;
    case 1:
        switch (size)
        {
        case 8:
            return "rcx";
        case 4:
            return "ecx";
        case 2:
            return "cx";
        case 1:
            return "cl";
        }
        break;
    case 2:
        switch (size)
        {
        case 8:
            return "rdx";
        case 4:
            return "edx";
        case 2:
            return "dx";
        case 1:
            return "dl";
        }
        break;
    case 3:
        switch (size)
        {
        case 8:
            return "rbx";
        case 4:
            return "ebx";
        case 2:
            return "bx";
        case 1:
            return "bl";
        }
        break;
    case 4:
        switch (size)
        {
        case 8:
            return "rsp";
        case 4:
            return "esp";
        case 2:
            return "sp";
        case 1:
            return "spl";
        }
        break;
    case 5:
        switch (size)
        {
        case 8:
            return "rbp";
        case 4:
            return "ebp";
        case 2:
            return "bp";
        case 1:
            return "bpl";
        }
        break;
    case 6:
        switch (size)
        {
        case 8:
            return "rsi";
        case 4:
            return "esi";
        case 2:
            return "si";
        case 1:
            return "sil";
        }
        break;
    case 7:
        switch (size)
        {
        case 8:
            return "rdi";
        case 4:
            return "edi";
        case 2:
            return "di";
        case 1:
            return "dil";
        }
        break;
    case 8:
        switch (size)
        {
        case 8:
            return "r8";
        case 4:
            return "r8d";
        case 2:
            return "r8w";
        case 1:
            return "r8b";
        }
        break;
    case 9:
        switch (size)
        {
        case 8:
            return "r9";
        case 4:
            return "r9d";
        case 2:
            return "r9w";
        case 1:
            return "r9b";
        }
        break;
    case 10:
        switch (size)
        {
        case 8:
            return "r10";
        case 4:
            return "r10d";
        case 2:
            return "r10w";
        case 1:
            return "r10b";
        }
        break;
    case 11:
        switch (size)
        {
        case 8:
            return "r11";
        case 4:
            return "r11d";
        case 2:
            return "r11w";
        case 1:
            return "r11b";
        }
        break;
    case 12:
        switch (size)
        {
        case 8:
            return "r12";
        case 4:
            return "r12d";
        case 2:
            return "r12w";
        case 1:
            return "r12b";
        }
        break;
    case 13:
        switch (size)
        {
        case 8:
            return "r13";
        case 4:
            return "r13d";
        case 2:
            return "r13w";
        case 1:
            return "r13b";
        }
        break;
    case 14:
        switch (size)
        {
        case 8:
            return "r14";
        case 4:
            return "r14d";
        case 2:
            return "r14w";
        case 1:
            return "r14b";
        }
        break;
    case 15:
        switch (size)
        {
        case 8:
            return "r15";
        case 4:
            return "r15d";
        case 2:
            return "r15w";
        case 1:
            return "r15b";
        }
        break;
    }

    return "INVALID";
}

std::string get_size(int size) {
    switch (size)
    {
    case 8:
        return "qword";
    case 4:
        return "dword";
    case 2:
        return "word";
    case 1:
        return "byte";
    
    default:
        return "ERROR!";
    }
}

void clear_register(std::stringstream* s, int reg, int size) {
    std::string r = get_register(reg, 8);

    switch (size)
    {
    case 8:
        break;
    case 4:
        emit_line(s, "and " + r + ", " + "-1");
        break;
    case 2:
        emit_line(s, "and " + r + ", " + "0xFFFF");
        break;
    
    default:
        break;
    }
}