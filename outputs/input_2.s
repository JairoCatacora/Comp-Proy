.section .data
print_fmt: .asciz "%d\n"
.section .text

.globl countTo
countTo:
 pushq %rbp
 movq %rsp, %rbp
 movq %rdi, -8(%rbp)
 movq $0, %rax
 pushq %rax
 movq $0, %rax
 pushq %rax
while_0:
 pushq %rax
 movq -8(%rbp), %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 movl $0, %eax
 setle %al
 movzbq %al, %rax
 cmpq $0, %rax
 je endwhile_0
 pushq %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 pushq %rax
 pushq %rax
 movq $1, %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 pushq %rax
 jmp while_0
endwhile_0:
.end_countTo:
 movq %rbp, %rsp
 popq %rbp
 ret
 jmp .end_countTo
