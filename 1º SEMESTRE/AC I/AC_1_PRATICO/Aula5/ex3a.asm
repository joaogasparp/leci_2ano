# Mapa de registos
# p1: $t0
# *p1: $t1
# houve_troca: $t4
# i: $t5
# lista: $t6
# lista + i: $t7

	.data
	.eqv SIZE,10
	.eqv TRUE,1
	.eqv FALSE,0
lista:	.space 40
	.eqv read_int,5
str1:	.asciiz "Introduza um número: "
str2:	.asciiz "\nNúmeros por ordem crecente: "
	.eqv print_string,4
	.eqv print_int10,1
	.eqv print_char,11
	.text
	.globl main
	
main: 	la $t0,lista # $t0 = lista ou &lista[0]
 	li $t1,SIZE # $t1 = SIZE
 	sll $t1,$t1,2 # $t1 = SIZE * 4
 	addu $t1,$t1,$t0 # $t1 = lista + SIZE * 4
 	
while:	bge $t0,$t1,endw #
	la $a0,str1
	li $v0,4
	syscall
	li $v0,5
	syscall
	sw $v0,0($t0)
	addiu $t0,$t0,4
	j while	
	
endw:	la $t6,lista
	
do: 				# do { 
 	li $t4,FALSE 		# houve_troca = FALSE; 
	li $t5,0 		# i = 0; 
	
	li $t3,SIZE
	sub $t3,$t3,1
	
for: 	bge $t5,$t3,endf 	# while(i < SIZE-1){ 
if: 	sll $t7,$t5,2 		# $t7 = i * 4 
 	addu $t7,$t7,$t6 	# $t7 = &lista[i] 
 	lw $t8,0($t7) 		# $t8 = lista[i] 
 	lw $t9,4($t7) 		# $t9 = lista[i+1] 
 	ble $t8,$t9,endif 	# if(lista[i] > lista[i+1]){ 
 	sw $t8,4($t7) 		# lista[i+1] = $t8 
 	sw $t9,0($t7) 		# lista[i] = $t9 
 	li $t4,TRUE 
 				# }
endif: 	addi $t5,$t5,1 		# i++;
 	j for 			# }
 	
endf:	beq $t4,TRUE,do 	# } while(houve_troca == TRUE);
 	
	li $t5,0		# i = 0
	la $t6,lista 	
	
	li $t3,SIZE
	
prt:	bge $t5,$t3,endpt
	sll $t7,$t5,2
	addu $t7,$t7,$t6
	lw $a0,0($t7)
	li $v0,print_int10
	syscall
	li $v0,print_char
	li $a0,';'
	syscall
	addi $t5,$t5,1
	j prt
 				
endpt: 	jr $ra 			# termina o programa 
