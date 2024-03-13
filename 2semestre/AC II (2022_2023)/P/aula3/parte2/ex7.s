# (1/frequency)*1000=miliseconds
# (1/1.5)*1000=miliseconds
# 666miliseconds
#

        .equ SFR_BASE_HI,0xBF88
        .equ TRISE,0x6100
        .equ PORTE,0x6110
        .equ LATE,0x6120
        .equ TRISB,0x6040
        .equ PORTB,0x6050
        .equ LATB,0x6060
        .data
        .text
        .globl main

main:   li $t0,0                # $t0 = 0

        lui $t1,SFR_BASE_HI
        lw $t2,TRISE($t1)       # obter configuracao de bits
        andi $t2,$t2,0xFFF0     # 1111 1111 1111 0000 -> RE0 a RE3 a 0, ou seja, saídas
        sw $t2,TRISE($t1)       # guardar configuracao

        lw $t2,TRISB($t1)       # obter configuracao de bits
        andi $t2,$t2,0xFFF0     # (reset)
        ori $t2,$t2,0x000F      # 0000 0000 0000 1111 -> RB0 a RE3 a 1, ou seja, entradas
        sw $t2,TRISB($t1)       # guardar configuracao

while:  lw $t3,LATE($t1)        # obter configuracao de bits
        andi $t3,$t3,0xFFF0     # (reset)
        or $t3,$t3,$t0          # LATE0(RE0) = $t0
        sw $t3,LATE($t1)        # guardar configuracao

        addiu $sp,$sp,-4        #
        sw $ra,0($sp)           #
        li $a0,666              # $a0 = 666
        jal delay               # delay($a0)
        lw $ra,0($sp)           #
        addiu $sp,$sp,4         #

        lw $t3,PORTB($t1)
        andi $t3,$t3,0x0004     # 0000 0000 0000 0100 -> PORTB2(RB2) a 1, ou seja, a ler o input RB2

if:     beq $t3,0x0004,else     # if(RB2 == 0x0004) salta para else
        xori $t4,$t0,0x0001     # bit menos significativo negado
        srl $t4,$t4,3           # 1000 >> 0001
        sll $t0,$t0,1           # 0001 << 0010
        andi $t0,$t0,0x000F     # 0010*1111=0010
        andi $t4,$t4,0x000F     # 0010*1111=0010
        or $t0,$t0,$t4          # 0010+0001=0011
        
        j while

else:   xori $t4,$t0,0x0008     # bit mais significativo negado
        srl $t4,$t4,3           # 1000 >> 0001
        sll $t0,$t0,1           # 0001 << 0010
        andi $t0,$t0,0x000F     # 0010*1111=0010
        or $t0,$t0,$t4          # 0010+0001=0011       

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