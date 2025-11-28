.section .data
print_fmt: .asciz "%d\n"
.section .text

.globl findMax
findMax:
 pushq %rbp
 movq %rsp, %rbp
 subq $48, %rsp
 movq %rdi, -8(%rbp)
 movq %rsi, -16(%rbp)
 leaq -8(%rbp), %rax
 pushq %rax
 movq $0, %rax
 imulq $8, %rax
 popq %rcx
 addq %rcx, %rax
 movq (%rax), %rax
 pushq %rax
 popq %rax
 movq %rax, -24(%rbp)
 movq $1, %rax
 pushq %rax
 popq %rax
 movq %rax, -32(%rbp)
while_0:
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
 je endwhile_0
 leaq -8(%rbp), %rax
 pushq %rax
 movq -32(%rbp), %rax
 imulq $8, %rax
 popq %rcx
 addq %rcx, %rax
 movq (%rax), %rax
 pushq %rax
 movq -24(%rbp), %rax
 movq %rax, %rcx
 popq %rax
 cmpq %rcx, %rax
 movl $0, %eax
 setg %al
 movzbq %al, %rax
 cmpq $0, %rax
 je else_1
 leaq -8(%rbp), %rax
 pushq %rax
 movq -32(%rbp), %rax
 imulq $8, %rax
 popq %rcx
 addq %rcx, %rax
 movq (%rax), %rax
 pushq %rax
 popq %rax
 movq %rax, -24(%rbp)
 jmp endif_1
 else_1:
 movq -24(%rbp), %rax
 pushq %rax
 popq %rax
 movq %rax, -24(%rbp)
endif_1:
 movq -32(%rbp), %rax
 pushq %rax
 movq $1, %rax
 movq %rax, %rcx
 popq %rax
 addq %rcx, %rax
 pushq %rax
 popq %rax
 movq %rax, -32(%rbp)
 jmp while_0
endwhile_0:
 movq -24(%rbp), %rax
 jmp .end_findMax
.end_findMax:
 leave
 ret

.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $96, %rsp
 movq $15, %rax
 pushq %rax
 leaq -8(%rbp), %rcx
 pushq %rcx
 movq $0, %rax
 imulq $8, %rax
 popq %rcx
 addq %rax, %rcx
 popq %rax
 movq %rax, (%rcx)
 movq $42, %rax
 pushq %rax
 leaq -8(%rbp), %rcx
 pushq %rcx
 movq $1, %rax
 imulq $8, %rax
 popq %rcx
 addq %rax, %rcx
 popq %rax
 movq %rax, (%rcx)
 movq $8, %rax
 pushq %rax
 leaq -8(%rbp), %rcx
 pushq %rcx
 movq $2, %rax
 imulq $8, %rax
 popq %rcx
 addq %rax, %rcx
 popq %rax
 movq %rax, (%rcx)
 movq $23, %rax
 pushq %rax
 leaq -8(%rbp), %rcx
 pushq %rcx
 movq $3, %rax
 imulq $8, %rax
 popq %rcx
 addq %rax, %rcx
 popq %rax
 movq %rax, (%rcx)
 movq -8(%rbp), %rax
 movq %rax, %rdi
 movq $4, %rax
 movq %rax, %rsi
 call findMax
 pushq %rax
 popq %rax
 movq %rax, -88(%rbp)
 movq -88(%rbp), %rax
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

