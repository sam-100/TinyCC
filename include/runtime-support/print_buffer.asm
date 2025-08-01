

section .text

    global print_buffer
print_buffer:
    ; function prologue
    push rbp
    mov rbp, rsp

    mov rsi, [rbp+16]

.loop:
    mov rax, 1
    mov rdi, 1
    mov rdx, 1
    syscall

    inc rsi
    cmp byte [rsi], 0
    jne .loop

    ; function epilogue and return
    leave
    ret