# Mapa de registos:
# $t0 - res
# $t1 - i
# $t2 - mdor
# $t3 - mdo
# $t4 - read_int()
	.data
str1:	.asciiz "Introduza dois números: "
str2:	.asciiz "\nResultado: "
	.eqv print_string,4
	.eqv read_int,5
	.eqv print_int10,1
	.text
	.globl main
	
main:	li $t0,0
	li $t1,0
	la $a0,str1
	li $v0,4
	syscall
	li $v0,5
	syscall
	or $t4,$0,$v0
	ori $t2,$t4,0x0f
	or $t3,$0,$v0
	ori $t3,$t4,0x0f

while:	beq $t2,0,endw
	addi $t1,$t1,1
	bge $t1,4,endw
	addi $t5,$t2,0x00000001
	
if:	beq $t5,0,outif
	add $t0,$t0,$t3

outif:	sll $t3,$t3,1
	srl $t2,$t2,1
	j while

endw:	la $a0,str2
	li $v0,4
	syscall
	or $a0,$0,$t0
	li $v0,1
	syscall