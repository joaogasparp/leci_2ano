        .equ READ_CORE_TIMER,11
        .equ RESET_CORE_TIMER,12
        .equ PUT_CHAR,3
        .equ PRINT_INT,6
        .equ time,10
        .data
        .text
        .globl main

main:   li $t0,0                    # counter = 0

while1: li $v0,RESET_CORE_TIMER  
        syscall

        li $a0,time                 # delay
        j delay

end:    move $a0,$t0                # print counter
        li $a1,0x0004000A
        li $v0,PRINT_INT
        syscall
        addi $t0,$t0,1              # counter++  

        li $a0,'\r'                 # print new line
        li $v0,PUT_CHAR
        syscall

        j while1

        jr $ra


delay:  move $t1,$a0                # delay = a0

        li $v0,RESET_CORE_TIMER     # reset timer
        syscall

while2: li $v0,READ_CORE_TIMER      # read timer
        syscall
        blt $v0,20000,while2        # while timer < 20000, while2

        j end
