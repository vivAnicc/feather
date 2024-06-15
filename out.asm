global _start
_start:
mov eax, 24
push rax
mov eax, 3
pop rcx
add rax, rcx
push 10
mov r9, 1
mov r10, 10
print_loop0:
xor rdx, rdx
div r10
add rdx, 48
push rdx
add r9, 8
cmp rax, 0
jne print_loop0
mov rsi, rsp
mov rax, 1
mov rdi, 1
xor rdx, rdx
mov rdx, r9
syscall
add rsp, r9
mov eax, 23
mov rdi, rax
mov rax, 60
syscall

