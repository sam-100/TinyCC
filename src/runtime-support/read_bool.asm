

section .text
    global read_bool
read_bool:
    push rbp
    mov rbp, rsp

    ; read a boolean from stdin here
    mov rax, 0      ; sys read
    mov rdi, 0      ; stdin
    mov rsi, [rbp+16]
    mov rdx, 4
    syscall

    leave
    ret