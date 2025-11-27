.section .data
print_fmt: .asciz "%d\n"
.section .text

.globl Comparar
Comparar:
 pushq %rbp
 movq %rsp, %rbp
 movq %rdi, -8(%rbp)
 movq %rsi, -16(%rbp)
 jmp .end_Comparar
.end_Comparar:
 movq %rbp, %rsp
 popq %rbp
 ret

.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 movq $1, %rax
 movq %rax, -8(%rbp)
 movq $5, %rax
 movq %rax, -16(%rbp)
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 movl $0, %eax
 call printf@PLT
.end_main:
 movq %rbp, %rsp
 popq %rbp
 ret
