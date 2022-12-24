# Mapa de registos
# exit_value:	$t0
	
	.data
	.eqv STR_MAX_SIZE, 30
	.eqv print_string, 4
	.eqv print_int10, 1
str1:	.asciiz "I serodatupmoC ed arutetiuqrA"
str2:	.space 31
str3:	.asciiz "\n"
str4:	.asciiz "String too long: "
	.text
	.globl main
	
main:	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	la $a0,str1
	jal strlen
	
if:	bgt $v0,STR_MAX_SIZE,else
	la $a0,str2
	la $a1,str1
	jal strcpy	# chamar a função strcpy(str2,str1)
	
	la $a0,str2
	li $v0,print_string
	syscall
	
	la $a0,str3
	li $v0,print_string
	syscall
	
	la $a0,str2
	jal strrev	# chamar a função strrev(str2)
	move $a0,$v0	# mover o return da função strrev ($v0) para $a0
	li $v0,print_string
	syscall
	
	li $t0,0
	j endif
	
else:	la $a0,str4
	li $v0,print_string
	syscall
	
	la $a0,str1
	jal strlen
	move $a0,$v0
	li $v0,print_int10
	syscall
	
	li $t0,-1
	
endif:	move $v0,$t0	# dar return a $t0	

	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra
