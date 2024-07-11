#pragma once
#include <string>

enum class instruction : int {
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
};