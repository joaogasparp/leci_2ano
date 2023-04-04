        .equ READ_CORE_TIMER,11
        .equ RESET_CORE_TIMER,12
        .equ PRINT_STR,8
        .equ PRINT_INT,7
str10:  .asciiz "cnt10: "
str5:   .asciiz "cnt5: "
str1:   .asciiz "cnt1: "
n:      .asciiz "\n"
        .data
        .text
        .globl main

main:   li $t0,0
        li $t1,0
        li $t2,0
        li $t7,1000
        li $t8,200
        li $t9,100

while:  addiu $t0,$t0,1
        li $v0,PRINT_STR
	    la $a0,str1
	    syscall
        
        move $a0,$t7
        jal delay

        li $v0,PRINT_INT
        move $a0,$t0
        syscall

        li $v0,PRINT_STR
        la $a0,n
        syscall

        j while

        li $v0,0
        jr $ra

#

delay:  li $v0,RESET_CORE_TIMER     # resetCoreTimer();
        syscall                     # resetCoreTimer();
        mul $a0,$a0,20000           # ms * 20000

while2: li $v0,READ_CORE_TIMER      # readCoreTimer();
        syscall                     # readCoreTimer();
        ble $v0,$a0,while2          # while(readCoreTimer() < 20000 * ms);
        jr $ra