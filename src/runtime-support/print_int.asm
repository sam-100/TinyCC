%include "print_buffer.asm"

extern integer_to_string
section .text

    global print_int
print_int:
    ; function prologue
    push rbp
    mov rbp, rsp
    sub rsp, 80         ; 16 byte aligned

    ; clear input registers for calling C-function
    xor rdi, rdi
    xor rsi, rsi


    ; pass the arguments and call the function
    mov edi, [rbp+16]           ; debug: getting proper integer in register edi
    mov rsi, rsp
    call integer_to_string

    ; print the string
    mov rax, rsp
    sub rsp, 8
    push rax
    call print_buffer
    add rsp, 16

    ; function epilogue and return
    add rsp, 80
    leave
    ret

section .note.GNU-stack noalloc noexec nowrite