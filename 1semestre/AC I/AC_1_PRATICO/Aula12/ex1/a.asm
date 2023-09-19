	.data
std:	.space 176
	.eqv MAX_STUDENTS,4
	.eqv print_string,4
	
	.text
	.globl main
	
main:	la $t0,std
	la $t1,MAX_STUDENTS

	jr $ra
	
