    .data
    
    .equ SFR_BASE_HI,0xBF88
    
    .equ TRISB,0x6040
    .equ PORTB,0x6050
    .equ LATB, 0x6060
	
	.equ TRISE,0x6100
    .equ PORTE,0x6110
    .equ LATE, 0x6120

    
    .text
    .globl main
    
main:addi $sp,$sp,-12
    sw $ra,0($sp)
    sw $s0,4($sp)
    sw $s1,8($sp)
    
    #################
    
    lui $s0,SFR_BASE_HI
    lw $s1,TRISB($s0)
    
    ori $s1,$s1,0x000F
    
    sw $s1,TRISB($s0) #RB3 - RB0 input
	
	lw $s1,TRISE($s0)
    
    andi $s1,$s1,0xFF7F
    
    sw $s1,TRISE($s0) #RE7 output
    
    #################
	
	lw $s1,LATE($s0)
    
    ori $s1,$s1,0x0080
    
    sw $s1,LATE($s0) #RE7 ligado
    
while1:
    
    lw $s1,PORTB($s0)

    not $s1,$s1
    andi $s1,$s1,0x000F
	
	
    
if:bgt $s1,0x9,else
    addi $s1,$s1,0x30 # passar para asscii decimal
    j end_if
else:
    addi $s1,$s1,0x37 ## passar para asscii letras hex
end_if:
    
    li $v0,3
    move $a0,$s1
    syscall # putChar
    
	lw $s1,LATE($s0)   
    xori $s1,$s1,0x0080
    sw $s1,LATE($s0) #RE7 ligado
	
    li $a0,125
    jal delay
    
    j while1
    
    #################
    

    lw $ra,0($sp)
    lw $s0,4($sp)
    sw $s1,8($sp)
    addi $sp,$sp,12
    
    li $v0,0
    
    jr $ra


delay:    move $t0,$a0

for_delay:    ble $t0,$0,end_f_delay

        li $v0,12        
        syscall                    # resetCoreTimer();
        
while_delay:    li $v0,11        
        syscall
        blt $v0,40000,while_delay    # while(readCoreTimer() < 40000);
        
        addi $t0,$t0,-1 # ms--
        
        j for_delay
end_f_delay:
        jr $ra