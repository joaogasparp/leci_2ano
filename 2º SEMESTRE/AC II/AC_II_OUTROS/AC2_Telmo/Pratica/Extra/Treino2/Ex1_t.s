    .equ SFR_BASE_HI, 0xBF88
    .equ TRISE, 0x6100
    .equ PORTE, 0x6110
    .equ LATE, 0x6120

    .equ resetCoreTimer, 12
    .equ readCoreTimer, 11
    .equ inkey, 1

    .data
    .text
    .globl main
main:

    addiu $sp, $sp, -12
    sw $ra, 0($sp)
    sw $s0, 4($sp)
    sw $s1, 8($sp)

    lui $s0, SFR_BASE_HI

    lw $s1, TRISE($s0)
    andi $s1, $s1, 0xFFE0
    sw $s1, TRISE($s0)

loop:

    li $v0, inkey
    syscall

if:
    bne $v0, '0', else1
    lw $s1, LATE($s0)
    ori $s1, $s1, 0x0001
    sw $s1, LATE($s0)

    j endif

else1:
    bne $v0, '1', else2
    lw $s1, LATE($s0)
    ori $s1, $s1, 0x0002
    sw $s1, LATE($s0)

    j endif

else2:
    bne $v0, '2', else3
    lw $s1, LATE($s0)
    ori $s1, $s1, 0x0004
    sw $s1, LATE($s0)

    j endif

else3:
    bne $v0, '3', else4
    lw $s1, LATE($s0)
    ori $s1, $s1, 0x0008
    sw $s1, LATE($s0)
    
    j endif

else4:

    beq $v0, $0, endif
    lw $s1, LATE($s0)
    ori $s1, $s1, 0x0010
    sw $s1, LATE($s0)

    li $a0, 2000
    jal delay

    lw $s1, LATE($s0)
    andi $s1, $s1, 0x0000
    sw $s1, LATE($s0)


endif: 
    j loop

    lw $ra, 0($sp)
    lw $s0, 4($sp)
    lw $s1, 8($sp)
    addiu $sp, $sp, 12 

    li $v0, 0
    jr $ra


##############################
delay:

    li $v0, resetCoreTimer
    syscall

while:
    li $v0, readCoreTimer
    syscall

    mul $t0, $a0, 20000
    blt $v0, $t0, while

    jr $ra
