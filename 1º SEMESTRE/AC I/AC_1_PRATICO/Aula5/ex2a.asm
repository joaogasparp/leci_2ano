# Mapa de registos
# p: $t0
# *p: $t1
# lista+SIZE: $t2

	.data
	.eqv SIZE,10
str1:	.asciiz "\nConteudo do array:\n"
str2:	.asciiz "; "
lista:	.word 8,-4,3,5,124,-15,87,9,27,15
	.align 2
	.eqv print_int10,1
	.eqv print_string,4
	.text
	.globl main
	
main:	la $a0,str1
	li $v0,4
	syscall

	la $t0,lista # p = lista
	li $t2,SIZE # $t2 = SIZE
	sll $t2,$t2,2 # SIZE * 4
	addu $t2,$t0,$t2 # $t2 = lista + SIZE
	
while:	bgeu $t0,$t2,endw
	lw $t1,0($t0)
	
	addi $a0,$t1,0
	li $v0,1
	syscall

	la $a0,str2
	li $v0,4
	syscall
	
	addiu $t0,$t0,4
	j while

endw:	jr $ra