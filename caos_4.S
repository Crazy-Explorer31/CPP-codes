    .intel_syntax noprefix 
    .global main
main:
    call readi64
    mov rbx, rax
    
    cmp rbx, 0
    jl end_point

comparing_point:
    mov rdi, rbx
    call writei64
    sub rbx, 1

    jl end_point
    jmp comparing_point

end_point:
    call finish