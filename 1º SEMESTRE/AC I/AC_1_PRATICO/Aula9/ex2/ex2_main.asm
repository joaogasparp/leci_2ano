# 

	.data
str1:	.asciiz "Valor (ºF): "
str2:	.asciiz "Valor em ºC: "
	.eqv read_double,7
	.eqv print_double,3
	.eqv print_string,4
const5:	.float 5.0
const9:	.float 9.0
const32:	.float 32.0
	.text
	.globl main

main:	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	li $v0,print_string
	la $a0,str1
	syscall
	
	li $v0,read_double
	syscall
	mov.d $f12,$f0
	jal f2c
	
	li $v0,print_string
	la $a0,str2
	syscall
	
	mov.d $f12,$f0
	li $v0,print_double
	syscall
	
	li $v0,0

	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra