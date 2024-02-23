        
        .data
        .equ inkey,1
        .equ putChar,3
        .text
        .globl main

main:

do:     li $v0, inkey
        syscall

if:     beqz $v0, else
        move $a0, $v0
        li $v0, putChar
        syscall

else:   li $a0, '.' 
        li $v0, putChar
        syscall

while:  bne $a0, '\n', do
        li $v0, 0
        jr $ra
