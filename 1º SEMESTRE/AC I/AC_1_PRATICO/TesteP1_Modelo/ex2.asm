# Mapa de registos
# i: $t0
# &val[0]: $t1
# val + i: $t2
# val[i] ou val[i+SIZE/2]: $t3
# SIZE: $t4
# i+SIZE/2: $t6

	.data
val:	.word 8,4,15,-1987,327,-9,27,16
str1:	.asciiz "Result is: "
	.eqv SIZE,8
	.eqv print_string,4
	.eqv print_int10,1
	.eqv print_char,11
	.text
	.globl main
	
main:	li $t0,0	# i = 0
	la $t1,val	# $t1 = val
	li $t4,SIZE	# $t4 = SIZE
	mul $t4,$t4,2	# $t4 = (SIZE*4)/2 == SIZE*2
	
do1:	addu $t2,$t1,$t0	# $t2 = val + i
	lw $t3,0($t2)		# $t3 = val[i]
	
	addu $t6,$t2,$t4	# $t6 = val+i+SIZE/2
	lw $t5,0($t6)		# $t5 = val[i+SIZE/2]
	
	sw $t3,0($t6)		# val[i] = val[i+SIZE/2]
	sw $t5,0($t2)		# val[i+SIZE/2] = val[i]
	
	addi $t0,$t0,4
	blt $t0,$t4,do1
	
	la $a0,str1
	li $v0,print_string
	syscall
	li $t0,0	# i = 0
	
	li $t4,SIZE	# $t4 = SIZE
	sll $t4,$t4,2	# $t4 = SIZE*4
	
do2:	addu $t2,$t1,$t0	# $t2 = val + i
	lw  $a0,0($t2)		# $a0 = val[i]
	li $v0,print_int10
	syscall
	li $a0,','
	li $v0,print_char
	syscall
	addi $t0,$t0,4		# i = i + 4
	blt $t0,$t4,do2
	
	jr $ra
