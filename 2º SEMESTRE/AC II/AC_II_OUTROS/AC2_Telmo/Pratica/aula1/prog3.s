	.data
	.equ inkey, 1
	.equ put_char, 3
	.text
	.globl main
	
main:

do:
	li $v0, inkey
	syscall
	
if:
	beq $v0, 0, else	#if(inkey != 0)
	
	move $a0, $v0
	li $v0, put_char
	syscall
	
else: 
	la $a0, '.'
	li $v0, put_char
	syscall

while:
	bne $a0, '\n', do
	
	li $v0, 0
	jr $ra
