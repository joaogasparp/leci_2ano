# Mapa de registos
# a:		$a0
# N:		$a1
# p_odd: 	$a2
# n_even: 	$t0
# p:		$t1
# *p: 		$t2

split_odd:	li $t0,0	# n_even
		sll $t3,$a1,2	# $t3 = N*4
		addu $t3,$t3,$a0	# $t3 = a+N*4
		move $t1,$a0
		
for:	bge $t1,$t3,endf

if:	lw $t2,0($t1)	# *p2
	rem $t4,$t2,2	# $t4 = 
	beq $t4,0,else
	sw $t2,0($a2)
	addiu $a2,$a2,4
	j endif
	
else:	addi $t0,$t0,1
	
endf:	addiu $t1,$t1,1
	j for