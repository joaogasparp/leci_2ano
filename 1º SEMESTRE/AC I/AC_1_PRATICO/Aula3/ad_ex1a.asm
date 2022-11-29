# Mapa de registos:
# $t0 - gray
# $t1 - mask
# $t2 - bin	
	.data
str1:	.asciiz "Introduza um número: "
str2:	.asciiz "Valor em código Gray: "
str3:	.asciiz "\nValor em binário: "
	.eqv print_string,4
	.eqv read_int,5
	.eqv print_int16,34
	.eqv print_int16,34
	.text
	.globl main
	
main:	la $a0,str1
	li $v0,4
	syscall
	li $v0,5
	syscall
	or $t0,$0,$v0
	srl $t1,$t0,1
	or $t2,$0,$t0
	
while:	beq $t1,0,endw
	xor $t2,$t2,$t1
	srl $t1,$t1,1
	j while

endw:	la $a0,str2
	li $v0,4
	syscall
	or $a0,$0,$t0
	li $v0,34
	syscall
	la $a0,str3
	li $v0,4
	syscall
	or $a0,$0,$t2
	li $v0,34
	syscall