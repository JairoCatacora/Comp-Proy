.section .data
print_fmt: .asciz "%d\n"
.section .text

.globl average
average:
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
 leaq -8(%rbp), %rax
 pushq %rax
 movq -32(%rbp), %rax
 imulq $8, %rax
 popq %rcx
 addq %rcx, %rax
 movq (%rax), %rax
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
 leave
 ret

.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $112, %rsp
 movq $101, %rax
 pushq %rax
 leaq -8(%rbp), %rcx
 addq $8, %rcx
 popq %rax
 movq %rax, (%rcx)
 movq $85, %rax
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
 movq $90, %rax
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
 movq $78, %rax
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
 popq %rax
 movq %rax, -24(%rbp)
.end_main:
 leave
 ret
.section note.GNU-stack,"",@progbits

