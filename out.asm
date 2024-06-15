global _start
_start:
mov rax, 9
add rax, 48
push 10
push rax
mov rsi, rsp
mov rax, 1
mov rdi, 1
mov rdx, 9
syscall
add rsp, 9
mov rax, 23
mov rdi, rax
mov rax, 60
syscall

