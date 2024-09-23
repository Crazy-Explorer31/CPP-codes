    .intel_syntax noprefix 
    .global main
main:
    call readi64
    mov r12, rax

    call readi64
    mov r13, rax

    call readi64
    mov r14, rax

    call readi64
    mov r15, rax

    sal r13, 1

    mov rbx, r14
    sal r14, 4
    add r14, rbx

    sub r12, r13
    add r12, r14

    mov rdi, r15
    call writei64

    mov rdi, r12
    call writei64

    call finish