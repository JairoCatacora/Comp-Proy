.section .data
print_fmt: .asciz "%d\n"
.section .text

.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $2, %rax
 pushq %rax
 popq %rax
 movq %rax, -8(%rbp)
 movq $1, %rax
 pushq %rax
 popq %rax
 movq %rax, -8(%rbp)
 movq $3, %rax
 pushq %rax
 popq %rax
 movq %rax, -8(%rbp)
 movq -8(%rbp), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 movl $0, %eax
 call printf@PLT
 movq -8(%rbp), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 movl $0, %eax
 call printf@PLT
 movq $0, %rax
 jmp .end_main
.end_main:
 movq %rbp, %rsp
 popq %rbp
 ret
