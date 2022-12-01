	.data
	.text
	.globl main
main:   ori $t0,$0,0x5c1b
	ori $t1,$0,0xa3e4
	and $t2,$t0,$t1
	or $t3,$t0,$t1
	nor $t4,$t0,$t1
	xor $t5,$t0,$t1
	jr $ra