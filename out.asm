global _start
_start:
; 19lowered_block_start
push rbp
mov rbp, rsp
sub rsp, 32
; 19bound_stmt_function
jmp function_end1
function_test_int:
; 19lowered_block_start
push rbp
mov rbp, rsp
sub rsp, 12
; 18bound_stmt_var_dec
mov eax, 43
mov dword [rbp + -4], eax
; 15bound_stmt_expr
lea rax, dword [rbp + -4]
mov qword [rbp + -12], rax
mov eax, 30
mov rcx, qword [rbp + -12]
mov dword [rcx], eax
; 17bound_stmt_return
mov eax, dword [rbp + 16]
mov qword [rbp + -12], rax
mov eax, dword [rbp + -4]
neg eax
mov rcx, qword [rbp + -12]
add eax, ecx
jmp end_label2
end_label2:
mov rsp, rbp
pop rbp
ret 
function_end1:
; 18bound_stmt_var_dec
mov qword [rbp + -8], rax
; 15bound_stmt_expr
lea rax, qword [rbp + -8]
mov qword [rbp + -24], rax
mov rcx, qword [rbp + -24]
mov qword [rcx], rax
; 18bound_stmt_var_dec
mov eax, 1
mov dword [rbp + -12], eax
; 18bound_stmt_var_dec
mov dword [rbp + -16], eax
; 15bound_stmt_expr
push rbp
mov eax, dword [rbp + -12]
mov dword [rsp + -4], eax
mov rbp, rsp
sub rsp, 4
call function_test_int
mov rsp, rbp
pop rbp
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
; 15bound_stmt_expr
push rbp
mov eax, 2
mov dword [rsp + -4], eax
mov rbp, rsp
sub rsp, 4
call function_test_int
mov rsp, rbp
pop rbp
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
; 17bound_stmt_gotoif
mov ax, 0
cmp ax, 0
mov cx, 1
cmovz ax, cx
mov cx, 0
cmovnz ax, cx
cmp ax, 0
je if_end0
; 19lowered_block_start
push rbp
mov rbp, rsp
sub rsp, 8
; 15bound_stmt_expr
mov ax, 97
; print_start
push 10
and rax, 65535
push rax
mov rsi, rsp
mov rax, 1
mov rdi, 1
mov rdx, 16
syscall 
add rsp, 16
; print end
; 17lowered_block_end
mov rsp, rbp
pop rbp
; 16bound_stmt_label
if_end0:
; 15bound_stmt_exit
mov eax, 0
mov edi, eax
mov rax, 60
syscall 
; 17lowered_block_end
mov rsp, rbp
pop rbp
