# Mapa de registos
# nodd: $t0
# i: $t1

	.data
	.eqv SIZE,7
	.eqv print_string,4
	.eqv print_int10,1
str:	.asciiz "Result is: "
val:	.word 7,4,15,-1987,9,27,16
odd:	.space 28
	.text
	.globl main
	
main:	