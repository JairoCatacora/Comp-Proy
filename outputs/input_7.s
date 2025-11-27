.section .data
print_fmt: .asciz "%d\n"
.section .text

.globl getAge
getAge:
 pushq %rbp
 movq %rsp, %rbp
 movq %rdi, -8(%rbp)
 movq -8(%rbp), %rax
 jmp .end_getAge
.end_getAge:
 movq %rbp, %rsp
 popq %rbp
 ret

.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
.end_main:
 movq %rbp, %rsp
 popq %rbp
 ret
