#pragma once
#include <string>

class asm_size {
    public:
        std::string name;
        int size;
};

asm_size qword = asm_size{ "qword", 8 };
asm_size dword = asm_size{ "dword", 4 };
asm_size word = asm_size{ "word", 2 };
asm_size byte = asm_size{ "byte", 1 };

asm_size* big_size(int s) {
    return new asm_size{ "TOO_BIG", s };
}

class asm_register {
    public:
        std::string name;
        asm_size* size;
        asm_register* family;
        int num;
};

asm_register RAX = asm_register{ "rax", &qword, &RAX, 0 };
asm_register RCX = asm_register{ "rcx", &qword, &RCX, 1 };
asm_register RDX = asm_register{ "rdx", &qword, &RDX, 2 };
asm_register RBX = asm_register{ "rbx", &qword, &RBX, 3 };
asm_register RSP = asm_register{ "rsp", &qword, &RSP, 4 };
asm_register RBP = asm_register{ "rbp", &qword, &RBP, 5 };
asm_register RSI = asm_register{ "rsi", &qword, &RSI, 6 };
asm_register RDI = asm_register{ "rdi", &qword, &RDI, 7 };
asm_register R8 = asm_register{ "r8", &qword, &R8, 8 };
asm_register R9 = asm_register{ "r9", &qword, &R9, 9 };
asm_register R10 = asm_register{ "r10", &qword, &R10, 10 };
asm_register R11 = asm_register{ "r11", &qword, &R11, 11 };
asm_register R12 = asm_register{ "r12", &qword, &R12, 12 };
asm_register R13 = asm_register{ "r13", &qword, &R13, 13 };
asm_register R14 = asm_register{ "r14", &qword, &R14, 14 };
asm_register R15 = asm_register{ "r15", &qword, &R15, 15 };

asm_register EAX = asm_register{ "eax", &dword, &RAX, 0 };
asm_register ECX = asm_register{ "ecx", &dword, &RCX, 1 };
asm_register EDX = asm_register{ "edx", &dword, &RDX, 2 };
asm_register EBX = asm_register{ "ebx", &dword, &RBX, 3 };
asm_register ESP = asm_register{ "esp", &dword, &RSP, 4 };
asm_register EBP = asm_register{ "ebp", &dword, &RBP, 5 };
asm_register ESI = asm_register{ "esi", &dword, &RSI, 6 };
asm_register EDI = asm_register{ "edi", &dword, &RDI, 7 };
asm_register R8D = asm_register{ "r8d", &dword, &R8, 8 };
asm_register R9D = asm_register{ "r9d", &dword, &R9, 9 };
asm_register R10D = asm_register{ "r10d", &dword, &R10, 10 };
asm_register R11D = asm_register{ "r11d", &dword, &R11, 11 };
asm_register R12D = asm_register{ "r12d", &dword, &R12, 12 };
asm_register R13D = asm_register{ "r13d", &dword, &R13, 13 };
asm_register R14D = asm_register{ "r14d", &dword, &R14, 14 };
asm_register R15D = asm_register{ "r15d", &dword, &R15, 15 };

asm_register AX = asm_register{ "ax", &word, &RAX, 0 };
asm_register CX = asm_register{ "cx", &word, &RCX, 1 };
asm_register DX = asm_register{ "dx", &word, &RDX, 2 };
asm_register BX = asm_register{ "bx", &word, &RBX, 3 };
asm_register SP = asm_register{ "sp", &word, &RSP, 4 };
asm_register BP = asm_register{ "bp", &word, &RBP, 5 };
asm_register SI = asm_register{ "si", &word, &RSI, 6 };
asm_register DI = asm_register{ "di", &word, &RDI, 7 };
asm_register R8W = asm_register{ "r8w", &word, &R8, 8 };
asm_register R9W = asm_register{ "r9w", &word, &R9, 9 };
asm_register R10W = asm_register{ "r10w", &word, &R10, 10 };
asm_register R11W = asm_register{ "r11w", &word, &R11, 11 };
asm_register R12W = asm_register{ "r12w", &word, &R12, 12 };
asm_register R13W = asm_register{ "r13w", &word, &R13, 13 };
asm_register R14W = asm_register{ "r14w", &word, &R14, 14 };
asm_register R15W = asm_register{ "r15w", &word, &R15, 15 };

