	.data
	.equ p_char, 3
	.equ g_char, 2
	.text
	.globl main
main:
do:
	li $v0, g_char
	syscall
	
	move $a0, $v0
	li $v0, p_char
	syscall
	
while:
	bne  $a0, '\n', do
	
	li $v0, 0
	jr $ra
	
	
