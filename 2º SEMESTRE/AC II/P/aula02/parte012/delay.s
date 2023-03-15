        .equ READ_CORE_TIMER,11
        .equ RESET_CORE_TIMER,12
        .equ PUT_CHAR,3
        .equ PRINT_INT,6
        .equ time,10
        .data
        .text
        .globl main

main:   li $t0,0

while1: li $v0,RESET_CORE_TIMER
        syscall

        li $a0,time
        j delay

end:    move $a0,$t0
        li $a1,0x0004000A
        li $v0,PRINT_INT
        syscall
        addi $t0,$t0,1

        li $a0,'\r'
        li $v0,PUT_CHAR
        syscall

        j while1

        jr $ra


delay:  move $t1,$a0

        li $v0,RESET_CORE_TIMER
        syscall

while2: li $v0,READ_CORE_TIMER
        syscall
        blt $v0,20000,while2

        j end
