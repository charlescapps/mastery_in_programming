	.file	"main.c"
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align 4
.LC0:
	.string	"Reached end-of-file before reading in %d rows.\n"
	.align 4
.LC1:
	.string	"Number of columns in file does not match given arg!"
	.text
	.p2align 4,,15
.globl game_from_file
	.type	game_from_file, @function
game_from_file:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$1100, %esp
	movl	8(%ebp), %eax
	movl	%gs:20, %edx
	movl	%edx, -28(%ebp)
	xorl	%edx, %edx
	movl	16(%ebp), %edx
	movl	%eax, -52(%ebp)
	leal	27(%esp), %eax
	andl	$-16, %eax
	movl	%eax, -48(%ebp)
	movl	12(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	new_game
	movl	%eax, %ebx
	movl	12(%ebp), %eax
	testl	%eax, %eax
	jle	.L2
	movzbl	DEAD, %edi
	movl	$0, -44(%ebp)
	.p2align 4,,7
	.p2align 3
.L8:
	movl	-52(%ebp), %edx
	movl	-48(%ebp), %eax
	movl	$1025, 4(%esp)
	movl	%edx, 8(%esp)
	movl	%eax, (%esp)
	call	fgets
	testl	%eax, %eax
	je	.L12
	movl	-48(%ebp), %eax
	movl	%eax, (%esp)
	call	strlen
	movl	-48(%ebp), %edx
	cmpb	$10, -1(%eax,%edx)
	je	.L13
	cmpl	%eax, 16(%ebp)
	jne	.L14
.L5:
	movl	-44(%ebp), %eax
	movl	-48(%ebp), %edx
	leal	0(,%eax,4), %esi
	movl	%edx, 4(%esp)
	movl	-44(%ebp), %edx
	movl	8(%ebx), %eax
	movl	(%eax,%edx,4), %eax
	movl	%eax, (%esp)
	call	strcpy
	jmp	.L6
	.p2align 4,,7
	.p2align 3
.L7:
	movl	%edi, %edx
	movb	%dl, (%eax)
.L6:
	movl	INPUT_FILE_DEAD, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebx), %eax
	movl	(%eax,%esi), %eax
	movl	%eax, (%esp)
	call	strstr
	testl	%eax, %eax
	jne	.L7
	addl	$1, -44(%ebp)
	movl	-44(%ebp), %eax
	cmpl	%eax, 12(%ebp)
	jg	.L8
.L2:
	movl	-28(%ebp), %edx
	xorl	%gs:20, %edx
	movl	%ebx, %eax
	jne	.L15
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L13:
	movb	$0, -1(%eax,%edx)
	movl	%edx, (%esp)
	call	strlen
	cmpl	%eax, 16(%ebp)
	je	.L5
.L14:
	movl	$.LC1, (%esp)
	xorl	%ebx, %ebx
	call	puts
	jmp	.L2
.L12:
	movl	12(%ebp), %edx
	xorl	%ebx, %ebx
	movl	$.LC0, 4(%esp)
	movl	$1, (%esp)
	movl	%edx, 8(%esp)
	call	__printf_chk
	jmp	.L2
.L15:
	call	__stack_chk_fail
	.size	game_from_file, .-game_from_file
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"-?"
.LC3:
	.string	"--help"
.LC4:
	.string	"%s"
	.section	.rodata.str1.4
	.align 4
.LC5:
	.string	"Invalid integer given for row or column.\n\n%s"
	.align 4
.LC6:
	.string	"Invalid number of evolutions given.\n\n%s"
	.section	.rodata.str1.1
.LC7:
	.string	"r"
.LC8:
	.string	"Error opening file '%s'!\n"
	.section	.rodata.str1.4
	.align 4
.LC9:
	.string	"An error occurred while getting initial game from file. Exiting..."
	.align 4
.LC10:
	.string	"****************INITIAL GAME****************"
	.text
	.p2align 4,,15
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$36, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	subl	$5, %eax
	cmpl	$1, %eax
	ja	.L17
	movl	4(%ebx), %eax
	movzbl	.LC2, %edx
	cmpb	%dl, (%eax)
	jne	.L18
	movzbl	.LC2+1, %edx
	cmpb	%dl, 1(%eax)
	je	.L30
.L18:
	movl	$.LC3, %edi
	movl	$7, %ecx
	movl	%eax, %esi
	repz cmpsb
	je	.L17
	movl	$10, 8(%esp)
	movl	$0, 4(%esp)
	movl	%eax, (%esp)
	call	strtol
	movl	$10, 8(%esp)
	movl	$0, 4(%esp)
	movl	%eax, %edi
	movl	8(%ebx), %eax
	movl	%eax, (%esp)
	call	strtol
	movl	%eax, %esi
	movl	12(%ebx), %eax
	movl	$10, 8(%esp)
	movl	$0, 4(%esp)
	movl	%eax, 20(%esp)
	movl	16(%ebx), %eax
	movl	%eax, (%esp)
	call	strtol
	cmpl	$6, 8(%ebp)
	movl	$0, 24(%esp)
	movl	%eax, 28(%esp)
	je	.L31
