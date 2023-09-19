# Mapa de registos
# str: $s0
# val: $s1
# O main é, neste caso, uma sub-rotina intermédia

	.data
str:	.space 34
	.eqv STR_MAX_SIZE,33
	.eqv read_int,5
	.eqv print_string,4
	.eqv print_char,11
	.text
	.globl main
	
main:	addiu $sp,$sp,-8	# reserva espaço na stack
	sw $s0,0($sp)		# guarda registos $sx na stack
	sw $ra,4($sp)		# guarda $ra na stack
	
do:	li $v0,read_int		# do {
	syscall
	move $s0,$v0		# val = read_int()
	
	move $a0,$s0
	li $a1,2
	la $a2,str
	jal itoa
	move $a0,$v0
	li $v0,print_string
	syscall
	
	li $v0,print_char
	li $a0,'|'
	syscall	
	
	move $a0,$s0
	li $a1,8
	la $a2,str
	jal itoa
	move $a0,$v0
	li $v0,print_string
	syscall
	
	li $v0,print_char
	li $a0,'|'
	syscall	
	
	move $a0,$s0
	li $a1,16
	la $a2,str
	jal itoa
	move $a0,$v0
	li $v0,print_string
	syscall
	
	li $v0,print_char
	li $a0,'\n'
	syscall	
	
	bnez $s0,do		# } while(val != 0)
	
	li $v0,0		# return 0;
	
	lw $s0,4($sp)		# repoe registos $sx
	lw $ra,0($sp)		# repõe registo $ra
	addiu $sp,$sp,8		# liberta espaço na stack
	jr $ra			# termina programa