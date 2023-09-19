# Mapa de registos
# i:		$s0
# nval:		$s1
# array:	$s2
# array+i:	$s3
# array[i]:	$f12
# media:	$f20
# soma:		$f22

	.data
fnum1:	.float 0.0
	.text
	.globl var

var:	addiu $sp,$sp,-28
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	sw $s2,12($sp)
	sw $s3,16($sp)
	s.s $f20,20($sp)
	s.s $f22,24($sp)
	
	jal avg
	cvt.s.d $f20,$f0
	move $s2,$a0
	move $s1,$a1
	li $s0,0
	la $t1,fnum1
	l.d $f4,0($t1)
	
for:	bge $s0,$s1,endfor
	sll $t0,$s0,3
	addu $s3,$t0,$s2
	l.d $f12,0($s3)
	cvt.s.d $f12,$f12
	sub.s $f12,$f12,$f20
	li $a0,2
	jal xtoy
	add.s $f22,$f22,$f0
	addi $s0,$s0,1
	j for

endfor:	cvt.d.s $f22,$f22
	mtc1 $s1,$f4
	cvt.d.w $f4,$f4
	div.d $f0,$f0,$f4
	
	lw $ra,0($sp)
	lw $s0,4($sp)
	lw $s1,8($sp)
	lw $s2,12($sp)
	lw $s3,16($sp)
	l.s $f20,20($sp)
	l.s $f22,24($sp)
	addiu $sp,$sp,28
	jr $ra