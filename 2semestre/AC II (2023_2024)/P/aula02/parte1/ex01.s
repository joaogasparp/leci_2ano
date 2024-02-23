        .equ READ_CORE_TIMER,11
        .equ RESET_CORE_TIMER,12
        .equ PUT_CHAR,3
        .equ PRINT_INT,6
        .data
        .text
        .globl main

main:   li $t0,0                # counter = 0
        li $t1,200000           # counterFrequency = 100Hz
        # li $t1,2000000 # counterFrequency = 1/2000000 * 20000000 = 10Hz
        # li $t1,4000000 # counterFrequency = 5Hz
        # li $t1,20000000 # counterFrequency = 1Hz
        
while1: li $v0,RESET_CORE_TIMER     # reset the core timer
        syscall

while2: li $v0,READ_CORE_TIMER      # read the core timer
        syscall
        bge $v0,$t1,while1          # if counterFrequency is reached, go to while1
        addi $t0,$t0,1              # counter++

        move $a0,$t0
        li $a1,0x0004000A
        li $v0,PRINT_INT
        syscall

        li $a0,'\r'                 # print a new line
        li $v0,PUT_CHAR
        syscall

        j while1                    # go to while1

        li $v0,0

        jr $ra
