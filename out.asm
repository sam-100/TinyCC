extern read_int
extern print_int


section .data


section .bss


section .text
	global _start
_start: 
	call main

.exit:
	mov rax, 60
	mov rdi, 0
	syscall
	global main
main: 
	push rbp
	mov rbp, rsp
	sub rsp, 32

	; TAC_READ_STMT statement
	sub rsp, 8
	lea rax, [rbp-8]
	push rax
	call read_int
	add rsp, 16
	mov [rbp-8], rax

	; TAC_READ_STMT statement
	sub rsp, 8
	lea rax, [rbp-16]
	push rax
	call read_int
	add rsp, 16
	mov [rbp-16], rax

	; TAC_ASSIGN_STMT statement
	mov eax, [rbp-8]
	mov ecx, [rbp-16]
	add eax, ecx
	mov [rbp-24], eax

	; TAC_COPY_STMT statement
	mov eax, [rbp-24]
	mov [rbp-24], eax

	; TAC_PRINT_STMT statement
	sub rsp, 8
	push qword [rbp-24]
	call print_int
	add rsp, 16

	; TAC_RETURN_VOID_STMT statement
	add rsp, 32
	leave
	ret

section .note.GNU-stack noalloc noexec nowrite progbits