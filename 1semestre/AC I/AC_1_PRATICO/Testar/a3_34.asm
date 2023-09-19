# Mapa de registos
# i: $t0
# k: $t1
	.data
str:	.asciiz "\n"
	.eqv print_int10,36
	.eqv print_string,8
	.text	
	.globl main
	
main:	ori $t0,$0,5
	ori $t1,$0,0
	
for:	bge $t0,20,endfor
	addi $t0,$t0,1
	addi $t1,$t1,5
	j for

endfor:	or $a0,$0,$t0
	li $v0,36
	syscall
	
	la $a0,str
	li $v0,4
	syscall
	
	or $a0,$0,$t1
	li $v0,36
	syscall
	
	jr $ra