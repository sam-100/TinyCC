

section .text

    global print_char
print_char:
    ; function prologue
    push rbp
    mov rbp, rsp

    mov rax, 1
    mov rdi, 1
    xor rsi, rsi
    mov esi, [rbp+16]
    mov rdx, 4
    syscall


    ; function epilogue and return
    leave
    ret

section .note.GNU-stack noalloc noexec nowrite