# Mapa de registos:
# $t0 – value
# $t1 – bit
# $t2 - i
	.data
str1: .asciiz "Introduza um numero: "
str2: .asciiz "\nO valor em binário é: "
	.eqv print_string,4
	.eqv read_int,5
	.eqv print_char,11
	.text
	.globl main
	
main:   la $a0,str1
	li $v0,4 # (instrução virtual)
	syscall # print_string(str1);
	li $v0,5 # value=read_int();
	syscall
	or $t0,$0,$v0 # value = $t0
	li $v0,4 # print_string("...");
	la $a0,str2
	syscall
	li $t2,0 # i = 0
	
for:    bge $t2,32,endfor # while(i < 32) {
	srl $t1,$t0,31 # (instrução virtual)
	
if:	rem $t3,$t2,4
	bne $t3,0,ascii
	li $v0,11 # print_char(' ');
	li $a0,' '
	syscall
	
ascii:	li $v0,11
	addi $a0,$t1,0x30
	syscall # print_char('0' + bit);
	
	sll $t0,$t0,1
	addi $t2,$t2,1
	j for # }
	
endfor: jr $ra # fim do programa
