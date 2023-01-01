# Mapa de registos:
# x: $s0
# y: 
# i: $s1
# result: $f4 
# abs(y): $v0
	.data
one:	.float 1.0
	.text
	.globl xtoy
	
xtoy:	addiu $sp,$sp,-12
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	
	move $s0,$a0
	li $s1,0
	l.s $f4,one
	
for:	jal aabs
	bge $s1,$v0,endf
	blez $s0,else
	mul.s $f4,$f4,$f12
	j eif
	
else:	div.s $f4,$f4,$f12

eif:	addiu $s1,$s1,1
	move $a0,$s0
	j for
	
endf:	mov.s $f0,$f4
	lw $s1,8($sp)
	lw $s0,4($sp)
	lw $ra,0($sp)
	addiu $sp,$sp,12
	jr $ra
