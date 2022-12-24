#

	.data
str1:	.asciiz "Arquitetura de "
str2:	.space 51
str3:	.asciiz "Computadores I"
	.eqv print_string,4
	.eqv print_char,11
	.text
	.globl main
	
main:	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	la $a0,str2
	la $a1,str1
	jal strcpy
	
	li $v0,print_string
	la $a0,str2
	syscall
	
	li $v0,print_char
	li $a0,'\n'
	syscall
	
	la $a0,str2
	la $a1,str3
	jal strcat
	move $a0,$v0
	li $v0,print_string
	syscall
	
	li $v0,0
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra