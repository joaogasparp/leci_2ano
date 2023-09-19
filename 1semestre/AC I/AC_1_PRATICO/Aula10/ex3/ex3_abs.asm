# Mapa de registos:
# val: $a0
	.text
	.globl aabs
	
aabs:	bgez $a0,enda
	li $t0,0
	sub $a0,$t0,$a0

enda:	move $v0,$a0
	jr $ra
