	.data
std:	.word 72343
	.asciiz "Napoleao"
	.space 9
	.asciiz "Bonaparte"
	.space 5
	.float 5.1
	.eqv print_str,4
	.eqv print_intu10,36
	.eqv print_char,11
	.eqv print_float,2
str1:	.asciiz "\nN. Mec: "
str2:	.asciiz "\nNome: "
str3:	.asciiz "\nNota: "
	.text
	.globl main
	
main:	la $t0,std

	la $a0,str1
	li $v0,4
	syscall
	lw $a0,0($t0)
	li $v0,36
	syscall
	
	la $a0,str2
	li $v0,4
	syscall
	addiu $a0,$t0,22
	li $v0,4
	syscall
	li $a0,','
	li $v0,11
	syscall
	addiu $a0,$t0,4
	li $v0,4
	syscall
	
	la $a0,str3
	li $v0,4
	syscall
	l.s $f12,40($t0)
	li $v0,2
	syscall
	
	jr $ra