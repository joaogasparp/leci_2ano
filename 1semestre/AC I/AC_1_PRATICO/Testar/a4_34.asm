# Mapa de registos
# k: $t0
	.data
	.eqv print_int10,36
	.text	
	.globl main
	
main:	li $t0,500

for:	bge $t0,1000,end
	addi $t0,$t0,10
	j for

end:	or $a0,$0,$t0
	li $v0,36
	syscall
	
	jr $ra