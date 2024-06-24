global _start
_start:
push rbp
mov rbp, rsp
jmp function_end0
function_test:
push rbp
mov rbp, rsp
mov eax, 43
and rax, -1
push rax
lea rax, [rbp - 8]
push rax
mov eax, 30
pop rcx
mov [rcx], rax
mov rax, [rbp - -16]
and rax, -1
push rax
mov rax, [rbp - 8]
and rax, -1
neg eax
pop rcx
add eax, ecx
jmp end_label1
end_label1:
mov rsp, rbp
pop rbp
ret
function_end0:
mov eax, 1
and rax, -1
push rax
mov rax, [rbp - 8]
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
jns print_neg5
neg eax
print_neg5:
print_loop4:
xor edx, edx
div r10d
add edx, 48
and rdx, -1
push rdx
add r9d, 8
cmp eax, 0
jne print_loop4
cmp ecx, 0
jns print_sign6
push 45
add r9, 8
print_sign6:
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
jns print_neg8
neg eax
print_neg8:
print_loop7:
xor edx, edx
div r10d
add edx, 48
and rdx, -1
push rdx
add r9d, 8
cmp eax, 0
jne print_loop7
cmp ecx, 0
jns print_sign9
push 45
add r9, 8
print_sign9:
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
