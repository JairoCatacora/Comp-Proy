.section .data
print_fmt: .asciz "%d\n"
.section .text

.globl Comparar
Comparar:
 pushq %rbp
 movq %rsp, %rbp
 subq $32, %rsp
 movq %rdi, -8(%rbp)
 movq %rsi, -16(%rbp)
 jmp .end_Comparar
.end_Comparar:
 leave
 ret

.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $32, %rsp
 movq $1, %rax
 movq %rax, -8(%rbp)
 movq $5, %rax
 movq %rax, -16(%rbp)
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 movl $0, %eax
 call printf@PLT
.end_main:
 leave
 ret
.section note.GNU-stack,"",@progbits

