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
 movq $1, %rax
 pushq %rax
while_0:
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
 movq %rax, %rcx
 popq %rax
 cmpq $0, %rax
 je else_1
 movq -8(%rbp), %rax
 pushq %rax
 jmp endif_1
 else_1:
 pushq %rax
endif_1:
 jmp while_0
endwhile_0:
.end_findMax:
 movq %rbp, %rsp
 popq %rbp
 ret
.section .data
=: .quad 0
.section .text
.section .data
+: .quad 0
.section .text
