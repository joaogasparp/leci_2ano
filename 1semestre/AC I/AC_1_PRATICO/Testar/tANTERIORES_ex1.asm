#######################
# typedef struct
# {				Align	Size		Offset
#	char name[50];		1	50		0
#	int num;		4	4		50+0->52
#	float grade;		4	4		52+6->56
#	char type;		1	1		56+4->60
# } student;			4	60+1->64

	.data
std:	.align 2
	.asciiz "Rei Eusebio"
	.space 38
	.word 12345
	.float 17.2
	.byte 'F'
	.align 2
	.asciiz "Rainha Amalia"
	.space 36 
	.word 23450
	.float 12.5
	.byte 'C'
zero:	.float 0.0
dois:	.float 2.0
	.eqv print_float,2
	.eqv print_string,4
	.text
	.globl main

main:	addiu $sp,$sp,-4
	sw $ra,0,($sp)
	
	la $a0,std
	li $a1,2
	jal fun3		# // fun3(std, 2)
	li $v0,print_float
	syscall
	
	li $v0,-1
	lw $ra,0,($sp)
	addiu $sp,$sp,4
	jr $ra
	
#######################
# Mapa de registos
# std	: $t0
# n	: $t1
# i	: $t2
# sum	: $t3

	.data
	.text
	.globl fun3

fun3:	move $t0,$a0		# // $t0 = std
	move $t1,$a1		# // $t1 = n 
	l.s $f4,zero		# sum = 0.0
	li $t2,0		# // i = 0
	
for:	bge $t2,$t1,endf	# for (i = 0; i < n; i++) {
	mulu $t3,$t2,64		# // $t3 = i*64
	addu $t3,$t3,$t0	# // $t3 = std[i].name
	move $a0,$t3
	li $v0,print_string
	syscall			# print_string(std[i].name)
	l.s $f6,56($t3)
	mov.s $f12,$f6
	li $v0,print_float
	syscall			# print_float(std[i].grade)
	add.s $f4,$f4,$f6	# sum += std[i].grade
	addi $t2,$t2,1		# // i++
	j for			# }
	
endf:	l.s $f8,dois		# // $f8 = 2.0
	div.s $f0,$f4,$f8	# return sum / 2.0
	jr $ra