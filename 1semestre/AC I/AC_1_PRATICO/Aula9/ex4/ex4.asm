###############
# Mapa de registos
# i:		$t0
# SIZE*8:	$t1
# a:		$t2
# a+i:		$t3

	.data
	.eqv SIZE,10
	.eqv read_int,5
	.eqv print_double,3
a:	.space 80
	.text
	.globl main
	
main:	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	la $t2,a
	li $t0,0
	li $t1,SIZE
	sll $t1,$t1,3

for1:	bge $t0,$t1,endf1
	li $v0,read_int
	syscall
	mtc1.d $v0,$f4
	cvt.d.w $f4,$f4
	addu $t3,$t2,$t0
	s.d $f4,0($t3)
	addi $t0,$t0,8
	j for1

endf1:	move $a0,$t2
	li $a1,SIZE
	jal max
	mov.d $f12,$f0
	li $v0,print_double
	syscall
	
	li $v0,0
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra
	
###############
# Mapa de registos
# max:	$f4
# u:	$t0
# p:	$a0
# *p:	$f6

	.data
	.text
	.globl max
	
max:	sub $a1,$a1,1		# $a1 = n-1
	sll $a1,$a1,3		# $a1 = (n-1)*8
	addu $t0,$a0,$a1	# *u = p+n–1
	l.d $f4,0($a0)		# max = *p
	addiu $a0,$a0,8		# p++
	
for2:	bgt $a0,$t0,endf2
	l.d $f6,0($a0)		# $f6 = *p
	
if2:	c.le.d $f6,$f4		# if(*p > max) {
	bc1t endif2
	mov.d $f4,$f6		# max = *p
	
endif2:	addiu $a0,$a0,8		# p++
	j for2
	
endf2:	mov.d $f0,$f4		# return max
	jr $ra