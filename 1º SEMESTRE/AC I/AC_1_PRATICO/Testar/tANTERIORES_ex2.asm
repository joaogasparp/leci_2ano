# Mapa de registos	
# a	: $t0
# N	: $t1
# b	: $t2
# k	: $t3
# p	: $t4
	
	.data
zero:	.double 0.0
dois:	.double 2.0	
	.text
	.globl fun1:

fun1:	move $t0,$a0		# $t0 = *a
	move $t1,$a1		# $t1 = N
	move $t2,$a2		# $t2 = *b
	li $t3,0		# k = 0
	move $t4,$t0		# $t4 = p = a
	mul $t5,$t1,8		# $t5 = N*8
	addu $t5,$t0,$t5	# $t5 = (a + N*8)

for:	bge $t4,$t5,endf	# for( p = a; p < (a + N); p++) 
	l.d $f8,0($t4)		# $f8 = *p
	l.d $f6,dois		# $f6 = 2.0
	div.d $f4,$f8,$f6	# $f4 = (*p / 2.0)
	l.d $f6,zero		# $f6 = 0.0
	
if:	c.eq.d $f4,$f6		# $f4 == $f6
	bc1t else		# if ((*p / 2.0) != 0.0 ) {
	s.d $f8,0($t2)		# *b = *p;
	addiu $t2,$t2,8		# b++
	j endif
	
else:	addi $t3,$t3,1		# k++

endif:	addiu $t4,$t4,8		# p++
	j for
	
endf:	sub $v0,$t1,$t3		# return (N - k); 
	jr $ra
