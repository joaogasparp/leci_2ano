	.data
	.text
	.globl main
main:   ori $t0,$0,0xe543
	xori $t1,$t0,0xffffffff 
	jr $ra