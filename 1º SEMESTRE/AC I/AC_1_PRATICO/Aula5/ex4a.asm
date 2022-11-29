# Mapa de registos
# *p: $t0
# *(p+1): $t1
# aux: $t2
# houve_troca: $t4
# p: $t5
# pUltimo: $t6

	.data
	.eqv SIZE,10
lista:	.space 40
	.eqv read_int,5
	.eqv print_int10,1
	.eqv print_char,11
	.eqv TRUE,1
	.eqv FALSE,0
	.text
	.globl main
	
main 