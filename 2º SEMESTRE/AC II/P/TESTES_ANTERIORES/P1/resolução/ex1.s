    .equ SFR_BASE_HI,0xBF88
    .equ TRISB,0x6040
    .equ PORTB,0x6050
    .equ LATB, 0x6060
	.equ TRISE,0x6100
    .equ PORTE,0x6110
    .equ LATE, 0x6120
    .data
    .text
    .globl main

main:   lui $t1,SFR_BASE_HI
        lw $t2,TRISB($t1)
        ori $t2,$t2,0x000F
        sw $t2,TRISB($t1)

        lw $t2,TRISE($t1)
        andi $t2,$t2,0xFF7F
        sw $t2,TRISE($t1)

        lw $t2,LATE($t1)
        ori $t2,$t2,0x0080
        sw $t2,LATE($t1)

while:  lw $t2,PORTB($t1)
        not $t2,$t2
        andi $t2,$t2,0x000F
        
if:     bgt $t2,0x9,else
        addi $t2,$t2,0x30       # passar a decimal
        j end

else:   addi $t2,$t2,0x37

end:    li $v0,3
        move $a0,$t2
        syscall

        lw $t2,LATE($t1)
        xori $t2,$t2,0x0080
        sw $t2,LATE($t1)

        addiu $sp,$sp,-4
        sw $ra,0($sp)
        li $a0,2
        jal delay
        lw $ra,0($sp)
        addiu $sp,$sp,4

        j while

        li $v0,0
        jr $ra

######

delay:  li $v0,12
        syscall

whiled: li $v0,11
        syscall
        mul $a0,$a0,20000
        blt $v0,$a0,whiled
        jr $ra
