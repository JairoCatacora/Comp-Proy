.section .data
print_fmt: .asciz "%d\n"
.section .text

.globl maximo
maximo:
 pushq %rbp
 movq %rsp, %rbp
 subq $32, %rsp
 movq %rdi, -8(%rbp)
 movq %rsi, -16(%rbp)
 movq -8(%rbp), %rax
 pushq %rax
 movq -16(%rbp), %rax
 movq %rax, %rcx
 popq %rax
 cmpq $0, %rax
 je else_0
 movq -8(%rbp), %rax
 jmp .end_maximo
 jmp endif_0
 else_0:
 movq -16(%rbp), %rax
 jmp .end_maximo
endif_0:
.end_maximo:
 leave
 ret

.globl minimo
minimo:
 pushq %rbp
 movq %rsp, %rbp
 subq $32, %rsp
 movq %rdi, -8(%rbp)
 movq %rsi, -16(%rbp)
 movq -8(%rbp), %rax
 pushq %rax
 movq -16(%rbp), %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 movl $0, %eax
 setle %al
 movzbq %al, %rax
 cmpq $0, %rax
 je else_1
 movq -8(%rbp), %rax
 jmp .end_minimo
 jmp endif_1
 else_1:
 movq -16(%rbp), %rax
 jmp .end_minimo
endif_1:
.end_minimo:
 leave
 ret

.globl absoluto
absoluto:
 pushq %rbp
 movq %rsp, %rbp
 subq $16, %rsp
 movq %rdi, -8(%rbp)
 movq -8(%rbp), %rax
 pushq %rax
 movq $0, %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 movl $0, %eax
 setle %al
 movzbq %al, %rax
 cmpq $0, %rax
 je else_2
 movq $0, %rax
 pushq %rax
 movq -8(%rbp), %rax
 movq %rax, %rcx
 popq %rax
 subq %rcx, %rax
 jmp .end_absoluto
 jmp endif_2
 else_2:
 movq -8(%rbp), %rax
 jmp .end_absoluto
endif_2:
.end_absoluto:
 leave
 ret

.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $48, %rsp
 movq $10, %rax
 pushq %rax
 popq %rax
 movq %rax, -8(%rbp)
 movq $25, %rax
 pushq %rax
 popq %rax
 movq %rax, -16(%rbp)
 pushq %rax
 popq %rax
 movq %rax, -24(%rbp)
.end_main:
 leave
 ret
.section note.GNU-stack,"",@progbits

