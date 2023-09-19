# Mapa de registos
# i: $t0
	.data
array:	.byte 'H','E','L','L','O'
str:	.ascii "\n"
	.eqv print_char,11
	.eqv print_string,4
	.text
	.globl main
	
main:	li $t0,0
	la $t1,array

while:	addu $t2,$t1,$t0
	lb $t3,0($t2)
	beq $t3,'\0',endw
	
	or $a0,$0,$t3
	li $v0,11
	syscall
	
	la $a0,str
	li $v0,4
	syscall
	
	addi $t0,$t0,1
	j while

endw:	jr $ra