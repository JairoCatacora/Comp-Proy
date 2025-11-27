.section .data
print_fmt: .asciz "%d\n"
.section .text

.globl average
average:
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
 movq -32(%rbp), %rax
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
 movq -24(%rbp), %rax
 pushq %rax
 movq -8(%rbp), %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 pushq %rax
 popq %rax
 movq %rax, -24(%rbp)
 movq -32(%rbp), %rax
 pushq %rax
 movq $1, %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 pushq %rax
 popq %rax
 movq %rax, -32(%rbp)
 jmp while_0
endwhile_0:
 movq -24(%rbp), %rax
 jmp .end_average
.end_average:
 movq %rbp, %rsp
 popq %rbp
 ret

.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
.end_main:
 movq %rbp, %rsp
 popq %rbp
 ret
