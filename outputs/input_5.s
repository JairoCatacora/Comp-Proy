.section .data
print_fmt: .asciz "%d\n"
.section .text

.globl countTo
countTo:
 pushq %rbp
 movq %rsp, %rbp
 subq $32, %rsp
 movq %rdi, -8(%rbp)
 movq $0, %rax
 pushq %rax
 popq %rax
 movq %rax, -16(%rbp)
 movq $0, %rax
 pushq %rax
 popq %rax
 movq %rax, -24(%rbp)
while_0:
 movq -16(%rbp), %rax
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
 movq -24(%rbp), %rax
 pushq %rax
 movq -16(%rbp), %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 pushq %rax
 popq %rax
 movq %rax, -24(%rbp)
 movq -16(%rbp), %rax
 pushq %rax
 movq $1, %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 pushq %rax
 popq %rax
 movq %rax, -16(%rbp)
 jmp while_0
endwhile_0:
 movq -24(%rbp), %rax
 jmp .end_countTo
.end_countTo:
 leave
 ret

.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $32, %rsp
 movq %rax, -8(%rbp)
 movq $10, %rax
 movq %rax, %rdi
 call countTo
 pushq %rax
 popq %rax
 movq %rax, -16(%rbp)
 movq -16(%rbp), %rax
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

