global _start
_start:
push rbp
mov rbp, rsp
mov eax, 1
; print start
push 10
mov r9d, 8
mov r10d, 10
print_loop0:
xor edx, edx
div r10d
add edx, 48
and rdx, -1
push rdx
add r9d, 8
cmp eax, 0
jne print_loop0
mov rsi, rsp
mov rax, 1
mov rdi, 1
xor rdx, rdx
mov edx, r9d
syscall
and r9, -1
add rsp, r9
; print end
mov eax, 32
and rax, -1
push rax
push rbp
mov rbp, rsp
mov ax, 0
and rax, 0xFFFF
push rax
mov rax, [rbp - 8]
and rax, 0xFFFF
; print start
push 10
cmp ax, 0
jne print_true1
mov r9w, 48
push 101
push 115
push 108
push 97
push 102
jmp print_end2
print_true1:
mov r9w, 40
push 101
push 117
push 114
push 116
print_end2:
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
mov rax, [rbp - 8]
and rax, -1
; print start
push 10
mov r9d, 8
mov r10d, 10
print_loop3:
xor edx, edx
div r10d
add edx, 48
and rdx, -1
push rdx
add r9d, 8
cmp eax, 0
jne print_loop3
mov rsi, rsp
mov rax, 1
mov rdi, 1
xor rdx, rdx
mov edx, r9d
syscall
and r9, -1
add rsp, r9
; print end
mov eax, 0
mov edi, eax
mov rax, 60
syscall
mov rsp, rbp
pop rbp
