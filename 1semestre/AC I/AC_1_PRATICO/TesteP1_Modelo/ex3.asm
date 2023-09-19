# Mapa de registros
# n_even: $t0
# n_odd: $t1
# p1: $t2
# p2: $t3
# *p1: $t4
# *p2: $t5

	.data
	.eqv N,35
av:	.space 140
bv:	.space 140
	.eqv read_int,5
	.eqv print_int10,1
	.eqv print_char,11
	.text
	.globl main
	
main:	li $t0,0	# n_even = 0
	li $t1,0	# n_odd = 0
	la $t2,av	# p1 = av
	li $t6,N	# $t6 = N == 35
	sll $t6,$t6,2	# $t6 = N*4
	addu $t6,$t2,$t6 	# $t6 = av + N*4
	
for1:	bge $t2,$t6,endf1	# while [p1 < ($t6 = av + N*4)]
	li $v0,read_int 
	syscall
	sw $v0,0($t2)	# o valor lido = *av == *p1
	addiu $t2,$t2,4	# p1 = p1 + 4
	j for1
	
endf1:	la $t2,av	# p1 = av
	la $t3,bv	# p2 = bv
	
for2:	bge $t2,$t6,endf2	# while [p1 < ($t6 = av + N*4)]
	lw $t4,0($t2)	# *p1
	rem $t7,$t4,2	# *p1 % 2
	
if:	beq $t7,0,else	# if [(*p1 % 2) != 0]
	lw $t5,0($t2)	# $t5 = *p1
	sw $t5,0($t3)	# ($t5 = *p2) == (*p1 = *p2)
	addiu $t3,$t3,4	# p2 = p2 + 1
	addi $t1,$t1,1	# n_ood = n_ood + 1
	j endif

else:	addi $t0,$t0,1	# n_even = n_even + 1
	j endif
	
endif:	addiu $t2,$t2,4	# p1 = p1 + 1
	j for2
	
endf2:	la $t3,bv	# p2 = bv
	add $t8,$t8,$t1	# $t8 = $t8 + 1
	sll $t8,$t8,2	# $t8 = $t8 * 4
	addu $t8,$t8,$t3	# $t8 = b + n_ood

for3:	bge $t3,$t8,endf3	# while [p2 < ($t8 = bv + n_ood)]
	lw $a0,0($t3)	# $a0 = *p2
	li $v0,print_int10
	syscall
	li $a0,','
	li $v0,print_char
	syscall
	addiu $t3,$t3,4	# p2 = p2 + 1
	j for3
	
endf3:	jr $ra