#

	.data
	.eqv id_number,0
	.eqv first_name,4
	.eqv last_name,22
	.eqv grade,40
	.eqv print_intu10,36
	.eqv print_string,4
	.eqv print_float,2
	.eqv print_char,11
str1:	.asciiz "\nN. Mec: "
str2:	.asciiz "\nNome: "
str3:	.asciiz "\nNota: "
	.text
	.globl print_student
	
print_student:	move $t0,$a0
	li $v0,print_string
	la $a0,str1
	syscall
	li $v0,print_intu10
	lw $a0,id_number($t0)
	syscall
	li $v0,print_string
	la $a0,str2
	syscall
	li $v0,print_string
	addiu $a0,$t0,first_name
	syscall
	li $v0,print_char
	li $a0,' '
	syscall
	li $v0,print_string
	addiu $a0,$t0,last_name	
	syscall
	li $v0,print_string
	la $a0,str3
	syscall
	li $v0,print_float
	l.s $f12,grade($t0)
	syscall
	jr $ra