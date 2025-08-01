%include "read_buffer.asm"

extern string_to_integer
extern integer_to_string

section .text

    global read_int
read_int:
    ; function prologue
    push rbp
    mov rbp, rsp
    sub rsp, 80

    ; read a integer as as string from user
    mov rax, rsp
    sub rsp, 8
    push rax
    call read_buffer
    add rsp, 16

    ; convert the string to integer (with sign)
    mov rdi, rsp
    call string_to_integer

    ; function epilogue and return
    add rsp, 80
    leave
    ret

section .note.GNU-stack noalloc noexec nowrite