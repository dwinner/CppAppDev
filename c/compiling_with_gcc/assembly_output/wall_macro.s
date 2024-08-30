	.file	"wall_macro.c"
 # GNU C17 (GCC) version 10.2.0 (x86_64-pc-cygwin)
 #	compiled by GNU C version 10.2.0, GMP version 6.2.0, MPFR version 4.1.0, MPC version 1.1.0, isl version isl-0.22.1-GMP

 # warning: GMP header version 6.2.0 differs from library version 6.2.1.
 # warning: MPC header version 1.1.0 differs from library version 1.2.1.
 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed: 
 # -idirafter /usr/lib/gcc/x86_64-pc-cygwin/10/../../../../lib/../include/w32api
 # -idirafter /usr/lib/gcc/x86_64-pc-cygwin/10/../../../../x86_64-pc-cygwin/lib/../lib/../../include/w32api
 # wall_macro.c -mtune=generic -march=x86-64 -fverbose-asm
 # options enabled:  -faggressive-loop-optimizations -fallocation-dce
 # -fasynchronous-unwind-tables -fauto-inc-dec -fdelete-null-pointer-checks
 # -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-symbols
 # -feliminate-unused-debug-types -ffp-int-builtin-inexact -ffunction-cse
 # -fgcse-lm -fgnu-unique -fident -finline-atomics -fipa-stack-alignment
 # -fira-hoist-pressure -fira-share-save-slots -fira-share-spill-slots
 # -fivopts -fkeep-inline-dllexport -fkeep-static-consts
 # -fleading-underscore -flifetime-dse -fmath-errno -fmerge-debug-strings
 # -fpeephole -fpic -fplt -fprefetch-loop-arrays -freg-struct-return
 # -fsched-critical-path-heuristic -fsched-dep-count-heuristic
 # -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
 # -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
 # -fsched-stalled-insns-dep -fschedule-fusion -fsemantic-interposition
 # -fset-stack-executable -fshow-column -fshrink-wrap-separate
 # -fsigned-zeros -fsplit-ivs-in-unroller -fssa-backprop -fstdarg-opt
 # -fstrict-volatile-bitfields -fsync-libcalls -ftrapping-math
 # -ftree-cselim -ftree-forwprop -ftree-loop-if-convert -ftree-loop-im
 # -ftree-loop-ivcanon -ftree-loop-optimize -ftree-parallelize-loops=
 # -ftree-phiprop -ftree-reassoc -ftree-scev-cprop -funit-at-a-time
 # -funwind-tables -fverbose-asm -fzero-initialized-in-bss
 # -m128bit-long-double -m64 -m80387 -maccumulate-outgoing-args
 # -malign-double -malign-stringops -mavx256-split-unaligned-load
 # -mavx256-split-unaligned-store -mfancy-math-387 -mfentry -mfp-ret-in-387
 # -mfxsr -mieee-fp -mlong-double-80 -mmmx -mno-sse4 -mpush-args -mred-zone
 # -msse -msse2 -mstack-arg-probe -mstackrealign -mvzeroupper

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
	pushq	%rbp	 #
	.seh_pushreg	%rbp
	movq	%rsp, %rbp	 #,
	.seh_setframe	%rbp, 0
	subq	$48, %rsp	 #,
	.seh_stackalloc	48
	.seh_endprologue
 # wall_macro.c:11: {
	call	__main	 #
 # wall_macro.c:12:    int x = 4;
	movl	$4, -4(%rbp)	 #, x
 # wall_macro.c:15:    printf("x = %d\n", x);
	movl	-4(%rbp), %eax	 # x, tmp88
	movl	%eax, %edx	 # tmp88,
	leaq	.LC0(%rip), %rcx	 #,
	call	printf	 #
 # wall_macro.c:16:    z = SQUARE(x);
	movl	-4(%rbp), %eax	 # x, tmp90
	imull	%eax, %eax	 # tmp90, tmp89
	movl	%eax, -8(%rbp)	 # tmp89, z
 # wall_macro.c:17:    printf("Evaluating SQUARE(x): ");
	leaq	.LC1(%rip), %rcx	 #,
	call	printf	 #
 # wall_macro.c:18:    PR(z);
	movl	-8(%rbp), %eax	 # z, tmp91
	movl	%eax, %edx	 # tmp91,
	leaq	.LC2(%rip), %rcx	 #,
	call	printf	 #
 # wall_macro.c:19:    z = SQUARE(2);
	movl	$4, -8(%rbp)	 #, z
 # wall_macro.c:20:    printf("Evaluating SQUARE(2): ");
	leaq	.LC3(%rip), %rcx	 #,
	call	printf	 #
 # wall_macro.c:21:    PR(z);
	movl	-8(%rbp), %eax	 # z, tmp92
	movl	%eax, %edx	 # tmp92,
	leaq	.LC2(%rip), %rcx	 #,
	call	printf	 #
 # wall_macro.c:22:    printf("Evaluating SQUARE(x+2): ");
	leaq	.LC4(%rip), %rcx	 #,
	call	printf	 #
 # wall_macro.c:23:    PR(SQUARE(x + 2));
	movl	-4(%rbp), %eax	 # x, tmp93
	leal	2(%rax), %edx	 #, _1
	movl	-4(%rbp), %eax	 # x, tmp94
	addl	$2, %eax	 #, _2
	imull	%edx, %eax	 # _1, _3
	movl	%eax, %edx	 # _3,
	leaq	.LC2(%rip), %rcx	 #,
	call	printf	 #
 # wall_macro.c:24:    printf("Evaluating 100/SQUARE(2): ");
	leaq	.LC5(%rip), %rcx	 #,
	call	printf	 #
 # wall_macro.c:25:    PR(100 / SQUARE(2));
	movl	$25, %edx	 #,
	leaq	.LC2(%rip), %rcx	 #,
	call	printf	 #
 # wall_macro.c:26:    printf("x is %d.\n", x);
	movl	-4(%rbp), %eax	 # x, tmp95
	movl	%eax, %edx	 # tmp95,
	leaq	.LC6(%rip), %rcx	 #,
	call	printf	 #
 # wall_macro.c:27:    printf("Evaluating SQUARE(++x): ");
	leaq	.LC7(%rip), %rcx	 #,
	call	printf	 #
 # wall_macro.c:28:    PR(SQUARE(++x));  /* Неопределенное поведение - тут даже скобки не спасут */
	addl	$1, -4(%rbp)	 #, x
	addl	$1, -4(%rbp)	 #, x
	movl	-4(%rbp), %eax	 # x, tmp96
	imull	%eax, %eax	 # tmp96, _4
	movl	%eax, %edx	 # _4,
	leaq	.LC2(%rip), %rcx	 #,
	call	printf	 #
 # wall_macro.c:29:    printf("After incrementing, x is %x.\n", x);
	movl	-4(%rbp), %eax	 # x, tmp97
	movl	%eax, %edx	 # tmp97,
	leaq	.LC8(%rip), %rcx	 #,
	call	printf	 #
 # wall_macro.c:31:    return 0;
	movl	$0, %eax	 #, _24
 # wall_macro.c:32: }
	addq	$48, %rsp	 #,
	popq	%rbp	 #
	ret	
	.seh_endproc
	.ident	"GCC: (GNU) 10.2.0"
	.def	printf;	.scl	2;	.type	32;	.endef
