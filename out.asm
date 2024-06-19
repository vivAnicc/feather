global _start
_start:
push rbp
mov rbp, rsp
and rax, -1
push rax
mov eax, 45
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
mov eax, 14
and rax, -1
mov [rbp - 8], rax
push rbp
mov rbp, rsp
push rbp
mov rbp, rsp
and rax, -1
push rax
mov eax, 65
and rax, -1
mov [rbp - 8], rax
mov eax, 33
and rax, -1
push rax
mov rax, [rbp - 8]
and rax, -1
push rax
mov rax, [rbp - 16]
and rax, -1
pop rcx
sub ecx, eax
mov eax, ecx
and rax, -1
mov [rbp - 8], rax
mov rax, [rbp - 8]
and rax, -1
jmp end_label6
end_label6:
mov rsp, rbp
pop rbp
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
print_loop9:
xor edx, edx
div r10d
add edx, 48
and rdx, -1
push rdx
add r9d, 8
cmp eax, 0
jne print_loop9
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
jmp function_end0
function_test:
push rbp
mov rbp, rsp
and rax, 0xFFFF
push rax
mov ax, 1
and rax, 0xFFFF
mov [rbp - 8], rax
jmp end_label10
end_label10:
mov rsp, rbp
pop rbp
ret
function_end0:
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
print_loop11:
xor edx, edx
div r10d
add edx, 48
and rdx, -1
push rdx
add r9d, 8
cmp eax, 0
jne print_loop11
mov rsi, rsp
mov rax, 1
mov rdi, 1
xor rdx, rdx
mov edx, r9d
syscall
and r9, -1
add rsp, r9
; print end
mov ax, 0
cmp ax, 0
je if_else2
mov rax, [rbp - 8]
and rax, -1
; print start
push 10
mov r9d, 8
mov r10d, 10
print_loop14:
xor edx, edx
div r10d
add edx, 48
and rdx, -1
push rdx
add r9d, 8
cmp eax, 0
jne print_loop14
mov rsi, rsp
mov rax, 1
mov rdi, 1
xor rdx, rdx
mov edx, r9d
syscall
and r9, -1
add rsp, r9
; print end
jmp if_end1
if_else2:
mov ax, 0
cmp ax, 0
je if_else4
push rbp
mov rbp, rsp
mov rax, [rbp - -8]
and rax, -1
push rax
mov eax, 2
pop rcx
xor edx, edx
xchg ecx, eax
div ecx
; print start
push 10
mov r9d, 8
mov r10d, 10
print_loop15:
xor edx, edx
div r10d
add edx, 48
and rdx, -1
push rdx
add r9d, 8
cmp eax, 0
jne print_loop15
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
jmp if_end3
if_else4:
mov rax, [rbp - 8]
and rax, -1
push rax
mov eax, 2
pop rcx
mul ecx
; print start
push 10
mov r9d, 8
mov r10d, 10
print_loop18:
xor edx, edx
div r10d
add edx, 48
and rdx, -1
push rdx
add r9d, 8
cmp eax, 0
jne print_loop18
mov rsi, rsp
mov rax, 1
mov rdi, 1
xor rdx, rdx
mov edx, r9d
syscall
and r9, -1
add rsp, r9
; print end
if_end3:
if_end1:
mov eax, 0
mov edi, eax
mov rax, 60
syscall
mov rsp, rbp
pop rbp
