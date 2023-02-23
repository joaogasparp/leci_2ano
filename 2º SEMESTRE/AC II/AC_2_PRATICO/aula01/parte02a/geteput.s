        .data
        .equ getChar, 2
        .equ putChar, 3
        .text
        .globl main

main:   

do:     li $v0,getChar
        syscall
        move $a0, $v0
        li $v0,putChar
        syscall

while:  bne $a0,'\n',do
        jr $ra