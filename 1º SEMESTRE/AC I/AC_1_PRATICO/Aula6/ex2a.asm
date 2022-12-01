# SIZE: $t0
# p: $t1
# pultimo: $t2
	.data
	.eqv SIZE,3
array:	.word str1,str2,str3
str1:	.asciiz "Array"
str2:	.asciiz "de"
str3:	.asciiz "ponteiros"
	.eqv print_string,4
	.eqv print_char,11
	.text
	.globl main
	
main:	la $t1,array # $t1 = p = &array[0] = array
	li $t0,SIZE # $t0 = SIZE
	sll $t0,$t0,2 # $t0 = SIZE * 4
	addu $t2,$t1,$t0 # $t2 = pultimo = array + SIZE
	
for:	bge $t1,$t2,endf
	lw $a0,0($t1) # $a0 = *p
	li $v0,print_string
	syscall
	li $a0,'\n'
	li $v0,print_char
	syscall	
	addiu $t1,$t1,4
	j for

endf:	jr $ra