#

	.data
	.text
	.globl stdev
	
stdev:	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	jal var
	mov.d $f12,$f0
	jal sqrt
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	jr $ra