# Mapa de registos
# a: $t0
# b: $t1
# c: $t2
	.data
str1:	.asciiz "Introduza um número (valor de \"a\"): "
str2:	.asciiz "Introduza um número (valor de \"b\"): "
str3:	.asciiz "Introduza um número (valor de \"c\"): "
	.eqv print_int10,36
	.eqv print_string,4
	.eqv read_int,5
	.text	
	.globl main
	
main:	la $a0,str1
	li $v0,4
	syscall
	li $v0,5
	syscall
	or $t0,$0,$v0
	
	la $a0,str2
	li $v0,4
	syscall
	li $v0,5
	syscall
	or $t1,$0,$v0
	
	la $a0,str3
	li $v0,4
	syscall
	li $v0,5
	syscall
	or $t2,$0,$v0
	
	bgt $t0,3,if
	bgt $t1,$t2,endif
	
if: 	add $t3,$t0,$t1
	sub $t2,$t2,$t3
	j end
	
endif:	sub $t3,$t0,5
	add $t2,$t2,$t3

end:	or $a0,$t0,$t2
	li $v0,36
	syscall
	
	jr $ra