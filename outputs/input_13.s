.section .data
print_fmt: .asciz "%d\n"
.section .text

.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $816, %rsp
 movq $2, %rax
 pushq %rax
 leaq -8(%rbp), %rcx
 pushq %rcx
 movq $0, %rax
 imulq $8, %rax
 popq %rcx
 addq %rax, %rcx
 pushq %rcx
 movq $1, %rax
 imulq $8, %rax
 popq %rcx
 addq %rax, %rcx
 popq %rax
 movq %rax, (%rcx)
 movq $1, %rax
 pushq %rax
 leaq -8(%rbp), %rcx
 pushq %rcx
 movq $1, %rax
 imulq $8, %rax
 popq %rcx
 addq %rax, %rcx
 pushq %rcx
 movq $1, %rax
 imulq $8, %rax
 popq %rcx
 addq %rax, %rcx
 popq %rax
 movq %rax, (%rcx)
 movq $3, %rax
 pushq %rax
 leaq -8(%rbp), %rcx
 pushq %rcx
 movq $2, %rax
 imulq $8, %rax
 popq %rcx
 addq %rax, %rcx
 pushq %rcx
 movq $1, %rax
 imulq $8, %rax
 popq %rcx
 addq %rax, %rcx
 popq %rax
 movq %rax, (%rcx)
 leaq -8(%rbp), %rax
 pushq %rax
 movq $0, %rax
 imulq $8, %rax
 popq %rcx
 addq %rcx, %rax
 pushq %rax
 movq $1, %rax
 imulq $8, %rax
 popq %rcx
 addq %rcx, %rax
 movq (%rax), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 movl $0, %eax
 call printf@PLT
 leaq -8(%rbp), %rax
 pushq %rax
 movq $1, %rax
 imulq $8, %rax
 popq %rcx
 addq %rcx, %rax
 pushq %rax
 movq $2, %rax
 imulq $8, %rax
 popq %rcx
 addq %rcx, %rax
 movq (%rax), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 movl $0, %eax
 call printf@PLT
 movq $0, %rax
 jmp .end_main
.end_main:
 leave
 ret
.section note.GNU-stack,"",@progbits

