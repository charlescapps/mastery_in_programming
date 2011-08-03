	.file	"game_v4.c"
	.text
	.p2align 4,,15
.globl new_game
	.type	new_game, @function
new_game:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %edi
	leal	0(,%eax,4), %ebx
	movl	8(%ebp), %eax
	leal	1(%edi), %edx
	movl	%edx, -32(%ebp)
	imull	%edx, %eax
	addl	%ebx, %eax
	movl	%eax, (%esp)
	call	malloc
	movl	8(%ebp), %edx
	testl	%edx, %edx
	movl	%eax, -28(%ebp)
	jle	.L2
	addl	%eax, %ebx
	xorl	%esi, %esi
	.p2align 4,,7
	.p2align 3
.L3:
	movl	-28(%ebp), %eax
	movl	%ebx, (%eax,%esi,4)
	addl	$1, %esi
	movl	%ebx, (%esp)
	movl	%edi, 8(%esp)
	movl	$32, 4(%esp)
	call	memset
	movb	$0, (%ebx,%edi)
	addl	-32(%ebp), %ebx
	cmpl	%esi, 8(%ebp)
	jg	.L3
.L2:
	movl	$12, (%esp)
	call	malloc
	movl	-28(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	8(%ebp), %edx
	movl	%edi, 4(%eax)
	movl	%edx, (%eax)
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	new_game, .-new_game
	.p2align 4,,15
.globl clone_game
	.type	clone_game, @function
clone_game:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	movl	8(%ebp), %edi
	movl	4(%edi), %eax
	movl	%eax, -40(%ebp)
	movl	(%edi), %eax
	movl	%eax, -28(%ebp)
	leal	0(,%eax,4), %ebx
	movl	-40(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -36(%ebp)
	imull	-28(%ebp), %eax
	addl	%ebx, %eax
	movl	%eax, (%esp)
	call	malloc
	movl	-28(%ebp), %esi
	testl	%esi, %esi
	movl	%eax, -32(%ebp)
	movl	%eax, %edx
	jle	.L7
	movl	%edi, -48(%ebp)
	movl	-40(%ebp), %edi
	addl	%eax, %ebx
	xorl	%esi, %esi
	movl	%eax, -44(%ebp)
	.p2align 4,,7
	.p2align 3
.L8:
	movl	-32(%ebp), %eax
	movl	%ebx, (%eax,%esi,4)
	addl	$1, %esi
	movl	%ebx, (%esp)
	movl	%edi, 8(%esp)
	movl	$32, 4(%esp)
	call	memset
	movb	$0, (%ebx,%edi)
	addl	-36(%ebp), %ebx
	cmpl	%esi, -28(%ebp)
	jg	.L8
	movl	-44(%ebp), %edx
	movl	-48(%ebp), %edi
.L7:
	movl	%edx, -52(%ebp)
	movl	$12, (%esp)
	call	malloc
	movl	-52(%ebp), %edx
	movl	%eax, %ebx
	movl	-32(%ebp), %eax
	movl	%eax, 8(%ebx)
	movl	-28(%ebp), %eax
	movl	%eax, (%ebx)
	movl	(%edi), %ecx
	movl	-40(%ebp), %eax
	testl	%ecx, %ecx
	movl	%eax, 4(%ebx)
	jle	.L9
	xorl	%esi, %esi
	jmp	.L10
	.p2align 4,,7
	.p2align 3
.L13:
	movl	8(%ebx), %edx
.L10:
	movl	8(%edi), %eax
	movl	(%eax,%esi,4), %eax
	movl	%eax, 4(%esp)
	movl	(%edx,%esi,4), %eax
	addl	$1, %esi
	movl	%eax, (%esp)
	call	strcpy
	cmpl	%esi, (%edi)
	jg	.L13
.L9:
	addl	$60, %esp
	movl	%ebx, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	clone_game, .-clone_game
	.p2align 4,,15
.globl free_game
	.type	free_game, @function
free_game:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	movl	8(%ebp), %ebx
	movl	8(%ebx), %eax
	movl	%eax, (%esp)
	call	free
	movl	%ebx, 8(%ebp)
	addl	$20, %esp
	popl	%ebx
	popl	%ebp
	jmp	free
	.size	free_game, .-free_game
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"+%s+\n"
.LC1:
	.string	"|%s|\n"
	.text
	.p2align 4,,15
.globl print_game
	.type	print_game, @function
print_game:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	8(%ebp), %esi
	movl	%gs:20, %eax
	movl	%eax, -28(%ebp)
	xorl	%eax, %eax
	movl	4(%esi), %edx
	leal	31(%edx), %eax
	andl	$-16, %eax
	subl	%eax, %esp
	leal	27(%esp), %edi
	andl	$-16, %edi
	movl	%edx, 8(%esp)
	movl	$45, 4(%esp)
	movl	%edi, (%esp)
	call	memset
	movl	4(%esi), %eax
	movb	$0, (%edi,%eax)
	movl	%edi, 8(%esp)
	movl	$.LC0, 4(%esp)
	movl	$1, (%esp)
	call	__printf_chk
	movl	(%esi), %eax
	testl	%eax, %eax
	jle	.L16
	xorl	%ebx, %ebx
	.p2align 4,,7
	.p2align 3
.L17:
	movl	8(%esi), %eax
	movl	(%eax,%ebx,4), %eax
	addl	$1, %ebx
	movl	$.LC1, 4(%esp)
	movl	$1, (%esp)
	movl	%eax, 8(%esp)
	call	__printf_chk
	cmpl	%ebx, (%esi)
	jg	.L17
.L16:
	movl	%edi, 8(%esp)
	movl	$.LC0, 4(%esp)
	movl	$1, (%esp)
	call	__printf_chk
	movl	-28(%ebp), %eax
	xorl	%gs:20, %eax
	jne	.L20
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
.L20:
	call	__stack_chk_fail
	.size	print_game, .-print_game
	.p2align 4,,15
.globl evolve_torus
	.type	evolve_torus, @function
evolve_torus:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$76, %esp
	movl	8(%ebp), %eax
	movl	4(%eax), %edi
	movl	(%eax), %edx
	leal	1(%edi), %ecx
	movl	%ecx, %eax
	imull	%edx, %eax
	leal	0(,%edx,4), %ebx
	movl	%edx, -32(%ebp)
	movl	%ecx, -40(%ebp)
	addl	%ebx, %eax
	movl	%eax, (%esp)
	call	malloc
	cmpl	$0, -32(%ebp)
	movl	%eax, -36(%ebp)
	jle	.L22
	addl	%eax, %ebx
	xorl	%esi, %esi
	.p2align 4,,7
	.p2align 3
.L23:
	movl	-36(%ebp), %eax
	movl	%ebx, (%eax,%esi,4)
	addl	$1, %esi
	movl	%ebx, (%esp)
	movl	%edi, 8(%esp)
	movl	$32, 4(%esp)
	call	memset
	movb	$0, (%ebx,%edi)
	addl	-40(%ebp), %ebx
	cmpl	%esi, -32(%ebp)
	jg	.L23
.L22:
	movl	$12, (%esp)
	call	malloc
	movl	-32(%ebp), %ecx
	movl	8(%ebp), %ebx
	movl	-36(%ebp), %edx
	movl	%ecx, (%eax)
	cmpl	$0, (%ebx)
	movl	%eax, -56(%ebp)
	movl	%edx, 8(%eax)
	movl	%edi, 4(%eax)
	jle	.L24
	movl	8(%ebp), %esi
	xorl	%ebx, %ebx
	movl	%eax, %edi
	.p2align 4,,7
	.p2align 3
.L25:
	movl	8(%esi), %eax
	movl	(%eax,%ebx,4), %eax
	movl	%eax, 4(%esp)
	movl	8(%edi), %eax
	movl	(%eax,%ebx,4), %eax
	addl	$1, %ebx
	movl	%eax, (%esp)
	call	strcpy
	movl	(%esi), %ecx
	cmpl	%ecx, %ebx
	jl	.L25
	testl	%ecx, %ecx
	jle	.L24
	movl	8(%ebp), %eax
	movl	$0, -44(%ebp)
	movl	-44(%ebp), %ebx
	movl	$-1, -36(%ebp)
	movl	4(%eax), %eax
	movl	%eax, -32(%ebp)
	movl	-44(%ebp), %eax
	.p2align 4,,7
	.p2align 3
.L26:
	addl	$1, %ebx
	xorl	%edx, %edx
	movl	%ebx, -40(%ebp)
	sall	$2, %eax
	movl	$-1, %ebx
	movl	%eax, -52(%ebp)
	movl	%ebx, -60(%ebp)
	jmp	.L60
	.p2align 4,,7
	.p2align 3
.L27:
	movl	-36(%ebp), %eax
	movl	-60(%ebp), %edi
	subl	%ecx, %eax
	cmpl	-36(%ebp), %ecx
	cmovg	-36(%ebp), %eax
	testl	%edi, %edi
	js	.L77
.L29:
	movl	-60(%ebp), %edi
	movl	-32(%ebp), %ebx
	subl	-32(%ebp), %edi
	cmpl	%ebx, -60(%ebp)
	cmovl	-60(%ebp), %edi
.L30:
	movl	(%esi,%eax,4), %eax
	movl	-36(%ebp), %ebx
	cmpb	$79, (%eax,%edi)
	sete	%al
	testl	%ebx, %ebx
	movzbl	%al, %eax
	js	.L78
	movl	-36(%ebp), %edi
	subl	%ecx, %edi
	cmpl	-36(%ebp), %ecx
	cmovg	-36(%ebp), %edi
.L32:
	movl	(%esi,%edi,4), %edi
	xorl	%ebx, %ebx
	movl	%edx, -48(%ebp)
	cmpb	$79, (%edi,%edx)
	sete	%bl
	addl	$1, %edx
	movl	%ebx, %edi
	addl	%edi, %eax
	movl	-36(%ebp), %edi
	testl	%edi, %edi
	js	.L79
	movl	-36(%ebp), %edi
	subl	%ecx, %edi
	cmpl	-36(%ebp), %ecx
	cmovg	-36(%ebp), %edi
.L35:
	testl	%edx, %edx
	js	.L80
	movl	%edx, %ebx
	subl	-32(%ebp), %ebx
	cmpl	%edx, -32(%ebp)
	cmovg	%edx, %ebx
	movl	%ebx, -28(%ebp)
.L37:
	movl	(%esi,%edi,4), %edi
	cmpb	$79, (%edi,%ebx)
	movl	-44(%ebp), %edi
	sete	%bl
	movzbl	%bl, %ebx
	addl	%ebx, %eax
	movl	-60(%ebp), %ebx
	subl	%ecx, %edi
	cmpl	%ecx, -44(%ebp)
	cmovl	-44(%ebp), %edi
	testl	%ebx, %ebx
	js	.L81
	movl	-60(%ebp), %ebx
	subl	-32(%ebp), %ebx
	movl	%ebx, -28(%ebp)
	movl	-32(%ebp), %ebx
	cmpl	%ebx, -60(%ebp)
	movl	-60(%ebp), %ebx
	cmovge	-28(%ebp), %ebx
	movl	%ebx, -28(%ebp)
.L41:
	movl	(%esi,%edi,4), %edi
	cmpb	$79, (%edi,%ebx)
	movl	-44(%ebp), %edi
	sete	%bl
	movzbl	%bl, %ebx
	subl	%ecx, %edi
	addl	%ebx, %eax
	cmpl	%ecx, -44(%ebp)
	cmovl	-44(%ebp), %edi
	testl	%edx, %edx
	js	.L82
	movl	%edx, %ebx
	subl	-32(%ebp), %ebx
	cmpl	%edx, -32(%ebp)
	cmovg	%edx, %ebx
	movl	%ebx, -28(%ebp)
.L45:
	movl	(%esi,%edi,4), %edi
	cmpb	$79, (%edi,%ebx)
	movl	-40(%ebp), %edi
	sete	%bl
	movzbl	%bl, %ebx
	addl	%ebx, %eax
	movl	-60(%ebp), %ebx
	subl	%ecx, %edi
	cmpl	-40(%ebp), %ecx
	cmovg	-40(%ebp), %edi
	testl	%ebx, %ebx
	js	.L83
	movl	-60(%ebp), %ebx
	subl	-32(%ebp), %ebx
	movl	%ebx, -28(%ebp)
	movl	-32(%ebp), %ebx
	cmpl	%ebx, -60(%ebp)
	movl	-60(%ebp), %ebx
	cmovge	-28(%ebp), %ebx
	movl	%ebx, -28(%ebp)
.L49:
	movl	(%esi,%edi,4), %edi
	cmpb	$79, (%edi,%ebx)
	movl	-40(%ebp), %edi
	sete	%bl
	movzbl	%bl, %ebx
	addl	%ebx, %eax
	movl	-40(%ebp), %ebx
	subl	%ecx, %ebx
	cmpl	-40(%ebp), %ecx
	movl	%ebx, -28(%ebp)
	cmovle	%ebx, %edi
	movl	-48(%ebp), %ebx
	movl	(%esi,%edi,4), %edi
	cmpb	$79, (%edi,%ebx)
	movl	-40(%ebp), %edi
	sete	%bl
	movzbl	%bl, %ebx
	addl	%ebx, %eax
	cmpl	-40(%ebp), %ecx
	cmovle	-28(%ebp), %edi
	testl	%edx, %edx
	js	.L84
	movl	%edx, %ebx
	subl	-32(%ebp), %ebx
	cmpl	%edx, -32(%ebp)
	cmovg	%edx, %ebx
	movl	%ebx, -28(%ebp)
.L55:
	movl	(%esi,%edi,4), %edi
	cmpb	$79, (%edi,%ebx)
	sete	%bl
	movzbl	%bl, %ebx
	addl	%ebx, %eax
	movl	-52(%ebp), %ebx
	movl	(%esi,%ebx), %esi
	movl	-48(%ebp), %ebx
	cmpb	$79, (%esi,%ebx)
	je	.L85
	cmpl	$3, %eax
	je	.L86
.L58:
	addl	$1, -60(%ebp)
.L60:
	cmpl	-32(%ebp), %edx
	jge	.L87
	movl	-36(%ebp), %eax
	movl	8(%ebp), %ebx
	testl	%eax, %eax
	movl	8(%ebx), %esi
	jns	.L27
	movl	-60(%ebp), %edi
	movl	-36(%ebp), %eax
	testl	%edi, %edi
	leal	(%ecx,%eax), %eax
	jns	.L29
.L77:
	movl	-60(%ebp), %edi
	addl	-32(%ebp), %edi
	jmp	.L30
	.p2align 4,,7
	.p2align 3
.L85:
	subl	$2, %eax
	cmpl	$1, %eax
	jbe	.L58
	movl	-56(%ebp), %ecx
	movl	-52(%ebp), %ebx
	movl	8(%ecx), %eax
	movl	-48(%ebp), %ecx
	movl	(%eax,%ebx), %eax
	movb	$32, (%eax,%ecx)
.L76:
	movl	8(%ebp), %ebx
	movl	8(%ebp), %eax
	movl	4(%ebx), %ebx
	movl	(%eax), %ecx
	movl	%ebx, -32(%ebp)
	jmp	.L58
	.p2align 4,,7
	.p2align 3
.L86:
	movl	-56(%ebp), %ecx
	movl	-52(%ebp), %ebx
	movl	8(%ecx), %eax
	movl	-48(%ebp), %ecx
	movl	(%eax,%ebx), %eax
	movb	$79, (%eax,%ecx)
	jmp	.L76
	.p2align 4,,7
	.p2align 3
.L84:
	movl	-32(%ebp), %ebx
	addl	%edx, %ebx
	movl	%ebx, -28(%ebp)
	jmp	.L55
	.p2align 4,,7
	.p2align 3
.L83:
	movl	-32(%ebp), %ebx
	addl	-60(%ebp), %ebx
	movl	%ebx, -28(%ebp)
	jmp	.L49
	.p2align 4,,7
	.p2align 3
.L82:
	movl	-32(%ebp), %ebx
	addl	%edx, %ebx
	movl	%ebx, -28(%ebp)
	jmp	.L45
	.p2align 4,,7
	.p2align 3
.L81:
	movl	-32(%ebp), %ebx
	addl	-60(%ebp), %ebx
	movl	%ebx, -28(%ebp)
	jmp	.L41
	.p2align 4,,7
	.p2align 3
.L80:
	movl	-32(%ebp), %ebx
	addl	%edx, %ebx
	movl	%ebx, -28(%ebp)
	jmp	.L37
	.p2align 4,,7
	.p2align 3
.L79:
	movl	-36(%ebp), %edi
	leal	(%ecx,%edi), %edi
	jmp	.L35
	.p2align 4,,7
	.p2align 3
.L78:
	movl	-36(%ebp), %edi
	leal	(%ecx,%edi), %edi
	jmp	.L32
	.p2align 4,,7
	.p2align 3
.L87:
	addl	$1, -36(%ebp)
	cmpl	%ecx, -40(%ebp)
	jge	.L24
	movl	-40(%ebp), %edx
	movl	%edx, -44(%ebp)
	movl	%edx, %ebx
	movl	%edx, %eax
	jmp	.L26
.L24:
	movl	-56(%ebp), %eax
	addl	$76, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	evolve_torus, .-evolve_torus
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align 4
.LC2:
	.string	"Invalid row or col passed to neighbors function."
	.text
	.p2align 4,,15
.globl neighbors
	.type	neighbors, @function
neighbors:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	12(%ebp), %eax
	movl	8(%ebp), %ecx
	movl	16(%ebp), %edi
	testl	%eax, %eax
	js	.L89
	movl	%edi, %eax
	movl	(%ecx), %edx
	shrl	$31, %eax
	testb	%al, %al
	jne	.L89
	cmpl	12(%ebp), %edx
	jle	.L89
	movl	4(%ecx), %eax
	cmpl	%eax, %edi
	jge	.L89
	movl	8(%ecx), %ecx
	movl	12(%ebp), %esi
	movl	12(%ebp), %ebx
	movl	%ecx, -36(%ebp)
	xorl	%ecx, %ecx
	subl	$1, %ebx
	testl	%esi, %esi
	movl	%ecx, %esi
	cmovg	%ebx, %esi
	movl	12(%ebp), %ebx
	addl	$1, %ebx
	movl	%ebx, -32(%ebp)
	leal	-1(%edx), %ebx
	cmpl	-32(%ebp), %edx
	leal	-1(%edi), %edx
	cmovg	-32(%ebp), %ebx
	testl	%edi, %edi
	cmovg	%edx, %ecx
	movl	%ecx, -28(%ebp)
	leal	1(%edi), %ecx
	cmpl	%ecx, %eax
	leal	-1(%eax), %edx
	cmovle	%edx, %ecx
	xorl	%eax, %eax
	cmpl	%ebx, %esi
	movl	%ebx, -32(%ebp)
	jg	.L91
	.p2align 4,,7
	.p2align 3
.L105:
	cmpl	%ecx, -28(%ebp)
	jg	.L101
	movl	-36(%ebp), %edx
	movl	(%edx,%esi,4), %ebx
	movl	-28(%ebp), %edx
	jmp	.L99
	.p2align 4,,7
	.p2align 3
.L97:
	addl	$1, %edx
	cmpl	%edx, %ecx
	jl	.L101
.L99:
	cmpb	$79, (%ebx,%edx)
	jne	.L97
	cmpl	%edi, %edx
	jne	.L104
	cmpl	12(%ebp), %esi
	.p2align 4,,2
	je	.L97
.L104:
	addl	$1, %edx
	addl	$1, %eax
	cmpl	%edx, %ecx
	jge	.L99
	.p2align 4,,7
	.p2align 3
.L101:
	addl	$1, %esi
	cmpl	%esi, -32(%ebp)
	jge	.L105
.L91:
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
.L89:
	movl	$.LC2, (%esp)
	call	puts
	orl	$-1, %eax
	jmp	.L91
	.size	neighbors, .-neighbors
	.p2align 4,,15
.globl evolve
	.type	evolve, @function
evolve:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	movl	8(%ebp), %esi
	movl	4(%esi), %eax
	movl	(%esi), %edx
	movl	%eax, -40(%ebp)
	addl	$1, %eax
	movl	%eax, -32(%ebp)
	imull	%edx, %eax
	leal	0(,%edx,4), %ebx
	movl	%edx, -28(%ebp)
	addl	%ebx, %eax
	movl	%eax, (%esp)
	call	malloc
	movl	-28(%ebp), %ecx
	testl	%ecx, %ecx
	movl	%eax, -36(%ebp)
	movl	%eax, %edi
	jle	.L111
	movl	-40(%ebp), %edi
	xorl	%edx, %edx
	addl	%eax, %ebx
	movl	%esi, -48(%ebp)
	movl	%edx, %esi
	movl	%eax, -44(%ebp)
	.p2align 4,,7
	.p2align 3
.L112:
	movl	-36(%ebp), %eax
	movl	%ebx, (%eax,%esi,4)
	addl	$1, %esi
	movl	%ebx, (%esp)
	movl	%edi, 8(%esp)
	movl	$32, 4(%esp)
	call	memset
	movb	$0, (%ebx,%edi)
	addl	-32(%ebp), %ebx
	cmpl	%esi, -28(%ebp)
	jg	.L112
	movl	-44(%ebp), %edi
	movl	-48(%ebp), %esi
.L111:
	movl	$12, (%esp)
	call	malloc
	movl	-36(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	-28(%ebp), %edx
	movl	%eax, -32(%ebp)
	movl	%edx, (%eax)
	movl	-40(%ebp), %edx
	movl	%edx, 4(%eax)
	movl	(%esi), %edx
	testl	%edx, %edx
	jle	.L113
	movl	%edi, %edx
	xorl	%ebx, %ebx
	movl	%eax, %edi
	jmp	.L115
	.p2align 4,,7
	.p2align 3
.L123:
	movl	8(%edi), %edx
.L115:
	movl	8(%esi), %eax
	movl	(%eax,%ebx,4), %eax
	movl	%eax, 4(%esp)
	movl	(%edx,%ebx,4), %eax
	addl	$1, %ebx
	movl	%eax, (%esp)
	call	strcpy
	movl	(%esi), %edx
	cmpl	%edx, %ebx
	jl	.L123
	testl	%edx, %edx
	jle	.L113
	movl	4(%esi), %eax
	movl	$0, -28(%ebp)
	.p2align 4,,7
	.p2align 3
.L116:
	testl	%eax, %eax
	jle	.L120
	movl	-28(%ebp), %eax
	xorl	%ebx, %ebx
	leal	0(,%eax,4), %edi
	jmp	.L119
	.p2align 4,,7
	.p2align 3
.L117:
	cmpl	$3, %eax
	je	.L124
.L118:
	movl	4(%esi), %eax
	addl	$1, %ebx
	cmpl	%ebx, %eax
	jle	.L125
.L119:
	movl	-28(%ebp), %eax
	movl	%ebx, 8(%esp)
	movl	%esi, (%esp)
	movl	%eax, 4(%esp)
	call	neighbors
	movl	8(%esi), %edx
	movl	(%edx,%edi), %edx
	cmpb	$79, (%edx,%ebx)
	jne	.L117
	subl	$2, %eax
	cmpl	$1, %eax
	jbe	.L118
	movl	-32(%ebp), %edx
	movl	8(%edx), %eax
	movl	(%eax,%edi), %eax
	movb	$32, (%eax,%ebx)
	movl	4(%esi), %eax
	addl	$1, %ebx
	cmpl	%ebx, %eax
	jg	.L119
.L125:
	movl	(%esi), %edx
.L120:
	addl	$1, -28(%ebp)
	cmpl	%edx, -28(%ebp)
	jl	.L116
.L113:
	movl	-32(%ebp), %eax
	addl	$60, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L124:
	movl	-32(%ebp), %edx
	movl	8(%edx), %eax
	movl	(%eax,%edi), %eax
	movb	$79, (%eax,%ebx)
	jmp	.L118
	.size	evolve, .-evolve
	.p2align 4,,15
.globl neighbors_torus
	.type	neighbors_torus, @function
neighbors_torus:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %edi
	movl	16(%ebp), %esi
	movl	4(%eax), %ecx
	movl	(%eax), %edx
	addl	$1, %edi
	movl	8(%eax), %eax
	movl	%ecx, -40(%ebp)
	movl	12(%ebp), %ecx
	movl	%eax, -32(%ebp)
	xorl	%eax, %eax
	subl	$1, %ecx
	cmpl	%edi, %ecx
	jg	.L127
	cmpl	%ecx, 12(%ebp)
	leal	-1(%esi), %ebx
	leal	1(%esi), %edi
	sete	-16(%ebp)
	testl	%ecx, %ecx
	leal	(%ecx,%edx), %eax
	movl	%ebx, -20(%ebp)
	movl	%edi, -24(%ebp)
	js	.L129
	movl	%ecx, %eax
	subl	%edx, %eax
	cmpl	%ecx, %edx
	cmovg	%ecx, %eax
.L129:
	movl	-20(%ebp), %ebx
	testl	%ebx, %ebx
	js	.L202
	movl	-20(%ebp), %ebx
	movl	-20(%ebp), %edi
	subl	-40(%ebp), %edi
	cmpl	%ebx, -40(%ebp)
	cmovle	%edi, %ebx
.L131:
	movl	-32(%ebp), %edi
	movl	(%edi,%eax,4), %eax
	cmpb	$79, (%eax,%ebx)
	sete	%al
	cmpb	$0, -16(%ebp)
	movzbl	%al, %eax
	movl	%eax, %edi
	je	.L203
.L132:
	testl	%ecx, %ecx
	leal	(%ecx,%edx), %ebx
	js	.L138
	movl	%ecx, %edi
	movl	%ecx, %ebx
	subl	%edx, %edi
	cmpl	%ecx, %edx
	cmovle	%edi, %ebx
.L138:
	movl	-24(%ebp), %edi
	testl	%edi, %edi
	js	.L204
	movl	-24(%ebp), %edi
	subl	-40(%ebp), %edi
	movl	%edi, -16(%ebp)
	movl	-24(%ebp), %edi
	cmpl	%edi, -40(%ebp)
	cmovle	-16(%ebp), %edi
	movl	%edi, -16(%ebp)
.L140:
	movl	-32(%ebp), %edi
	movl	(%edi,%ebx,4), %ebx
	movl	-16(%ebp), %edi
	cmpb	$79, (%ebx,%edi)
	sete	%bl
	addl	$1, %ecx
	movzbl	%bl, %ebx
	addl	%ebx, %eax
	cmpl	%ecx, 12(%ebp)
	leal	(%ecx,%edx), %edi
	sete	-16(%ebp)
	testl	%ecx, %ecx
	js	.L143
	movl	%ecx, %edi
	subl	%edx, %edi
	cmpl	%ecx, %edx
	cmovg	%ecx, %edi
.L143:
	movl	-20(%ebp), %ebx
	testl	%ebx, %ebx
	js	.L205
	movl	-20(%ebp), %ebx
	subl	-40(%ebp), %ebx
	movl	%ebx, -36(%ebp)
	movl	-20(%ebp), %ebx
	cmpl	%ebx, -40(%ebp)
	cmovle	-36(%ebp), %ebx
	movl	%ebx, -36(%ebp)
.L145:
	movl	-32(%ebp), %ebx
	movl	(%ebx,%edi,4), %edi
	movl	-36(%ebp), %ebx
	cmpb	$79, (%edi,%ebx)
	sete	%bl
	movzbl	%bl, %ebx
	addl	%ebx, %eax
	cmpb	$0, -16(%ebp)
	je	.L206
.L147:
	testl	%ecx, %ecx
	leal	(%ecx,%edx), %edi
	js	.L153
	movl	%ecx, %edi
	subl	%edx, %edi
	cmpl	%ecx, %edx
	cmovg	%ecx, %edi
.L153:
	movl	-24(%ebp), %ebx
	testl	%ebx, %ebx
	js	.L207
	movl	-24(%ebp), %ebx
	subl	-40(%ebp), %ebx
	movl	%ebx, -16(%ebp)
	movl	-24(%ebp), %ebx
	cmpl	%ebx, -40(%ebp)
	cmovle	-16(%ebp), %ebx
	movl	%ebx, -16(%ebp)
.L155:
	movl	-32(%ebp), %ebx
	movl	(%ebx,%edi,4), %edi
	movl	-16(%ebp), %ebx
	cmpb	$79, (%edi,%ebx)
	sete	%bl
	addl	$1, %ecx
	movzbl	%bl, %ebx
	addl	%ebx, %eax
	cmpl	%ecx, 12(%ebp)
	leal	(%edx,%ecx), %edi
	sete	-25(%ebp)
	testl	%ecx, %ecx
	js	.L163
	movl	%ecx, %edi
	subl	%edx, %edi
	cmpl	%ecx, %edx
	cmovg	%ecx, %edi
.L163:
	movl	-20(%ebp), %ebx
	testl	%ebx, %ebx
	js	.L208
	movl	-20(%ebp), %ebx
	subl	-40(%ebp), %ebx
	movl	%ebx, -16(%ebp)
	movl	-20(%ebp), %ebx
	cmpl	%ebx, -40(%ebp)
	cmovle	-16(%ebp), %ebx
	movl	%ebx, -20(%ebp)
.L162:
	movl	-32(%ebp), %ebx
	movl	(%ebx,%edi,4), %edi
	movl	-20(%ebp), %ebx
	cmpb	$79, (%edi,%ebx)
	sete	%bl
	movzbl	%bl, %ebx
	addl	%ebx, %eax
	cmpb	$0, -25(%ebp)
	je	.L209
.L164:
	testl	%ecx, %ecx
	leal	(%edx,%ecx), %esi
	js	.L177
	movl	%ecx, %esi
	subl	%edx, %esi
	cmpl	%ecx, %edx
	cmovg	%ecx, %esi
.L177:
	movl	-24(%ebp), %ebx
	testl	%ebx, %ebx
	js	.L210
	movl	-24(%ebp), %ebx
	movl	-24(%ebp), %edx
	subl	-40(%ebp), %edx
	cmpl	%ebx, -40(%ebp)
	cmovg	%ebx, %edx
	movl	%edx, -24(%ebp)
	movl	%edx, %ecx
.L176:
	movl	-32(%ebp), %edi
	movl	(%edi,%esi,4), %edx
	cmpb	$79, (%edx,%ecx)
	sete	%dl
	movzbl	%dl, %edx
	addl	%edx, %eax
.L127:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L209:
	testl	%ecx, %ecx
	leal	(%edx,%ecx), %edi
	js	.L170
	movl	%ecx, %edi
	subl	%edx, %edi
	cmpl	%ecx, %edx
	cmovg	%ecx, %edi
.L170:
	movl	-40(%ebp), %ebx
	addl	%esi, %ebx
	testl	%esi, %esi
	movl	%ebx, -20(%ebp)
	js	.L169
	movl	%esi, %ebx
	subl	-40(%ebp), %ebx
	cmpl	%esi, -40(%ebp)
	cmovle	%ebx, %esi
	movl	%esi, -20(%ebp)
.L169:
	movl	-32(%ebp), %ebx
	movl	(%ebx,%edi,4), %esi
	xorl	%ebx, %ebx
	movl	-20(%ebp), %edi
	cmpb	$79, (%esi,%edi)
	sete	%bl
	movl	%ebx, %esi
	addl	%esi, %eax
	jmp	.L164
	.p2align 4,,7
	.p2align 3
.L203:
	testl	%ecx, %ecx
	leal	(%ecx,%edx), %ebx
	js	.L134
	movl	%ecx, %eax
	movl	%ecx, %ebx
	subl	%edx, %eax
	cmpl	%ecx, %edx
	cmovle	%eax, %ebx
.L134:
	testl	%esi, %esi
	js	.L211
	movl	%esi, %eax
	subl	-40(%ebp), %eax
	cmpl	%esi, -40(%ebp)
	cmovg	%esi, %eax
	movl	%eax, -36(%ebp)
.L136:
	movl	-32(%ebp), %eax
	movl	(%eax,%ebx,4), %ebx
	leal	1(%edi), %eax
	movl	%eax, -16(%ebp)
	movl	-36(%ebp), %eax
	cmpb	$79, (%ebx,%eax)
	movl	-16(%ebp), %eax
	cmovne	%edi, %eax
	jmp	.L132
	.p2align 4,,7
	.p2align 3
.L206:
	testl	%ecx, %ecx
	leal	(%ecx,%edx), %edi
	js	.L149
	movl	%ecx, %edi
	subl	%edx, %edi
	cmpl	%ecx, %edx
	cmovg	%ecx, %edi
.L149:
	testl	%esi, %esi
	js	.L212
	movl	%esi, %ebx
	subl	-40(%ebp), %ebx
	cmpl	%esi, -40(%ebp)
	cmovg	%esi, %ebx
	movl	%ebx, -16(%ebp)
.L151:
	movl	-32(%ebp), %ebx
	movl	(%ebx,%edi,4), %edi
	movl	-16(%ebp), %ebx
	cmpb	$79, (%edi,%ebx)
	sete	%bl
	movzbl	%bl, %ebx
	addl	%ebx, %eax
	jmp	.L147
	.p2align 4,,7
	.p2align 3
.L202:
	movl	-20(%ebp), %ebx
	addl	-40(%ebp), %ebx
	jmp	.L131
	.p2align 4,,7
	.p2align 3
.L212:
	movl	-40(%ebp), %ebx
	addl	%esi, %ebx
	movl	%ebx, -16(%ebp)
	jmp	.L151
	.p2align 4,,7
	.p2align 3
.L211:
	movl	-40(%ebp), %eax
	addl	%esi, %eax
	movl	%eax, -36(%ebp)
	jmp	.L136
	.p2align 4,,7
	.p2align 3
.L210:
	movl	-40(%ebp), %edi
	addl	%edi, -24(%ebp)
	movl	-24(%ebp), %ecx
	jmp	.L176
	.p2align 4,,7
	.p2align 3
.L208:
	movl	-40(%ebp), %ebx
	addl	%ebx, -20(%ebp)
	jmp	.L162
	.p2align 4,,7
	.p2align 3
.L207:
	movl	-24(%ebp), %ebx
	addl	-40(%ebp), %ebx
	movl	%ebx, -16(%ebp)
	jmp	.L155
	.p2align 4,,7
	.p2align 3
.L205:
	movl	-20(%ebp), %ebx
	addl	-40(%ebp), %ebx
	movl	%ebx, -36(%ebp)
	jmp	.L145
	.p2align 4,,7
	.p2align 3
.L204:
	movl	-24(%ebp), %edi
	addl	-40(%ebp), %edi
	movl	%edi, -16(%ebp)
	jmp	.L140
	.size	neighbors_torus, .-neighbors_torus
.globl ALIVE
	.section	.rodata
	.type	ALIVE, @object
	.size	ALIVE, 1
ALIVE:
	.byte	79
.globl DEAD
	.type	DEAD, @object
	.size	DEAD, 1
DEAD:
	.byte	32
.globl INPUT_FILE_ALIVE
	.section	.rodata.str1.1
.LC3:
	.string	"O"
	.data
	.align 4
	.type	INPUT_FILE_ALIVE, @object
	.size	INPUT_FILE_ALIVE, 4
INPUT_FILE_ALIVE:
	.long	.LC3
.globl INPUT_FILE_DEAD
	.section	.rodata.str1.1
.LC4:
	.string	"X"
	.data
	.align 4
	.type	INPUT_FILE_DEAD, @object
	.size	INPUT_FILE_DEAD, 4
INPUT_FILE_DEAD:
	.long	.LC4
	.ident	"GCC: (Ubuntu/Linaro 4.5.2-8ubuntu4) 4.5.2"
	.section	.note.GNU-stack,"",@progbits
