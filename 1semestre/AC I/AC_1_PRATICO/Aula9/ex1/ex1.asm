# Mapa de registos
# res:	$f8

	.data
	.eqv read_int, 5
	.eqv print_float, 2
	.eqv print_char, 11
k0:	.float 2.59375
k1:	.float 0.0
	.text
	.globl main
	
main:						# do {
	li $v0,read_int				# read_int()
	syscall					#
	mtc1 $v0,$f4				# $f4 = read_int()
	cvt.s.w $f4,$f4				# $0 = (float) val
	la $t1,k0				# $t1 = &k0
	l.s $f6,0($t1)				# $f6 = 2.59375
	mul.s $f8,$f4,$f6			# res = (float)val * 2.59375;
	mov.s $f12,$f8				# print_float(res)
	li $v0,print_float			#
	syscall					#
	li $v0,print_char			# print_char('\n')
	li $a0,'\n'				#
	syscall
	la $t1,k1				# $t1 = &k1
	l.s $f6,0($t1)				# $f6 = 0.0
	c.eq.s $f8,$f6				# res == 0.0
	bc1f main				# } while (res != 0.0)
	li $v0,0				# return 0
	jr $ra