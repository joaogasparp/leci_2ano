# Mapa de registos
# val: $t0
# n: $t1
# min: $t2
# max: $t3

	.data
	.eqv print_string,4
	.eqv read_int,5
str1:	.asciiz "Digite até 20 inteiros (zero para terminar): "
str2:	.asciiz "Máximo/mínimo são: "
	.eqv print_char,11
	.eqv print_int10,1
	.text
	.globl main
	
main:	li $t1,0
	li $t2,0x7FFFFFFF
	li $t3,0x80000000
	
	la $a0,str1
	li $v0,print_string
	syscall
	
do:	li $v0,read_int
	syscall
	or $t0,$0,$v0

if:	beq $t0,0,endif
	
if1:	ble $t0,$t3,if2
	or $t3,$0,$t0
	j endif
	
if2:	bge $t0,$t2,endif
	or $t2,$0,$t0

endif:	addi $t1,$t1,1
	bge $t1,20,enddo
	beq $t0,0,enddo
	j do
	
enddo:	la $a0,str2
	li $v0,print_string
	syscall
	
	or $a0,$0,$t3
	li $v0,print_int10
	syscall
	
	li $a0,':'
	li $v0,print_char
	syscall	
	
	or $a0,$0,$t2
	li $v0,print_int10
	syscall
	
	jr $ra
	
	
	