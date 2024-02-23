# a)    (1/frequency)*1000=miliseconds
#       (1/frequency)*1000=500miliseconds
#       frequency=2Hz
#
# d)    (1/frequency)*1000=10miliseconds
#       frequency=100Hz

        .equ SFR_BASE_HI,0xBF88
        .equ TRISB,0x6040
        .equ PORTB,0x6050
        .equ LATB,0x6060
        .equ TRISE,0x6100
        .equ PORTE,0x6110
        .equ LATE,0x6120
        .equ TRISD,0x60C0
        .equ PORTD,0x60D0
        .equ LATD,0x60E0
        .data
        .text
        .globl main

main:   li $t0,0x0000                   # int v = 0
        lui $t1,SFR_BASE_HI
        lw $t2,TRISE($t1)               # READ  (Mem_addr = 0xBF880000 + 0x6100) -> obter configuracao de bits 
        andi $t2,$1,0xFFF6              # MODIFY (bit0= (0 means OUTPUT)) -> meter bit 0 como output, logo, a 0
        sw $t2,TRISE($t1)               # WRITE (Write TRISE register) -> guardar configuracao

        lw $t2,TRISD($t1)
        andi $t2,$t2,0xFFF6             # TRISD0 = 0
        sw $t2,TRISD($t1)

while:  lw $t3,LATE($t1)                # obter configuracao de bits
        andi $t3,$t3,0xFFF6             # (reset) meter bit 0 como output, logo, a 0
        or $t3,$t3,$t0                  # LATE0 = v
        sw $t3,LATE($t1)                # guardar configuracao

        lw $t3,LATD($t1)
        andi $t3,$t3,0xFFFE
        or $t3,$t3,$t0
        sw $t3,LATD($t1)

        addiu $sp,$sp,-4
        sw $ra,0($sp)
        li $a0,500
        jal delay
        lw $ra,0($sp)
        addiu $sp,$sp,4

        xori $t0,$t0,1
        j while

        li $v0,0
        jr $ra

#

delay:  li $v0,RESET_CORE_TIMER
        syscall

whiled: li $v0,READ_CORE_TIMER
        syscall
        mul $a0,$a0,20000
        ble $v0,$a0,while2
        jr $ra
