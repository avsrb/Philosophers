	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	_print                  ## -- Begin function print
	.p2align	4, 0x90
_print:                                 ## @print
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	movq	(%rdi), %rax
	movq	%rax, -32(%rbp)
	movq	8(%rdi), %rax
	movq	%rax, -24(%rbp)
	movq	16(%rdi), %rax
	movq	%rax, -16(%rbp)
	movl	$1000, %edi             ## imm = 0x3E8
	callq	_usleep
	movl	$0, -36(%rbp)
	movl	%eax, -40(%rbp)         ## 4-byte Spill
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$5, -36(%rbp)
	jge	LBB0_4
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	movq	-24(%rbp), %rdi
	callq	_pthread_mutex_lock
	movq	-16(%rbp), %rdi
	movl	%eax, -44(%rbp)         ## 4-byte Spill
	callq	_pthread_mutex_lock
	movl	-32(%rbp), %esi
	leaq	L_.str(%rip), %rdi
	movl	%eax, -48(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	movq	-24(%rbp), %rdi
	movl	%eax, -52(%rbp)         ## 4-byte Spill
	callq	_pthread_mutex_unlock
	movq	-16(%rbp), %rdi
	movl	%eax, -56(%rbp)         ## 4-byte Spill
	callq	_pthread_mutex_unlock
	movl	%eax, -60(%rbp)         ## 4-byte Spill
## %bb.3:                               ##   in Loop: Header=BB0_1 Depth=1
	movl	-36(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -36(%rbp)
	jmp	LBB0_1
LBB0_4:
	leaq	L_.str.1(%rip), %rdi
	movb	$0, %al
	callq	_printf
	xorl	%ecx, %ecx
	movl	%ecx, %edi
	movl	%eax, -64(%rbp)         ## 4-byte Spill
	movq	%rdi, %rax
	addq	$64, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_threads                ## -- Begin function threads
	.p2align	4, 0x90
_threads:                               ## @threads
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$112, %rsp
	movq	_mutex1@GOTPCREL(%rip), %rdi
	xorl	%eax, %eax
	movl	%eax, %esi
	callq	_pthread_mutex_init
	movq	_mutex2@GOTPCREL(%rip), %rdi
	xorl	%ecx, %ecx
	movl	%ecx, %esi
	movl	%eax, -68(%rbp)         ## 4-byte Spill
	callq	_pthread_mutex_init
	xorl	%ecx, %ecx
	movl	%ecx, %esi
	movq	_mutex1@GOTPCREL(%rip), %rdi
	movq	_mutex2@GOTPCREL(%rip), %rdx
	movl	$1, -40(%rbp)
	movq	%rdi, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movl	$2, -64(%rbp)
	movq	%rdx, -56(%rbp)
	movq	%rdi, -48(%rbp)
	leaq	-40(%rbp), %rdx
	leaq	-8(%rbp), %rdi
	leaq	_print(%rip), %r8
	movq	%rdx, -80(%rbp)         ## 8-byte Spill
	movq	%r8, %rdx
	movq	-80(%rbp), %rcx         ## 8-byte Reload
	movl	%eax, -84(%rbp)         ## 4-byte Spill
	callq	_pthread_create
	xorl	%r9d, %r9d
	movl	%r9d, %esi
	leaq	-64(%rbp), %rcx
	leaq	-16(%rbp), %rdi
	leaq	_print(%rip), %rdx
	movl	%eax, -88(%rbp)         ## 4-byte Spill
	callq	_pthread_create
	xorl	%r9d, %r9d
	movl	%r9d, %esi
	movq	-8(%rbp), %rdi
	movl	%eax, -92(%rbp)         ## 4-byte Spill
	callq	_pthread_join
	xorl	%r9d, %r9d
	movl	%r9d, %esi
	movq	-16(%rbp), %rdi
	movl	%eax, -96(%rbp)         ## 4-byte Spill
	callq	_pthread_join
	movl	$1, %edi
	leaq	L_.str.2(%rip), %rsi
	movl	$5, %edx
	movl	%eax, -100(%rbp)        ## 4-byte Spill
	callq	_write
	movq	%rax, -112(%rbp)        ## 8-byte Spill
	addq	$112, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	callq	_threads
	xorl	%eax, %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"Thread = %d\n"

L_.str.1:                               ## @.str.1
	.asciz	"end\n"

	.comm	_mutex1,64,3            ## @mutex1
	.comm	_mutex2,64,3            ## @mutex2
L_.str.2:                               ## @.str.2
	.asciz	"Exit\n"


.subsections_via_symbols
