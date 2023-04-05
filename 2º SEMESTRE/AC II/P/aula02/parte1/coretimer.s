# a)
        # 20 000 000 -- 1 segundo
        # 200 000 -- 0,01 segundos
        # counterFrequency = 1/0.01 = 100Hz

# b)
        .equ READ_CORE_TIMER,11
        .equ RESET_CORE_TIMER,12
        .equ PUT_CHAR,3
        .equ PRINT_INT,6
        .data
        .text
        .globl main

main:   li $t0,0
        li $t1,200000
        # li $t1,2000000 # counterFrequency = 1/2000000 * 20000000 = 10Hz
        # li $t1,4000000 # counterFrequency = 5Hz
        # li $t1,20000000 # counterFrequency = 1Hz
        
while1: li $v0,RESET_CORE_TIMER
        syscall

while2: li $v0,READ_CORE_TIMER
        syscall
        bge $v0,$t1,while1
        addi $t0,$t0,1

        move $a0,$t0
        li $a1,0x0004000A
        li $v0,PRINT_INT
        syscall

        li $a0,'\r'
        li $v0,PUT_CHAR
        syscall

        j while1

        li $v0,0

        jr $ra