        .data
        .equ readInt10, 5
        .equ printInt10, 7
        .equ printStr, 8
        .equ printInt, 6
str1:   .asciiz "\nIntroduza um numero (sinal e modulo): "
str2:   .asciiz "\nValor lido, em base 2: "
str3:   .asciiz "\nValor lido, em base 16: "
str4:   .asciiz "\nValor lido, em base 10 (unsigned): "
str5:   .asciiz "\nValor lido, em base 10 (signed): "
str6:	.asciiz "\nValor em base 10 (unsigned), formatado: "
str7:	.asciiz "\nValor em base 10 (unsigned):"
        .text
        .globl main

main:         

while:  bne $0, $0, endw
        la $a0, str1
        li $v0, printStr
        syscall
        li $v0, readInt10
        syscall
        move $t1, $v0
        
        la $a0, str5
        li $v0, printStr
        syscall
        move $a0, $t1
        li $v0, printInt10
        syscall

        la $a0, str2
        li $v0, printStr
        syscall
        move $a0, $t1
        li $a1, 2
        li $v0, printInt
        syscall

        la $a0, str3
        li $v0, printStr
        syscall
        move $a0, $t1
        li $a1, 16
        li $v0, printInt
        syscall
        
        la $a0, str7
        li $v0, printStr
        syscall
        move $a0, $t1
        li $a1, 10
        li $v0, printInt
        syscall

        la $a0, str6
        li $v0, printStr
        syscall
        move $a0, $t1
        li $a1, 5
        sll $a1, $a1, 16
        ori $a1, $a1, 10
        li $v0, printInt
        syscall
        j while

endw:   li $v0, 0
        jr $ra