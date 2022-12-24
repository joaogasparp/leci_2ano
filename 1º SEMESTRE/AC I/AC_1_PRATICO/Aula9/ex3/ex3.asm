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
	jal avg
	mov.d $f12,$f0
	li $v0,print_double
	syscall
	
	li $v0,0
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra
	
###############
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
	
	
	