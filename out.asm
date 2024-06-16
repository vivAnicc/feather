global _start
_start:
mov rax, 24
push rax
mov rax, 3
pop rcx
add rax, rcx
push 10
mov r9, 8
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
mov al, 1
push 10
cmp al, 0
jne print_true1
mov r9b, 48
push 101
push 115
push 108
push 97
push 102
jmp print_end2
print_true1:
mov r9b, 40
push 101
push 117
push 114
push 116
print_end2:
mov rsi, rsp
mov rax, 1
mov rdi, 1
xor rdx, rdx
mov dl, r9b
syscall
add spl, r9b
mov al, 0
push 10
cmp al, 0
jne print_true3
mov r9b, 48
push 101
push 115
push 108
push 97
push 102
jmp print_end4
print_true3:
mov r9b, 40
push 101
push 117
push 114
push 116
print_end4:
mov rsi, rsp
mov rax, 1
mov rdi, 1
xor rdx, rdx
mov dl, r9b
syscall
add spl, r9b
mov al, 97
push 10
push ax
mov rsi, rsp
mov rax, 1
mov rdi, 1
mov rdx, 10
syscall
add rsp, 10
mov rax, 0
mov rdi, rax
mov rax, 60
syscall

