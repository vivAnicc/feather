#pragma once
#include <string>

enum class opcode : int {
    push,
    mov,
    sub,
    jmp,
    lea,
    neg,
    pop,
    ret,
    call,
    xor_,
    div,
    and_,
    add,
    cmp,
    j,
    syscall,
    cmov,
    mul,
    or_,
    imul,
    idiv,
    xchg,
};

std::string instr_str[] = {
    "push",
    "mov",
    "sub",
    "jmp",
    "lea",
    "neg",
    "pop",
    "ret",
    "call",
    "xor_",
    "div",
    "and_",
    "add",
    "cmp",
    "j",
    "syscall",
    "cmov",
    "mul",
    "or",
    "imul",
    "idiv",
    "xchg",
};

const std::string opcode_to_string(const opcode& code) {
    return instr_str[int(code)];
}