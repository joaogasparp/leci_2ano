 	.data
fnum:	.float 4.0
	.eqv print_float, 2
	.text
	.globl main

main:	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	li $a0,2
	l.s $f12,fnum
	jal xtoy
	
	li $v0,print_float
	mov.s $f12,$f0
	syscall
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	jr $ra