# Mapa de registos
# rv		: $t0
# n		: $t1
# lista		: $t2
# lista + n	: $t3
# lista[n]	: $t4
# sum		: $s0
# nit		: $s1
# pt		: $s2

	.data
	.eqv SIZE,8
	.eqv read_int,5
	.eqv print_int10,1
	.eqv print_string,4
list:	.space 32
str1:	.asciiz "Media invalida!\n"
	.text
	.globl main
	
main:	addiu $sp,$sp,-20
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	sw $s2,12($sp)
	sw $s3,16($sp)

	li $s0,0		# sum = 0
	li $s1,0		# nit = 0
	la $s2,list		# pt = list
	li $s3,SIZE		# // $s3 = SIZE
	sll $s3,$s3,2		# // $s3 = SIZE*4 = 32
	addu $s3,$s3,$s2	# // $s3 = list + SIZE
	
for1:	bge $s2,$s3,endf1
	li $v0,read_int
	syscall
	sw $v0,0($s2)
	addi $s2,$s2,4
	j for1

endf1:	li $t1,0
	la $t2,list

for2:	bge $t1,SIZE,if2
	sll $t3,$t1,2		# // $t3 = n*4
	addu $t3,$t3,$t2	# // $t3 = list+n*4
	lw $t4,0($t3)		# // $t4 = list[n]
	
if1:	bltz $t4,endif
	addu $s0,$s0,$t4
	addi $s1,$s1,1
	
endif:	addiu $t1,$t1,1
	j for2

if2:	blez $s1,else
	div $a0,$s0,$s1
	li $v0,print_int10
	syscall
	li $t0,0
	j end
	
else:	la $a0,str1
	li $v0,print_string
	syscall
	li $t0,-1

end:	move $v0,$t0

	lw $s3,16($sp)
	lw $s2,12($sp)
	lw $s1,8($sp)
	lw $s0,4($sp)
	lw $ra,0($sp)
	addiu $sp,$sp,20
	jr $ra