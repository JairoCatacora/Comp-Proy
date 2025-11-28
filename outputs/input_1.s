.section .data
print_fmt: .asciz "%d\n"
.section .text

.globl suma
suma:
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
 addq %rcx, %rax
 jmp .end_suma
.end_suma:
 leave
 ret

.globl factorial
factorial:
 pushq %rbp
 movq %rsp, %rbp
 subq $16, %rsp
 movq %rdi, -8(%rbp)
 movq -8(%rbp), %rax
 cmpq $0, %rax
 je else_0
 jmp endif_0
 else_0:
endif_0:
.end_factorial:
 leave
 ret
.section note.GNU-stack,"",@progbits

