    .equ SFR_BASE_HI, 0xBF88
    .equ TRISB, 0x6040
    .equ PORTB, 0x6050
    .equ LATB, 0x6060
    .equ TRISE, 0x6100
    .equ PORTE, 0x6110
    .equ LATE, 0x6120


    .equ resetCoreTimer, 12
    .equ readCoreTimer, 11
    .equ putChar, 3
    .equ printInt, 6
    .equ inkey, 1

    
    .data
    .text
    .globl main
main:

    addi $sp, $sp, -12
    sw $ra, 0($sp)
    sw $s0, 4($sp)
    sw $s1, 8($sp)


    lui $s0, SFR_BASE_HI

    #porto B
    lw $s1, TRISB($s0)
    ori $s1, $s1, 0x000F
    sw $s1, TRISB($s0)

    #port E
    lw $s1, TRISE($s0)
    andi $s1, $s1, 0xFF7F
    sw $s1, TRISE($s0)

    #LED LIGADO
    lw $s1, LATE($s0)
    ori $s1, $s1, 0x0080            
    sw $s1, LATE($s0)

loop:

    lw $s1, PORTB($s0)
    andi $s1, $s1, 0x000F

    xori $s1, $s1, 0x000F   #negado


if:
    bgt $s1, 0x0009,else
    addi $s1, $s1, 0x30
    j endif
else:
    addi $s1, $s1, 0x37
endif:

    move $a0, $s1
    li $v0, putChar
    syscall

    li $a0, '\r'
    li $v0, putChar
    syscall

    #LED complementado
    lw $s1, LATE($s0)
    xori $s1, $s1, 0x0080
    sw $s1, LATE($s0)

    li $a0,125          # 1s / 4 = 0.25   -> 250/2 = 125 s
    jal delay

    j loop

    lw $ra, 0($sp)
    lw $s0, 4($sp)
    lw $s1, 8($sp)
    addi $sp, $sp, 12

    li $v0, 0
    jr $ra

##########################
delay:

    li $v0, resetCoreTimer
    syscall

while:
    li $v0, readCoreTimer
    syscall

    mul $t0, $a0, 40000         #2ms
    blt $v0, $t0, while

    jr $ra
