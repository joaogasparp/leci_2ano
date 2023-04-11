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

        lw $t2,TRISE($t1)
        andi $t2,$t2,0xFFE0     # meter a output
        sw $t2,TRISE($t1)

        lw $t0,LATE($t1)
        andi $t0,$t0,0xFFE0
        sw $t0,LATE($t1)

do:     li $v0,2                # getchar
        syscall

        beq $v0,'0',zero
        beq $v0,'1',um
        beq $v0,'2',dois
        beq $v0,'3',tres

        lw $t3,LATE($t1)        # inicializar o LATE
        andi $t3,$t3,0xFFF0     # primeiro dá reset
        ori $t3,$t3,0x0010      # fazer o resultado
        sw $t3,LATE($t1)        # escrever o resultado

        li $a0,2000
        addiu $sp,$sp,-4
        sw $ra,0($sp)
        jal delay
        lw $ra,0($sp)
        addiu $sp,$sp,4

        lw $t0,LATE($t1)
        andi $t0,$t0,0xFFE0
        sw $t0,LATE($t1)

        j do

zero:   lw $t3,LATE($t1)
        andi $t3,$t3,0xFFF0
        ori $t3,$t3,0x0001
        sw $t3,LATE($t1)
        j do

um:     lw $t3,LATE($t1)
        andi $t3,$t3,0xFFF0
        ori $t3,$t3,0x0002
        sw $t3,LATE($t1)
        j do

dois:   lw $t3,LATE($t1)
        andi $t3,$t3,0xFFF0
        ori $t3,$t3,0x0004
        sw $t3,LATE($t1)
        j do

tres:   lw $t3,LATE($t1)
        andi $t3,$t3,0xFFF0
        ori $t3,$t3,0x0008
        sw $t3,LATE($t1)
        j do

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