.L20:
	leal	-1(%edi), %eax
	cmpl	$1023, %eax
	ja	.L21
	testl	%esi, %esi
	jle	.L21
	cmpl	$1024, %esi
	jg	.L21
	cmpl	$100000, 28(%esp)
	ja	.L32
	movl	20(%esp), %edx
	movl	$.LC7, 4(%esp)
	movl	%edx, (%esp)
	call	fopen
	testl	%eax, %eax
	je	.L33
	movl	%esi, 8(%esp)
	movl	%edi, 4(%esp)
	movl	%eax, (%esp)
	call	game_from_file
	testl	%eax, %eax
	movl	%eax, %ebx
	je	.L34
	movl	$.LC10, (%esp)
	xorl	%esi, %esi
	call	puts
	movl	%ebx, (%esp)
	call	print_game
	movl	28(%esp), %edx
	testl	%edx, %edx
	jne	.L27
	jmp	.L26
	.p2align 4,,7
	.p2align 3
.L29:
	movl	%edi, %ebx
.L27:
	movl	%ebx, (%esp)
	addl	$1, %esi
	call	evolve_torus
	movl	%ebx, (%esp)
	movl	%eax, %edi
	call	free_game
	movl	24(%esp), %edx
	movl	%edx, (%esp)
	call	usleep
	cmpl	28(%esp), %esi
	jl	.L29
.L26:
	addl	$36, %esp
	xorl	%eax, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L30:
	movzbl	.LC2+2, %edx
	cmpb	%dl, 2(%eax)
	jne	.L18
.L17:
	movl	USAGE, %eax
	movl	$.LC4, 4(%esp)
	movl	$1, (%esp)
	movl	%eax, 8(%esp)
	call	__printf_chk
	movl	$0, (%esp)
	call	exit
	.p2align 4,,7
	.p2align 3
.L31:
	movl	$10, 8(%esp)
	movl	$0, 4(%esp)
	movl	20(%ebx), %eax
	movl	%eax, (%esp)
	call	strtol
	imull	$1000, %eax, %eax
	movl	%eax, 24(%esp)
	jmp	.L20
.L21:
	movl	USAGE, %eax
	movl	$.LC5, 4(%esp)
	movl	$1, (%esp)
	movl	%eax, 8(%esp)
	call	__printf_chk
	movl	$1, (%esp)
	call	exit
.L32:
	movl	USAGE, %eax
	movl	$.LC6, 4(%esp)
	movl	$1, (%esp)
	movl	%eax, 8(%esp)
	call	__printf_chk
	movl	$1, (%esp)
	call	exit
.L34:
	movl	$.LC9, (%esp)
	call	puts
	movl	$1, (%esp)
	call	exit
.L33:
	movl	20(%esp), %eax
	movl	$.LC8, 4(%esp)
	movl	$1, (%esp)
	movl	%eax, 8(%esp)
	call	__printf_chk
	movl	$1, (%esp)
	call	exit
	.size	main, .-main
.globl USAGE
	.section	.rodata.str1.4
	.align 4
.LC11:
	.ascii	"game_of_life <num_rows> <num_cols> <input_file> <num_evoluti"
	.ascii	"ons> [<pause_time_ms>] [--help | -?]\n\tnum_rows : specify n"
	.ascii	"umber of rows in game of life <= 1024.\n\tnum_cols : specify"
	.ascii	" number of cols in game of life <= 1024.\n\tinput_file : spe"
	.ascii	"cify input file name. If file does not contain a rectangle o"
	.ascii	"f O's and X's with given rows/"
	.string	"cols an error will occur.\n\tnum_evolutions : specify number of iterations to perform in game of life <= 100000.\n\tpause_time_ms : specify time in milliseconds to pause between each evolution for your viewing pleasure\n\t--help or -? : show this usage and exit\n"
	.data
	.align 4
	.type	USAGE, @object
	.size	USAGE, 4
USAGE:
	.long	.LC11
.globl MAX_ROWS_COLS
	.section	.rodata
	.align 4
	.type	MAX_ROWS_COLS, @object
	.size	MAX_ROWS_COLS, 4
MAX_ROWS_COLS:
	.long	1024
.globl MAX_EVOLUTIONS
	.align 4
	.type	MAX_EVOLUTIONS, @object
	.size	MAX_EVOLUTIONS, 4
MAX_EVOLUTIONS:
	.long	100000
	.comm	ALIVE,1,1
	.comm	DEAD,1,1
	.comm	INPUT_FILE_ALIVE,4,4
	.comm	INPUT_FILE_DEAD,4,4
	.ident	"GCC: (Ubuntu/Linaro 4.5.2-8ubuntu4) 4.5.2"
	.section	.note.GNU-stack,"",@progbits
