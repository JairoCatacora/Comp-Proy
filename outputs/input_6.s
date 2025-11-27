.section .data
print_fmt: .asciz "%d\n"
.section .text

.globl findMax
findMax:
 pushq %rbp
 movq %rsp, %rbp
 movq %rdi, -8(%rbp)
 movq %rsi, -16(%rbp)
 movq -8(%rbp), %rax
 pushq %rax
 popq %rax
 movq %rax, -24(%rbp)
 movq $1, %rax
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
 movq -8(%rbp), %rax
 pushq %rax
 movq -24(%rbp), %rax
 movq %rax, %rcx
 popq %rax
 cmpq $0, %rax
 je else_1
 movq -8(%rbp), %rax
 pushq %rax
 popq %rax
 movq %rax, -24(%rbp)
 jmp endif_1
 else_1:
 movq -24(%rbp), %rax
 pushq %rax
 popq %rax
 movq %rax, -24(%rbp)
endif_1:
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
 jmp .end_findMax
.end_findMax:
 movq %rbp, %rsp
 popq %rbp
 ret

.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $15, %rax
 pushq %rax
 popq %rax
 movq %rax, -8(%rbp)
 movq $42, %rax
 pushq %rax
 popq %rax
 movq %rax, -8(%rbp)
 movq $8, %rax
 pushq %rax
 popq %rax
 movq %rax, -8(%rbp)
 movq $23, %rax
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
