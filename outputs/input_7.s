.section .data
print_fmt: .asciz "%d\n"
.section .text

.globl getAge
getAge:
 pushq %rbp
 movq %rsp, %rbp
 subq $16, %rsp
 movq %rdi, -8(%rbp)
 leaq -8(%rbp), %rax
 addq $8, %rax
 movq (%rax), %rax
 jmp .end_getAge
.end_getAge:
 leave
 ret

.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $32, %rsp
 movq $25, %rax
 pushq %rax
 leaq -8(%rbp), %rcx
 addq $8, %rcx
 popq %rax
 movq %rax, (%rcx)
 pushq %rax
 leaq -8(%rbp), %rcx
 addq $8, %rcx
 pushq %rcx
 movq $0, %rax
 imulq $8, %rax
 popq %rcx
 addq %rax, %rcx
 popq %rax
 movq %rax, (%rcx)
 pushq %rax
 leaq -8(%rbp), %rcx
 addq $8, %rcx
 pushq %rcx
 movq $1, %rax
 imulq $8, %rax
 popq %rcx
 addq %rax, %rcx
 popq %rax
 movq %rax, (%rcx)
 pushq %rax
 leaq -8(%rbp), %rcx
 addq $8, %rcx
 pushq %rcx
 movq $2, %rax
 imulq $8, %rax
 popq %rcx
 addq %rax, %rcx
 popq %rax
 movq %rax, (%rcx)
 pushq %rax
 leaq -8(%rbp), %rcx
 addq $8, %rcx
 pushq %rcx
 movq $3, %rax
 imulq $8, %rax
 popq %rcx
 addq %rax, %rcx
 popq %rax
 movq %rax, (%rcx)
 movq $0, %rax
 pushq %rax
 leaq -8(%rbp), %rcx
 addq $8, %rcx
 pushq %rcx
 movq $4, %rax
 imulq $8, %rax
 popq %rcx
 addq %rax, %rcx
 popq %rax
 movq %rax, (%rcx)
 pushq %rax
 popq %rax
 movq %rax, -24(%rbp)
.end_main:
 leave
 ret
.section note.GNU-stack,"",@progbits

