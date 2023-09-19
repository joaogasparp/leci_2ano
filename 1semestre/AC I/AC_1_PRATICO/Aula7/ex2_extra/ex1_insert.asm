# Mapa de registos:
# *array: $a0
# value: $a1
# pos: $a2
# size: $a3

	.data
	.text
	.globl insert
	
insert:	ble $a2,$a3,else
	li $v0,1
	j end
	
else:	sub $t0,$a3,1
	
for:	blt $t0,$a2,endfor
	sll $t1,$t0,2		# $t1 = i*4
	addu $t2,$a0,$t1	# $t2 = array+i
	lw $t3,0($t2)		# $t3 = array[i]
	sw $t3,4($t2)		# array[i+1] = array[i]
	sub $t0,$t0,1
	j for			

endfor:	sll $t1,$a2,2
	addu $t2,$a0,$t1
	sw $a1,0($t2)
	li $v0,0
	
end:	jr $ra