#

	.data
k0:	.double 5.0
k1:	.double 9.0
k2:	.double 32.0
	.text
	.globl f2c

f2c:	la $t0,k0
	l.d $f4,0($t0)
	la $t0,k1
	l.d $f6,0($t0)
	la $t0,k2
	l.d $f8,0($t0)
	
	sub.d $f8,$f12,$f8
	div.d $f4,$f4,$f6
	mul.d $f0,$f4,$f8
	
	jr $ra