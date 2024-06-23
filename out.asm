global _start
_start:
push rbp
mov rbp, rsp
jmp function_end0
function_test:
push rbp
mov rbp, rsp
mov rax, 43
push rax
lea rax, [rbp - 8]
push rax
mov rax, 30
pop rcx
mov [rcx], rax
mov rax, [rbp - -16]
neg rax
push rax
mov rax, [rbp - 8]
neg rax
neg rax
pop rcx
add rax, rcx
jmp end_label1
end_label1:
mov rsp, rbp
pop rbp
ret
function_end0:
mov rax, 1
push rax
mov rax, [rbp - 8]
push rax
call function_test
; print start
push 10
mov r9, 8
mov r10, 10
mov rcx, rax
cmp rax, 0
jns print_neg5
neg rax
print_neg5:
print_loop4:
xor rdx, rdx
div r10
add rdx, 48
push rdx
add r9, 8
cmp rax, 0
jne print_loop4
cmp rcx, 0
jns print_sign6
push 45
add r9, 8
print_sign6:
mov rsi, rsp
mov rax, 1
mov rdi, 1
xor rdx, rdx
mov rdx, r9
syscall
add rsp, r9
; print end
mov rax, 2
push rax
call function_test
; print start
push 10
mov r9, 8
mov r10, 10
mov rcx, rax
cmp rax, 0
jns print_neg8
neg rax
print_neg8:
print_loop7:
xor rdx, rdx
div r10
add rdx, 48
push rdx
add r9, 8
cmp rax, 0
jne print_loop7
cmp rcx, 0
jns print_sign9
push 45
add r9, 8
print_sign9:
mov rsi, rsp
mov rax, 1
mov rdi, 1
xor rdx, rdx
mov rdx, r9
syscall
add rsp, r9
; print end
mov rax, 0
mov rdi, rax
mov rax, 60
syscall
mov rsp, rbp
pop rbp
