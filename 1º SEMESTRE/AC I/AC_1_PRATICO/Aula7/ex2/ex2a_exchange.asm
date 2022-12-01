	.text
	.globl exchange
	
exchange:	lb $t0,0($a0)
		lb $t1,0($a1)
		sb $t0,0($a1)
		sb $t1,0($a0)
		
		jr $ra