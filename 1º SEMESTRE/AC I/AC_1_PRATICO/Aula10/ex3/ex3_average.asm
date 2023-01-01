# Mapa de registos
# i:		$t0	
# sum:		$f4
# array+i:	$t1
# array[i-1]:	$f6

	.data
k0:	.double 0.0
	.text
	.globl avg

avg:	move $t0,$a1
	sll $t0,$t0,3
	la $t1,k0
	l.d $f4,0($t1)
	
for2:	blez $t0,endf2
	addu $t1,$a0,$t0
	l.d $f6,-8($t1)
	add.d $f4,$f4,$f6
	sub $t0,$t0,8
	j for2
	
endf2:	mtc1.d $a1,$f6	
	cvt.d.w $f6,$f6
	div.d $f0,$f4,$f6
	jr $ra