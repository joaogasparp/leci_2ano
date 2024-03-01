# TRISx é usado para configurar os portos com entrada ou saída
# para configurar como entrada tem de ser colocado a 1
# PORTx é usado para ler nos portos configurados com saída
# LATx é usado para escrever nos portos configurados com entrada

        .equ ADDR_BASE_HI, 0xBF88
        .equ TRISB, 0x6040
        .equ PORTB, 0x6050
        .equ LATB, 0x6060
        .equ TRISE, 0x6100
        .equ PORTE, 0x6110
        .equ LATE, 0x6120
        .data
        .text
        .globl main

main:   lui $t1,ADDR_BASE_HI    # $t1 = 0xBF88

        lw $t2,TRISE($t1)       # MODIFY RE0 = out(0)
        andi $t2,$t2,0xFFFE     # MODIFY RE0 = out(0)
        sw $t2,TRISE($t1)       # MODIFY RE0 = out(0)

        lw $t2,TRISB($t1)       # MODIFY RB0 = in(1)
        ori $t2,$t2,0x0001      # MODIFY RB0 = in(1)
        sw $t2,TRISB($t1)       # MODIFY RB0 = in(1)

while:  lw $t2,PORTB($t1)       # RB0 ler(PORT)
        andi $t2,$t2,0x0001     # ler o primeiro porto daí estar a 1

        lw $t3,LATE($t1)        # RE0 escrever(PORT)                
        andi $t3,$t3,0xFFFE     # RE0 = 0
        or $t3,$t2,$t3          # RE0 = RB0
        sw $t3,LATE($t1)        # RE0 = RB0

        j while

        li $v0,0                # return 0
        jr $ra