	.data
std:	.space 44
	.eqv print_str,4
	.eqv print_intu10,36
	.eqv print_char,11
	.eqv print_float,2
	.eqv read_int,5
	.eqv read_string,8
	.eqv read_float,6
str1:	.asciiz "N. Mec: "
str2:	.asciiz "Primeiro Nome: "
str3:	.asciiz "�ltimo Nome: "
str4:	.asciiz "Nota: "
str5:	.asciiz "\nNome: "
str6:	.asciiz "\nNota: "
	.text
	.globl main
	
main:	la $t0,std

# print mec
	la $a0,str1
	li $v0,4
	syscall
# read mec
	li $v0,5
	syscall
	sw $v0,0($t0)
	
# print pnome
	la $a0,str2
	li $v0,4
	syscall
# read pnome
	li $v0,8
	addi $a0,$t0,4
	li $a1,18
	syscall
	
# print lnome
	la $a0,str3
	li $v0,4
	syscall
# read lnome
	li $v0,8
	addi $a0,$t0,22
	li $a1,15
	syscall
	
# print nota
	la $a0,str4
	li $v0,4
	syscall
# read nota
	li $v0,6
	syscall
	s.s $f0,40($t0)
	
# print mec
	la $a0,str1
	li $v0,4
	syscall
	lw $a0,0($t0)
	li $v0,36
	syscall
	
# print nome
	la $a0,str5
	li $v0,4
	syscall
# print pnome
	addiu $a0,$t0,22
	li $v0,4
	syscall
# print ','
	li $a0,','
	li $v0,11
	syscall
# print lnome
	addiu $a0,$t0,4
	li $v0,4
	syscall
	
# print nota
	la $a0,str6
	li $v0,4
	syscall
	l.s $f12,40($t0)
	li $v0,2
	syscall
	
	jr $ra