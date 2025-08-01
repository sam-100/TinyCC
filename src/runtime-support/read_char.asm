

section .text

    global read_char
read_char:
    ; function prologue
    push rbp
    mov rbp, rsp

    mov rax, 0
    mov rdi, 0
    xor rsi, rsi
    mov esi, [rbp+16]
    mov rdx, 4
    syscall


    ; function epilogue and return
    leave
    ret

section .note.GNU-stack noalloc noexec nowrite