asm_register AL = asm_register{ "al", &byte, &RAX, 0 };
asm_register CL = asm_register{ "cl", &byte, &RCX, 1 };
asm_register DL = asm_register{ "dl", &byte, &RDX, 2 };
asm_register BL = asm_register{ "bl", &byte, &RBX, 3 };
asm_register SPL = asm_register{ "spl", &byte, &RSP, 4 };
asm_register BPL = asm_register{ "bpl", &byte, &RBP, 5 };
asm_register SIL = asm_register{ "sil", &byte, &RSI, 6 };
asm_register DIL = asm_register{ "dil", &byte, &RDI, 7 };
asm_register R8B = asm_register{ "r8b", &byte, &R8, 8 };
asm_register R9B = asm_register{ "r9b", &byte, &R9, 9 };
asm_register R10B = asm_register{ "r10b", &byte, &R10, 10 };
asm_register R11B = asm_register{ "r11b", &byte, &R11, 11 };
asm_register R12B = asm_register{ "r12b", &byte, &R12, 12 };
asm_register R13B = asm_register{ "r13b", &byte, &R13, 13 };
asm_register R14B = asm_register{ "r14b", &byte, &R14, 14 };
asm_register R15B = asm_register{ "r15b", &byte, &R15, 15 };

asm_register* invalid_reg(std::string msg, int size) {
    return new asm_register { msg, big_size(size), nullptr, -1 };
}

asm_register* get_register(asm_register r, int size) {
    if (size > 8)
        return invalid_reg("TOO_BIG", size);
    while (size != 1 && size != 2 && size != 4 && size != 8)
        size++;
    switch (r.family->num)
    {
    case 0:
        switch (size)
        {
        case 8:
            return &RAX;
        case 4:
            return &EAX;
        case 2:
            return &AX;
        case 1:
            return &AL;
        }
        break;
    case 1:
        switch (size)
        {
        case 8:
            return &RCX;
        case 4:
            return &ECX;
        case 2:
            return &CX;
        case 1:
            return &CL;
        }
        break;
    case 2:
        switch (size)
        {
        case 8:
            return &RDX;
        case 4:
            return &EDX;
        case 2:
            return &DX;
        case 1:
            return &DL;
        }
        break;
    case 3:
        switch (size)
        {
        case 8:
            return &RBX;
        case 4:
            return &EBX;
        case 2:
            return &BX;
        case 1:
            return &BL;
        }
        break;
    case 4:
        switch (size)
        {
        case 8:
            return &RSP;
        case 4:
            return &ESP;
        case 2:
            return &SP;
        case 1:
            return &SPL;
        }
        break;
    case 5:
        switch (size)
        {
        case 8:
            return &RBP;
        case 4:
            return &EBP;
        case 2:
            return &BP;
        case 1:
            return &BPL;
        }
        break;
    case 6:
        switch (size)
        {
        case 8:
            return &RSI;
        case 4:
            return &ESI;
        case 2:
            return &SI;
        case 1:
            return &SIL;
        }
        break;
    case 7:
        switch (size)
        {
        case 8:
            return &RDI;
        case 4:
            return &EDI;
        case 2:
            return &DI;
        case 1:
            return &DIL;
        }
        break;
    case 8:
        switch (size)
        {
        case 8:
            return &R8;
        case 4:
            return &R8D;
        case 2:
            return &R8W;
        case 1:
            return &R8B;
        }
        break;
    case 9:
        switch (size)
        {
        case 8:
            return &R9;
        case 4:
            return &R9D;
        case 2:
            return &R9W;
        case 1:
            return &R9B;
        }
        break;
    case 10:
        switch (size)
        {
        case 8:
            return &R10;
        case 4:
            return &R10D;
        case 2:
            return &R10W;
        case 1:
            return &R10B;
        }
        break;
    case 11:
        switch (size)
        {
        case 8:
            return &R11;
        case 4:
            return &R11D;
        case 2:
            return &R11W;
        case 1:
            return &R11B;
        }
        break;
    case 12:
        switch (size)
        {
        case 8:
            return &R12;
        case 4:
            return &R12D;
        case 2:
            return &R12W;
        case 1:
            return &R12B;
        }
        break;
    case 13:
        switch (size)
        {
        case 8:
            return &R13;
        case 4:
            return &R13D;
        case 2:
            return &R13W;
        case 1:
            return &R13B;
        }
        break;
    case 14:
        switch (size)
        {
        case 8:
            return &R14;
        case 4:
            return &R14D;
        case 2:
            return &R14W;
        case 1:
            return &R14B;
        }
        break;
    case 15:
        switch (size)
        {
        case 8:
            return &R15;
        case 4:
            return &R15D;
        case 2:
            return &R15W;
        case 1:
            return &R15B;
        }
        break;
    default:
        return invalid_reg("NOT_A_REGISTER", size);
    }

    return invalid_reg("ERROR!", size);
}

asm_size* get_size(int size) {
    if (size > 8)
        return big_size(size);
    while (size != 1 && size != 2 && size != 4 && size != 8)
        size++;
    switch (size)
    {
    case 8:
        return &qword;
    case 4:
        return &dword;
    case 2:
        return &word;
    case 1:
        return &byte;
    
    default:
        return big_size(size);
    }
}