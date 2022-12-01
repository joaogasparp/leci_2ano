# Mapa de registos:
# val: $f0
# 2.59375: $f2
# res: $f4
# 0.0: $f6
	
	.data
	.eqv read_int,5
	.eqv print_float,2
k1:	.float 2.59375
k2:	.float 0.0
	.text
	.globl main

main:	

do:	li $v0,read_int
	syscall
	mtc1 $v0,$f0	# $f0 = $v0
	cvt.s.w $f0,$f0
	
	l.s $f2,k1
	
	mul.s $f4,$f0,$f2
	
	mfc1 $a0,$f4
	li $v0,print_float
	syscall
	
	l.s $f6,k2
	c.eq.s $f4,$f6
	bc1f do
	
	jr $ra