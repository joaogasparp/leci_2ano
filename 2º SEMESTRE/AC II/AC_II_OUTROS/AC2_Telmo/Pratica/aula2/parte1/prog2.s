    .equ resetCoreTimer, 12
    .equ readCoreTimer, 11
    .equ putChar, 3
    .equ printInt, 6

    .data

    .text
    .globl main
main:

    addiu $sp , $sp, -8
    sw $ra, 0($sp)
    sw $s0, 4($sp)

    li $s0, 0	                #counter = 0

while:

    li $a0, 100                 #1hz  = 100ms * 200000
    jal delay

    addi $s0, $s0, 1		    #counter++
	move $a0, $s0
	
	li $a1, 4
	sll $a1, $a1, 16
	ori $a1, $a1, 10		    #10 | 4 << 16
	
	li $v0, printInt
	syscall			            #printInt(counter++, 10 | 4 << 16)
	
	li $a0, '\r'
	li $v0, putChar
	syscall			            #putChar('\r')

    j while

    lw $ra, 0($sp)
    lw $s0, 4($sp)
    addiu $sp , $sp, 8    
    
delay:
    li $v0, resetCoreTimer
    syscall

read:
    li $v0, readCoreTimer  
    syscall                     #readCoreTimer()

    mul $t0, $a0, 20000         #k * ms  
    blt $v0, $t0, read          #while(readCoreTimer() < K * ms)

    jr $ra
