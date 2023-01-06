# Mapa de registos
# fl			: $a0 -> $s0
# k			: $a1 -> $s1
# av			: $a2 -> $s2
# i			: $s3
# res			: $t0
# fl+i, av+i, i*4	: $t1
# fl[i], av[i]		: $t2

	.data
	.eqv SIZE,15
	.eqv print_int10,1
	.eqv print_string,4
str1:	.asciiz "Invalid argc"
	.text
	.globl main
	
main:	addiu $sp,$sp,-20
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	sw $s2,12($sp)
	sw $s3,16($sp)

	li $t0,-1
	move $s0,$a0
	move $s1,$a1
	move $s2,$a2
	
if:	blt $s1,2,else
	bgt $s1,SIZE,else
	li $s3,2
	
do:	sll $t1,$s3,2		# // $t1 = i*4
	addu $t1,$s2,$t1	# // $t1 = av + i*4
	lw $a0,0($t1)		# // $a0 = av[i]
	jal toi			# // toi(av[i])
	sll $t1,$s3,2		# // $t1 = i*4
	addu $t1,$s0,$t1	# // $t1 = fl + i*4
	sw $v0,0($t1)		# fl[i] = toi(av[i])
	addiu $s3,$s3,1
	blt $s3,$s1,do
	
	move $a0,$s0
	move $a1,$s1
	jal avz
	move $t0,$v0		# res = avz(fl, k)
	
	move $a0,$t0
	li $v0,print_int10
	syscall
	j end
	
else:	la $a0,str1
	li $v0,print_string
	syscall
	
end:	move $v0,$t0

	lw $ra,0($sp)
	lw $s0,4($sp)
	lw $s1,8($sp)
	lw $s2,12($sp)
	lw $s3,16($sp)
	addiu $sp,$sp,20
	jr $ra