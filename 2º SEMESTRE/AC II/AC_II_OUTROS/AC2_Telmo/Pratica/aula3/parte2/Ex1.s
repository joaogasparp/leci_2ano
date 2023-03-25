    .equ SFR_BASE_HI, 0xBF88
    .equ TRISB, 0x6040
    .equ PORTB, 0x6050
    .equ LATB, 0x6060
    .equ TRISE, 0x6100
    .equ PORTE, 0x6110
    .equ LATE, 0x6120
    .equ TRISD, 0x60C0
    .equ PORTD, 0x60D0
    .equ LATD, 0x60E0
    .equ resetCoreTimer, 12
    .equ readCoreTimer, 11

    .data
    .text
    .globl main

main:

    addi    $sp, $sp, -20
    sw      $ra, 0($sp)
    sw      $s0, 4($sp)
    sw      $s1, 8($sp)
    sw      $s2, 12($sp)
    sw      $s3, 16($sp)
    
    lui     $s0, SFR_BASE_HI    #Base
    li      $s3, 0              #count = 0

    lw      $s1, TRISE($s0)        
    andi    $s1, $s1, 0xFFF0    # MODIFY RE0 a 3= out(0)
    sw      $s1, TRISE($s0)     

loop:                           #while(1)                                        

    
    lw      $s2, LATE($s0)
    andi    $s2, $s2, 0xFFF0    #RE= 0
    or      $s2, $s2, $s3    
    sw      $s2, LATE($s0)      #RE = count

    addi    $s3, $s3, 1         #count ++
    andi    $s3, $s3, 0x000F    #count <16
    

    li $a0, 1000                #1hz
    jal delay                   #delay(1000)


    j       loop

    
    lw      $ra, 0($sp)
    lw      $s0, 4($sp)
    lw      $s1, 8($sp)
    lw      $s2, 12($sp)
    lw      $s3, 16($sp)
    addi    $sp, $sp, 20

    
    li      $v0, 0              #return 0;
    jr      $ra

###########################
delay:
    li $v0, resetCoreTimer
    syscall
whiled:
    li $v0, readCoreTimer
    syscall

    li $t0, 20000	# k 
    mul $t0, $a0, $t0	#k *ms
    blt $v0, $t0, whiled
    jr $ra