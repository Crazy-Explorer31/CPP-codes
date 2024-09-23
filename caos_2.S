    .intel_syntax noprefix 
    .global main
main:
    mov rdi, 42
    call writei64
    call finish