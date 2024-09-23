    .intel_syntax noprefix 
    .global main
main:
    call readi64
    mov rbx, rax

    xor r13, r13
    cmp rbx, 0
    jl negative
    jmp positive

negative:
    add r13, 1
positive:
    xor r12, r12
    add r12, 1
    
start_testing:
    test rbx, r12
    jnz have_one
    jmp have_zero

have_one:
    add r13, 1
have_zero:
    
    sal r12, 1
    jo printing_result
    jmp start_testing

printing_result:
    mov rdi, r13
    call writei64
    call finish
