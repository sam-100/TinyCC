
section .text
    global read_buffer
read_buffer:
    ; function prologue
    push rbp
    mov rbp, rsp

    ; set the destination pointer
    mov rsi, [rbp+16]

.input_loop:
    ; read a character
    mov rax, 0              ; sys read
    mov rdi, 0              ; stdin 
    mov rdx, 1              ; size to read
    syscall

    ; check new line character
    cmp byte [rsi], 10
    je .input_end

    ; increment the pointer and jump back to loop
    inc rsi
    jmp .input_loop

.input_end:
    mov byte [rsi], 0

.return:
    ; function epilogue
    leave
    ret