# Mapa de registos
# i:		$t0
# a:		$s0
# a+i:		$t1
# var_r:	
# stdev_r:	$f12
	
	.data
	.eqv print_double, 3
	.eqv print_string, 4
	.eqv read_double, 7
	.eqv print_char, 11
	.eqv SIZE, 10
str1:	.asciiz "\nvar: "
str2:	.asciiz "\nstdev: "
	.align 3
a:	.space 80
	.text
	.globl main
	
main:	addiu $sp,$sp,-8
	sw $ra,0($sp)
	sw $s0,4($sp)
	la $s0,a
	li $t0,0
	
for:	bge $t0,SIZE,endfor
	li $v0,read_double
	syscall
	sll $t1,$t0,3
	addu $t1,$s0,$t1
	s.d $f0,0($t1)
	addi $t0,$t0,1
	j for		

endfor:	move $a0,$s0
	li $a1,SIZE
	jal var
	mov.d $f12,$f0
	li $v0,print_string
	la $a0,str1
	syscall
	li $v0,print_double
	syscall
	move $a0,$s0
	li $a1,SIZE
	jal stdev
	mov.d $f12,$f0
	li $v0,print_string
	la $a0,str2
	syscall
	li $v0,print_double
	syscall
	li $v0,0
	
	lw $ra,0($sp)
	lw $s0,4($sp)
	addiu $sp,$sp,8
	jr $ra
