	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 10
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	leaq	-11(%rbp), %rdi
	movl	$0, -4(%rbp)
	movl	L_main.name(%rip), %eax
	movl	%eax, -11(%rbp)
	movw	L_main.name+4(%rip), %cx
	movw	%cx, -7(%rbp)
	movb	L_main.name+6(%rip), %dl
	movb	%dl, -5(%rbp)
	callq	_myprint
	leaq	-11(%rbp), %rdi
	callq	_myprint
	xorl	%eax, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_main.name:                            ## @main.name
	.asciz	"steven"


.subsections_via_symbols
