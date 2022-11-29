	.text
	.globl toascii
	
toascii:or $t0,$t0,'0'
	
if:	ble $t0,'9',endif
	addi $t0,$t0,7

endif:	move $v0,$t0
	jr $ra