# Mapa de registo:
# i: $t0
# xn: $f4
# 0.0 | aux: $f6
# 0.5: $f8
# val: $f12 porque é o valor de entrada

	.data
fnum1:	.double 1.0
fnum2:	.double 0.0
fnum3:	.double 0.5
	.text
	.globl sqrt
	
sqrt:	li $t0,0
	la $t1,fnum1
	l.d $f4,0($t1)
	la $t1,fnum2
	l.d $f6,0($t1)
	
if2:	c.le.d $f12,$f6
	bc1t else2
	
do2:	mov.d $f6,$f4
	div.d $f8,$f12,$f4
	add.d $f4,$f4,$f8
	la $t1,fnum3
	l.d $f8,0($t1)
	mul.d $f4,$f8,$f4
	
	c.eq.d $f6,$f4
	bc1t enddo2
	addi $t0,$t0,1
	blt $t0,25,do2

enddo2:	j endif

else2:	la $t1,fnum2
	l.d $f4,0($t1)

endif:	mov.d $f0,$f4
	jr $ra