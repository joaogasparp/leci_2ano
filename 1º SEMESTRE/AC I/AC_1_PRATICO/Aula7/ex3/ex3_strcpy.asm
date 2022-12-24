# Mapa de registos
# i:		$t0
# src+i:	$t1
# src[i]:	$t2
# dst+i:	$t3
	
	.data
	.text
	.globl strcpy

strcpy:	li $t0,0			# i = 0

do:	addu $t1,$a1,$t0		#	// do { $t1 = src+i
	lb $t2,0($t1)			#	// $t2 = src[i]
	addu $t3,$a0,$t0		#	// $t3 = dst+i
	sb $t2,0($t3)			#	dst[i] = src[i]
	addi $t0,$t0,1			#	// i++
	bne $t2,'\0',do			# } while(src[i++] != '\0');
	move $v0,$a0			# return dst
	
	jr $ra