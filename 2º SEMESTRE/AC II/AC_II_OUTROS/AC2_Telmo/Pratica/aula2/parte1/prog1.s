	.equ resetCoreTimer, 12
    .equ readCoreTimer, 11
    .equ putChar, 3
    .equ printInt, 6

	.data
	.text
	.globl main

main:

	li $t0, 0	                #counter = 0

while:
	li $v0, resetCoreTimer
	syscall
	
read:		
	li $v0, readCoreTimer		
	syscall
	#blt $v0, 200000, read       #while(readCoreTimer() < 200000)    -> 100hz
    #blt $v0, 2000000, read      #while(readCoreTimer() < 2000000)   -> 10hz
    #blt $v0, 4000000, read      #while(readCoreTimer() < 4000000)   -> 5hz
    blt $v0, 20000000, read     #while(readCoreTimer() < 20000000)  -> 1hz

	addi $t0, $t0, 1		    #counter++
	move $a0, $t0
	
	li $a1, 4
	sll $a1, $a1, 16
	ori $a1, $a1, 10		    #10 | 4 << 16
	
	li $v0, printInt
	syscall			            #printInt(counter++, 10 | 4 << 16)
	
	li $a0, '\r'
	li $v0, putChar
	syscall			        #putChar('\r')

    j while
		
	li $v0, 0
	jr $ra
	
	
	
	
	