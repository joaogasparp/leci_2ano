        .equ SFR_BASE_HI,0xBF88
        .equ TRISB,0x6040
        .equ PORTB,0x6050
        .equ LATB,0x6060
        .equ TRISC,0x6080
        .equ PORTC,0x6090
        .equ LATC,0x60A0
        .equ TRISD,0x60C0
        .equ PORTD,0x60D0
        .equ LATD,0x60E0
        .equ TRISE,0x6100
        .equ PORTE,0x6110
        .equ LATE,0x6120
        .data
        .text
        .globl main

main:   lui $t1,SFR_BASE_HI

        lw $t2,TRISB($t1)
        ori $t2,$t2,0x000F     # meter RB0 a RB3 como input
        sw $t2,TRISB($t1)

        lw $t2,TRISE($t1)
        andi $t2,$t2,0xFF00     # meter RE0 a RE3 como output
        sw $t2,TRISE($t1)

do:     lw $t0,PORTB($t1)
        andi $t0,$t0,0x000F
        xori $t0,$t0,0x000F

        lw $t2,PORTB($t1)       # ler a configuração dos bits de input
        andi $t2,$t2,0x0008
        srl $t2,$t2,1

        lw $t3,PORTB($t1)
        andi $t3,$t3,0x0004
        srl $t3,$t3,3

        lw $t4,PORTB($t1)
        andi $t4,$t4,0x0002
        sll $t4,$t4,5

        lw $t5,PORTB($t1)
        andi $t5,$t5,0x0001
        sll $t5,$t5,7

        lw $t6,LATE($t1)
        andi $t6,$t6,0xFF00

        or $t7,$t7,$t0
        or $t7,$t7,$t2
        or $t7,$t7,$t3
        or $t7,$t7,$t4
        or $t7,$t7,$t5

        sw $t7,LATE($t1)        # write

        j do

        li $v0,0
        jr $ra
