	.data
	
	.equ SFR_BASE_HI,0xBF88
	.equ TRISE, 0x6100
	.equ PORTE, 0x6110
	.equ LATE, 0x6120
	
	.text
	.globl main
	
main:addi $sp,$sp,-8
	sw $ra,0($sp)
	sw $s0,4($sp)
	
	#################
	
	lui $s0,SFR_BASE_HI
	lw $s1,TRISE($s0)
	
	andi $s1,$s1,0xFFE0
	
	sw $s1,TRISE($s0) #RE0 - RE4 outputs
	
	#################
	
while1:
	
	li $v0,2
	syscall #getChar();
	
if: bne $v0,'0',elseif1

	##ligar led0
	lw $s1,LATE($s0)
	ori $s1,$s1,0x0001
	sw $s1,LATE($s0)
	
	j end
elseif1:bne $v0,'1',elseif2

	##ligar led1
	lw $s1,LATE($s0)
	ori $s1,$s1,0x0002
	sw $s1,LATE($s0)
	
	j end	
elseif2:bne $v0,'2',elseif3

	##ligar led2
	lw $s1,LATE($s0)
	ori $s1,$s1,0x0004
	sw $s1,LATE($s0)
	
	j end
elseif3:bne $v0,'3',else4

	##ligar led3
	lw $s1,LATE($s0)
	ori $s1,$s1,0x0008
	sw $s1,LATE($s0)
	
	j end	
else4:# outra tecla foi premida

	#ligar led4 por 2s e dps desligar todos os leds
	lw $s1,LATE($s0)
	ori $s1,$s1,0x0010
	sw $s1,LATE($s0)
	
	##delay(2)
	li $a0,2000
	jal delay
	
	lw $s1,LATE($s0)
	andi $s1,$s1,0xFFE0
	sw $s1,LATE($s0)
	
end:
	j while1
	
	#################
	
	lw $ra,0($sp)
	lw $s0,4($sp)
	addi $sp,$sp,8
	
	li $v0,0
	
	jr $ra


delay:	move $t0,$a0

for_delay:	ble $t0,$0,end_f_delay

		li $v0,12		
		syscall					# resetCoreTimer();
		
while_delay:	li $v0,11		
		syscall
		blt $v0,20000,while_delay	# while(readCoreTimer() < 20000);
		
		addi $t0,$t0,-1 # ms--
		
		j for_delay
end_f_delay:
		jr $ra
	
	