# Mapa de registos
# val: $t0
# n: $t1
# min: $t2
# max: $t3
	.data
str1: 	.asciiz "Digite até 20 números inteiros (zero para terminar): "
str2: 	.asciiz "Máximo/Mínimo são: "
	.eqv print_string,4
	.eqv read_int,5
	.eqv print_int10,36
	.eqv print_char,11
	.text
	.globl main
	
main:	li $t1,0
	li $t2,0x7FFFFFFF
	li $t3,0x80000000
	la $a0,str1
	li $v0,4
	syscall
	
do:	li $v0,5
	syscall
	or $t0,$0,$v0
	
if1:	beq $t0,0,endif

if11:	ble $t0,$t3,if12
	or $t3,$t0,$0

if12:	bge $t0,$t2,endif
	or $t2,$t0,$0

endif:	addi $t1,$t1,1
	bge $t1,20,enddo
	bne $t0,0,do

enddo:	la $a0,str2
	li $v0,4
	syscall
	add $a0,$0,$t3
	li $v0,36
	syscall
	li $a0,':'
	li $v0,11
	syscall
	add $a0,$0,$t2
	li $v0,36
	syscall
	
	jr $ra
	
	