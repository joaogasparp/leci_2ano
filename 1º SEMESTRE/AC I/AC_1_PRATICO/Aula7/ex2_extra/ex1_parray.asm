# Mapa de registos
# *a: $s0
# n: $t0
# *p: $s1

	.data
	.eqv print_int10,1
	.eqv print_string,4
str1:	.asciiz ", "
	.text
	.globl parray
	
parray:	addiu $sp,$sp,-12
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	
	move $s0,$a0
	sll $t0,$a1,2
	addu $s1,$s0,$t0
	
for:	bge $s0,$s1,endfor
	li $v0,print_int10
	lw $a0,0($s0)
	syscall
	li $v0,print_string
	la $a0,str1
	syscall
	addiu $s0,$s0,4
	j for
	
endfor:	lw $ra,0($sp)
	lw $s0,4($sp)
	lw $s1,8($sp)
	addiu $sp,$sp,12
	
	jr $ra