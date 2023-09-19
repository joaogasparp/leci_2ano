# Mapa de registos		# Legenda
# a	: $a0			# #: linha de código C
# t	: $f12			# //: comentário
# n	: $a2
# oldg	: $f4
# g	: $f6
# s	: $f8
# k	: $t1

	.data
f1:	.float -1.0
f2:	.float 1.0
f3:	.float 0.0
	.text
	.globl func3

func3:	l.s $f4,f1		# $f4 (oldg) = -1.0
	l.s $f6,f2		# $f6 (g) = 1.0
	l.s $f8,f3		# $f8 (s) = 0.0
	li $t0,0		# k = 0

for:	bge $t0,$a1,endf	# for (k = 0; k < n; k++) {
	
while:	sub.s $f10,$f6,$f4	# $f10 = g - oldg
	c.le.s $f10,$f12	# // ((g - oldg) > t)
	bc1t endw
	mov.s $f4,$f6		# oldg = g
	sll $t1,$t0,2		# // $t1 = k*4
	addu $t1,$a0,$t1	# // $t1 = &a + k*4
	l.s $f14,0($t1)		# // $f14 = a[k]
	add.s $f6,$f14,$f6	# // $f6 = g + a[k]
	div.s $f6,$f6,$f12	# g = (g + a[k] / t)
	j while			

endw:	add.s $f8,$f8,$f6	# s = s + g
	s.s $f6,0($t1)		# a[k] = g
	addiu $t0,$t0,1		# // k++
	j for

endf:	mtc1 $a1,$f0		# // $f0 = n
	cvt.s.w $f0,$f0		# // $f0 = (float) n
	div.s $f0,$f8,$f0	# return s / (float) n
	jr $ra