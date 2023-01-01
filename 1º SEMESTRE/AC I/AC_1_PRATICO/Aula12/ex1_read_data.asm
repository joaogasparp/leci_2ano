#

	.data
	.eqv id_number,0
	.eqv first_name,4
	.eqv last_name,22
	.eqv grade,40
	.eqv SIZE_STUDENT,44
	.eqv SIZE_FIRST_NAME,17
	.eqv SIZE_LAST_NAME,14
	.eqv read_int,5
	.eqv print_string,4
	.eqv read_string,8
	.eqv read_float,6
str1:	.asciiz "N. Mec: "
str2:	.asciiz "Primeiro Nome: "
str3:	.asciiz "Ultimo Nome: "
str4:	.asciiz "Nota: "
	.text
	.globl read_data
	
read_data:	move $t0,$a0
	move $t1,$a1
	li $t2,0

for:	bge $t2,$t1,endfor
	mul $t3,$t2,SIZE_STUDENT
	addu $t3,$t0,$t3
	la $a0,str1
	li $v0,print_string
	syscall
	li $v0,read_int		# st[i].id_number = read_int()
	syscall
	sw $v0,id_number($t3)
	la $a0,str2
	li $v0,print_string
	syscall
	li $v0,read_string	# read_string(st[i].first_name, 17)
	addiu $a0,$t3,first_name
	li $a1,SIZE_FIRST_NAME
	syscall
	la $a0,str3
	li $v0,print_string
	syscall
	li $v0,read_string	# read_string(st[i].last_name, 14)
	addiu $a0,$t3,last_name
	li $a1,SIZE_LAST_NAME
	syscall
	la $a0,str4
	li $v0,print_string
	syscall
	li $v0,read_float	# st[i].grade = read_float()
	syscall
	s.s $f0,grade($t3)
	addi $t2,$t2,1
	j for

endfor:	jr $ra