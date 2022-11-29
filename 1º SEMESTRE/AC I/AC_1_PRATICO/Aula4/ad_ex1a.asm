		# Mapa de registos:
		# $t0 - *p
		# $t1 - p
	.data
str1:	.asciiz "Introduza uma string: "
	.eqv read_string,8
	.eqv print_string,4
	.eqv SIZE,20
str:	.space 40
	.text
	.globl main

main:	la $a0,str1
	li $v0,4
	syscall
	la $a0,str
	li $a1,SIZE
	li $v0,8
	syscall
	la $t1,str
	
while:	lb $t0,0($t1)
	beq $t0,'\0',endw
	sub $t0,$t0,0x20
	addi $t1,$t1,1
	j while
	
endw:	or $a0,$0,$t1
	li $v0,4
	syscall
	
	jr $ra
