# Mapa de registos
# a: $t0
# b: $t1
	.data
	.eqv print_int10,36
	.text	
	.globl main
	
main:	li $t0,3
	li $t1,8
	ble $t0,$t1,endif
	beqz $t1,endif
	
if:	sll $t2,$t1,2
	j end

endif:	and $t3,$t0,$t1
	or $t4,$t0,$t1
	xor $t2,$t3,$t4
	
end:	or $a0,$0,$t2
	li $v0,36
	syscall
	
	jr $ra