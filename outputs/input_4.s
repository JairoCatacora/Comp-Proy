.section .data
print_fmt: .asciz "%d\n"
.section .text

.globl sumArray
sumArray:
 pushq %rbp
 movq %rsp, %rbp
 subq $48, %rsp
 movq %rdi, -8(%rbp)
 movq %rsi, -16(%rbp)
 movq $0, %rax
 pushq %rax
 popq %rax
 movq %rax, -24(%rbp)
 movq $0, %rax
 pushq %rax
 popq %rax
 movq %rax, -32(%rbp)
while_0:
 movq -24(%rbp), %rax
 pushq %rax
 movq -16(%rbp), %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 movl $0, %eax
 setle %al
 movzbq %al, %rax
 cmpq $0, %rax
 je endwhile_0
 movq -32(%rbp), %rax
 pushq %rax
 leaq -8(%rbp), %rax
 pushq %rax
 movq -24(%rbp), %rax
 imulq $8, %rax
 popq %rcx
 addq %rcx, %rax
 movq (%rax), %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 pushq %rax
 popq %rax
 movq %rax, -32(%rbp)
 movq -24(%rbp), %rax
 pushq %rax
 movq $1, %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 pushq %rax
 popq %rax
 movq %rax, -24(%rbp)
 jmp while_0
endwhile_0:
 movq -32(%rbp), %rax
 jmp .end_sumArray
.end_sumArray:
 leave
 ret

.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $96, %rsp
 movq $10, %rax
 pushq %rax
 leaq -8(%rbp), %rcx
 pushq %rcx
 movq $0, %rax
 imulq $8, %rax
 popq %rcx
 addq %rax, %rcx
 popq %rax
 movq %rax, (%rcx)
 movq $20, %rax
 pushq %rax
 leaq -8(%rbp), %rcx
 pushq %rcx
 movq $1, %rax
 imulq $8, %rax
 popq %rcx
 addq %rax, %rcx
 popq %rax
 movq %rax, (%rcx)
 movq $30, %rax
 pushq %rax
 leaq -8(%rbp), %rcx
 pushq %rcx
 movq $2, %rax
 imulq $8, %rax
 popq %rcx
 addq %rax, %rcx
 popq %rax
 movq %rax, (%rcx)
 movq $40, %rax
 pushq %rax
 leaq -8(%rbp), %rcx
 pushq %rcx
 movq $3, %rax
 imulq $8, %rax
 popq %rcx
 addq %rax, %rcx
 popq %rax
 movq %rax, (%rcx)
 movq $50, %rax
 pushq %rax
 leaq -8(%rbp), %rcx
 pushq %rcx
 movq $4, %rax
 imulq $8, %rax
 popq %rcx
 addq %rax, %rcx
 popq %rax
 movq %rax, (%rcx)
 movq -8(%rbp), %rax
 movq %rax, %rdi
 movq $5, %rax
 movq %rax, %rsi
 call sumArray
 pushq %rax
 popq %rax
 movq %rax, -88(%rbp)
 movq -88(%rbp), %rax
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

