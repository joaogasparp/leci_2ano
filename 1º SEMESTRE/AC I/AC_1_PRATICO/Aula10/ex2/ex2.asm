################

	.data
	.eqv print_double,3
	.eqv print_string,4
	.eqv read_double,7
str1:	.asciiz "X: "
str2:	.asciiz "Square root of X: "
	.text
	.globl main
	
main:	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	li $v0,print_string
	la $a0,str1
	syscall
	
	li $v0,read_double
	syscall
	mov.d $f12,$f0
	jal sqrt
	
	li $v0,print_string
	la $a0,str2
	syscall
	
	mov.d $f12,$f0
	li $v0,print_double
	syscall
	
	li $v0,0
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	jr $ra

################
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