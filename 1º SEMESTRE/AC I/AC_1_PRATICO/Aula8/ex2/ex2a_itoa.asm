	# Mapa de registos
	# n: $a0 -> $s0
	# b: $a1 -> $s1
	# s: $a2 -> $s2
	# p: $s3
	# digit: $t0
	# Sub-rotina intermédia
	.text
	.globl itoa
	
itoa: 	addiu $sp,$sp,-16 # reserva espaço na stack
	sw $s0,0($sp) # guarda registos $sx e $ra
	sw $s1,4($sp)
	sw $s2,8($sp)
	sw $ra,12($sp)
	move $s0,... # copia n, b e s para registos
	(...) # "callee-saved"
	move $s3,$a2 # p = s;
	
do: 	# do {
	(...) #
	b?? $s0,... # } while(n > 0);
	sb $0,0($s3) # *p = 0;
	(...) #
	jal strrev # strrev( s );
	(...) # return s;
	lw $s0,... # repõe registos $sx e $ra
	(...)
	addiu $sp,... # liberta espaço na stack
	jr $ra #