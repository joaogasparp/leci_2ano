# Mapa de registos:
# *st: $a0, $t0
# ns: $a1, $t1
	
	.data
	.eqv print_string,4
	.eqv read_int,5
	.eqv read_string,8
	.eqv read_float,6
mec:	.asciiz "N. Mec.: "
pnome:	.asciiz "Primeiro Nome: "
lnome:	.asciiz "Último Nome: "
nota:	.asciiz ""
	.text
	.globl main
	
main:	move $t0,$a0
	move $t1,$a1
	li $t2,0
	
for:	bge $t2,$t1,fin
	
# print mec
	la $a0,mec
	li $v0,4
	syscall
# read mec
	li $v0,5
	syscall
	sw $v0,0($t0)
	
# print pnome
	la $a0,pnome
	li $v0,4
	syscall
# read pnome
	li $v0,8
	addi $a0,$t0,4
	li $a1,18
	syscall
	
# print lnome
	la $a0,lnome
	li $v0,4
	syscall
# read lnome
	li $v0,8
	addi $a0,$t0,22
	li $a1,15
	syscall
	
# print nota
	la $a0,nota
	li $v0,4
	syscall
# read nota
	li $v0,6
	syscall
	s.s $f0,40($t0)	
		
	addiu $t2,$t2,4
	j for
	
fin:	jr $ra