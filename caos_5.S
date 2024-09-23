    .intel_syntax noprefix 
    .global main
main:
    xor r12, r12
    xor r12, r12
    xor r14, r14
    add r14, 1

reading_continue:
    call readi64
    jc printing_result

    mov r15, rax
    test r15, 1
    jnz summing_odd
    jmp summing_not_odd

summing_odd:
    add r13, r15
    jmp reading_continue
summing_not_odd:
    add r12, r15
    jmp reading_continue

printing_result:
    mov rdi, r12
    call writei64

    mov rdi, r13
    call writei64

    call finish
