# i: $t0
# lista: $t1
# lista + i: $t2

	.data
	.eqv SIZE,5
str1:	.asciiz "\nIntroduza um número: "
	.align 2
lista:	.space 20
	.eqv print_string,4
	.eqv read_int,5
	.text
	.globl main
	
main:	li $t0,0

while:	bge $t0,SIZE,endw
	la $a0, str1
	li $v0,4
	syscall
	
	li $v0,5
	syscall
	
	la $t1,lista # $t1 = lista ou &lista[0]
	sll $t2,$t0,2 # $t2 = i x 4
	addu $t2,$t2,$t1 # $t2 = &lista[i] ou lista + i
	sw $v0,0($t2)
	
	addi $t0,$t0,1
	j while
	
endw:	jr $ra