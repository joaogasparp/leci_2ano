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

    .data
    .text
    .globl main

main:

    lui     $t1, SFR_BASE_HI    #Base

    lw      $t2, TRISE($t1)        
    andi    $t2, $t2, 0xFFFE    # MODIFY RE0 = out(0)
    sw      $t2, TRISE($t1)     

    lw      $t2, TRISD($t1)    
    ori     $t2, $t2, 0x0100    # MODIFY RD8= in(1)
    sw	    $t2, TRISD($t1)

loop:                           #while(1)                                        

    lw      $t2, PORTD($t1)     
    andi    $t2, $t2, 0x0100    #RD8 ler(PORT)
    srl     $t2, $t2, 8         #RD8 >> 8

    lw      $t3, LATE($t1)
    andi    $t3, $t3, 0xFFFE    #RE0= 0
    or      $t3, $t2, $t3      
    sw      $t3, LATE($t1)      #RE0 = RD8

    j       loop

    
    li      $v0, 0              #return 0;
    jr      $ra
