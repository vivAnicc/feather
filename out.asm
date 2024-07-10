global _start
_start:
push rbp
mov rbp, rsp
sub rsp, 4
jmp function_end1
function_test:
push rbp
mov rbp, rsp
sub rsp, 12
mov eax, 43
and rax, -1
mov dword [rbp - 4], eax
lea rax, [rbp - 4]
mov qword [rbp - 12], rax
mov eax, 30
mov rcx, qword [rbp - 12]
mov dword [rcx], eax
mov rax, [rbp - -12]
and rax, -1
mov qword [rbp - 12], rax
mov rax, [rbp - 4]
and rax, -1
neg eax
mov rcx, qword [rbp - 12]
add eax, ecx
jmp end_label2
end_label2:
mov rsp, rbp
pop rbp
ret
function_end1:
mov eax, 1
and rax, -1
mov dword [rbp - 4], eax
mov rax, [rbp - 4]
and rax, -1
and rax, -1
push rax
call function_test
; print start
push 10
mov r9d, 8
mov r10d, 10
mov rcx, rax
cmp eax, 0
jns print_neg6
neg eax
print_neg6:
print_loop5:
xor edx, edx
div r10d
add edx, 48
and rdx, -1
push rdx
add r9d, 8
cmp eax, 0
jne print_loop5
cmp ecx, 0
jns print_sign7
push 45
add r9, 8
print_sign7:
mov rsi, rsp
mov rax, 1
mov rdi, 1
xor rdx, rdx
mov edx, r9d
syscall
and r9, -1
add rsp, r9
; print end
mov eax, 2
and rax, -1
push rax
call function_test
; print start
push 10
mov r9d, 8
mov r10d, 10
mov rcx, rax
cmp eax, 0
jns print_neg9
neg eax
print_neg9:
print_loop8:
xor edx, edx
div r10d
add edx, 48
and rdx, -1
push rdx
add r9d, 8
cmp eax, 0
jne print_loop8
cmp ecx, 0
jns print_sign10
push 45
add r9, 8
print_sign10:
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
mov cx, 1
cmovz ax, cx
mov cx, 0
cmovnz ax, cx
cmp ax, 0
je if_end0
push rbp
mov rbp, rsp
sub rsp, 0
mov ax, 97
; print start
push 10
and rax, 0xFFFF
push rax
mov rsi, rsp
mov rax, 1
mov rdi, 1
mov rdx, 16
syscall
add rsp, 16
; print end
mov rsp, rbp
pop rbp
if_end0:
mov eax, 0
mov edi, eax
mov rax, 60
syscall
mov rsp, rbp
pop rbp
