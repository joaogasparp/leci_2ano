# Mapa de registos
# pmax: $t0
	
	.data
	.eqv MAX_STUDENTS,4
	.eqv print_string,4
	.eqv print_float,2
st_array:	.space 176	# sizeof(student) * 4 = 44*4
media:	.float 0.0
str1:	.asciiz "\nMedia: "
	.text
	.globl main
	
main:	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	la $a0,st_array
	li $a1,MAX_STUDENTS
	jal read_data
	la $a0,st_array
	li $a1,MAX_STUDENTS
	la $a2,media
	jal max
	move $t0,$v0
	la $a0,str1
	li $v0,print_string
	syscall
	la $t1,media
	l.d $f12,0($t1)
	li $v0,print_float
	syscall
	move $a0,$t0
	jal print_student
	li $v0,0
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	jr $ra