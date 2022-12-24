	.data
	.eqv print_int10,1
str:	.asciiz "Arquitetura de computadores I"
	.text
	.globl main
	
main:	addiu $sp,$sp,-4
	sw $ra,0($sp)

	la $a0,str
	jal strlen
	move $a0,$v0
	li $v0,print_int10
	syscall
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra 