global _start
_start:
push rbp
mov rbp, rsp
mov eax, 20
and rax, -1
push rax
mov eax, 45
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
mov eax, 14
and rax, -1
mov [rbp - 8], rax
push rbp
mov rbp, rsp
mov eax, 32
and rax, -1
push rax
push rbp
mov rbp, rsp
mov rax, [rbp - -8]
and rax, -1
; print start
push 10
mov r9d, 8
mov r10d, 10
print_loop1:
xor edx, edx
div r10d
add edx, 48
and rdx, -1
push rdx
add r9d, 8
cmp eax, 0
jne print_loop1
mov rsi, rsp
mov rax, 1
mov rdi, 1
xor rdx, rdx
mov edx, r9d
syscall
and r9, -1
add rsp, r9
; print end
mov rsp, rbp
pop rbp
mov rsp, rbp
pop rbp
mov rax, [rbp - 8]
and rax, -1
push rax
mov eax, 2
pop rcx
sub ecx, eax
mov eax, ecx
; print start
push 10
mov r9d, 8
mov r10d, 10
print_loop2:
xor edx, edx
div r10d
add edx, 48
and rdx, -1
push rdx
add r9d, 8
cmp eax, 0
jne print_loop2
mov rsi, rsp
mov rax, 1
mov rdi, 1
xor rdx, rdx
mov edx, r9d
syscall
and r9, -1
add rsp, r9
; print end
mov rax, [rbp - 8]
and rax, -1
; print start
push 10
mov r9d, 8
mov r10d, 10
print_loop5:
xor edx, edx
div r10d
add edx, 48
and rdx, -1
push rdx
add r9d, 8
cmp eax, 0
jne print_loop5
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
