global _start
_start:
mov ax, 1
push ax
mov ax, 0
pop cx
or ax, cx
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
add sp, r9w
mov rax, 1
push rax
mov rax, 3
pop rcx
cmp rcx, rax
jl condition_true6
mov rax, 0
jmp condition_end7
condition_true6:
mov rax, 1
condition_end7:
push 10
cmp ax, 0
jne print_true4
mov r9w, 48
push 101
push 115
push 108
push 97
push 102
jmp print_end5
print_true4:
mov r9w, 40
push 101
push 117
push 114
push 116
print_end5:
mov rsi, rsp
mov rax, 1
mov rdi, 1
xor rdx, rdx
mov dx, r9w
syscall
add sp, r9w
mov rax, 2
push rax
mov rax, 4
pop rcx
add rax, rcx
push rax
mov rax, 6
pop rcx
cmp rcx, rax
je condition_true12
mov rax, 0
jmp condition_end13
condition_true12:
mov rax, 1
condition_end13:
push 10
cmp ax, 0
jne print_true8
mov r9w, 48
push 101
push 115
push 108
push 97
push 102
jmp print_end9
print_true8:
mov r9w, 40
push 101
push 117
push 114
push 116
print_end9:
mov rsi, rsp
mov rax, 1
mov rdi, 1
xor rdx, rdx
mov dx, r9w
syscall
add sp, r9w
mov ax, 115
push ax
mov ax, 91
pop cx
cmp cx, ax
jne condition_true16
mov ax, 0
jmp condition_end17
condition_true16:
mov ax, 1
condition_end17:
push 10
cmp ax, 0
jne print_true14
mov r9w, 48
push 101
push 115
push 108
push 97
push 102
jmp print_end15
print_true14:
mov r9w, 40
push 101
push 117
push 114
push 116
print_end15:
mov rsi, rsp
mov rax, 1
mov rdi, 1
xor rdx, rdx
mov dx, r9w
syscall
add sp, r9w
mov rax, 0
mov rdi, rax
mov rax, 60
syscall

