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
        andi $t2,$t2,0xFFF0     # meter RE0 a RE3 como output
        sw $t2,TRISE($t1)

do:     lw $t2,PORTB($t1)       # ler a configuração dos bits de input
        andi $t2,$t2,0x000F

        lw $t2,LATE($t1)
        andi $t2,$t2,0xFFF0     # dar reset
        or $t3,$t3,$t2

        sw $t3,LATE($t1)

        j do

        li $v0,0
        jr $ra
