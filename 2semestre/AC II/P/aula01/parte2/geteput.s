    
        .data
        .equ getChar, 2
        .equ putChar, 3
        .text
        .globl main

main:

do:     li $v0, getChar     # syscall for reading a character
        syscall         # read a character
        move $a0, $v0    # move the character to $a0
        add $a0, $a0, 1   # add 1 to the character
        li $v0, putChar    # syscall for printing a character
        syscall        # print the character

while:  bne $a0, '\n', do   # if the character is not a newline, repeat
        li $v0, 0     # syscall for exiting
        jr $ra      # return to the operating system