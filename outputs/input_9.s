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
 movq -8(%rbp), %rax
 movq %rax, %rdi
 movq -16(%rbp), %rax
 movq %rax, %rsi
 call Comparar
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 movl $0, %eax
 call printf@PLT
.end_main:
 leave
 ret
.section note.GNU-stack,"",@progbits

