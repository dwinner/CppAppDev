	.file	"wall_macro.c"
	.text
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "x = %d\12\0"
.LC1:
	.ascii "Evaluating SQUARE(x): \0"
.LC2:
	.ascii "The result is %d.\12\0"
.LC3:
	.ascii "Evaluating SQUARE(2): \0"
.LC4:
	.ascii "Evaluating SQUARE(x+2): \0"
.LC5:
	.ascii "Evaluating 100/SQUARE(2): \0"
.LC6:
	.ascii "x is %d.\12\0"
.LC7:
	.ascii "Evaluating SQUARE(++x): \0"
.LC8:
	.ascii "After incrementing, x is %x.\12\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	call	__main
	movl	$4, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %edx
	leaq	.LC0(%rip), %rcx
	call	printf
	movl	-4(%rbp), %eax
	imull	%eax, %eax
	movl	%eax, -8(%rbp)
	leaq	.LC1(%rip), %rcx
	call	printf
	movl	-8(%rbp), %eax
	movl	%eax, %edx
	leaq	.LC2(%rip), %rcx
	call	printf
	movl	$4, -8(%rbp)
	leaq	.LC3(%rip), %rcx
	call	printf
	movl	-8(%rbp), %eax
	movl	%eax, %edx
	leaq	.LC2(%rip), %rcx
	call	printf
	leaq	.LC4(%rip), %rcx
	call	printf
	movl	-4(%rbp), %eax
	leal	2(%rax), %edx
	movl	-4(%rbp), %eax
	addl	$2, %eax
	imull	%edx, %eax
	movl	%eax, %edx
	leaq	.LC2(%rip), %rcx
	call	printf
	leaq	.LC5(%rip), %rcx
	call	printf
	movl	$25, %edx
	leaq	.LC2(%rip), %rcx
	call	printf
	movl	-4(%rbp), %eax
	movl	%eax, %edx
	leaq	.LC6(%rip), %rcx
	call	printf
	leaq	.LC7(%rip), %rcx
	call	printf
	addl	$1, -4(%rbp)
	addl	$1, -4(%rbp)
	movl	-4(%rbp), %eax
	imull	%eax, %eax
	movl	%eax, %edx
	leaq	.LC2(%rip), %rcx
	call	printf
	movl	-4(%rbp), %eax
	movl	%eax, %edx
	leaq	.LC8(%rip), %rcx
	call	printf
	movl	$0, %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 10.2.0"
	.def	printf;	.scl	2;	.type	32;	.endef
