global _start
_start:
push rbp
mov rbp, rsp
push rbp
mov rbp, rsp
mov ax, 0
and rax, 0xFFFF
push rax
mov ax, 1
and rax, 0xFFFF
mov [rsp - 0], rax
mov rax, [rbp - 0]
and rax, 0xFFFF
; print start
push 10
cmp ax, 0
jne print_true0
mov r9w, 48
push 101
push 115
push 108
push 97
push 102
jmp print_end1
print_true0:
mov r9w, 40
push 101
push 117
push 114
push 116
print_end1:
mov rsi, rsp
mov rax, 1
mov rdi, 1
xor rdx, rdx
mov dx, r9w
syscall
and r9, 0xFFFF
add rsp, r9
; print end
mov rsp, rbp
pop rbp
mov eax, 0
mov edi, eax
mov rax, 60
syscall
mov rsp, rbp
pop rbp
