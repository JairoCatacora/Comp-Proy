.section .data
print_fmt: .asciz "%d\n"
.section .text

.globl esPar
esPar:
 pushq %rbp
 movq %rsp, %rbp
 subq $32, %rsp
 movq %rdi, -8(%rbp)
 movq -8(%rbp), %rax
 pushq %rax
 movq $2, %rax
 movq %rax, %rcx
 popq %rax
 pushq %rax
 popq %rax
 movq %rax, -16(%rbp)
 movq -8(%rbp), %rax
 pushq %rax
 movq -16(%rbp), %rax
 pushq %rax
 movq $2, %rax
 movq %rax, %rcx
 popq %rax
 imulq %rcx, %rax
 movq %rax, %rcx
 popq %rax
 subq %rcx, %rax
 pushq %rax
 popq %rax
 movq %rax, -16(%rbp)
 movq -16(%rbp), %rax
 pushq %rax
 movq $0, %rax
 movq %rax, %rcx
 popq %rax
 cmpq $0, %rax
 je else_0
 movq $0, %rax
 jmp .end_esPar
 jmp endif_0
 else_0:
 movq $1, %rax
 jmp .end_esPar
endif_0:
.end_esPar:
 leave
 ret

.globl potencia
potencia:
 pushq %rbp
 movq %rsp, %rbp
 subq $48, %rsp
 movq %rdi, -8(%rbp)
 movq %rsi, -16(%rbp)
 movq $1, %rax
 pushq %rax
 popq %rax
 movq %rax, -24(%rbp)
 movq $0, %rax
 pushq %rax
 popq %rax
 movq %rax, -32(%rbp)
while_1:
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
 je endwhile_1
 movq -24(%rbp), %rax
 pushq %rax
 movq -8(%rbp), %rax
 movq %rax, %rcx
 popq %rax
 imulq %rcx, %rax
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
 jmp while_1
endwhile_1:
 movq -24(%rbp), %rax
 jmp .end_potencia
.end_potencia:
 leave
 ret

.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $32, %rsp
 movq $4, %rax
 pushq %rax
 popq %rax
 movq %rax, -8(%rbp)
 cmpq $0, %rax
 je else_2
 jmp endif_2
 else_2:
endif_2:
.end_main:
 leave
 ret
.section note.GNU-stack,"",@progbits

