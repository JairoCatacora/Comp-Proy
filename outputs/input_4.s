.section .data
print_fmt: .asciz "%d\n"
.section .text

.globl sumArray
sumArray:
 pushq %rbp
 movq %rsp, %rbp
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
 movq -8(%rbp), %rax
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
 movq %rbp, %rsp
 popq %rbp
 ret

.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $10, %rax
 pushq %rax
 popq %rax
 movq %rax, -8(%rbp)
 movq $20, %rax
 pushq %rax
 popq %rax
 movq %rax, -8(%rbp)
 movq $30, %rax
 pushq %rax
 popq %rax
 movq %rax, -8(%rbp)
 movq $40, %rax
 pushq %rax
 popq %rax
 movq %rax, -8(%rbp)
 movq $50, %rax
 pushq %rax
 popq %rax
 movq %rax, -8(%rbp)
 pushq %rax
 popq %rax
 movq %rax, -16(%rbp)
.end_main:
 movq %rbp, %rsp
 popq %rbp
 ret
