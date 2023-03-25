    .equ resetCoreTimer, 12
    .equ readCoreTimer, 11
    .equ putChar, 3
    .equ printInt, 6
    .equ inkey, 1

    .data

    .text
    .globl main
main:

    addiu $sp , $sp, -16
    sw $ra, 0($sp)
    sw $s0, 4($sp)	#cnt10
    sw $s1, 8($sp)	#cnt5
    sw $s2, 12($sp)	#cnt1
    
    li $s0, 0
    li $s1, 0
    li $s2, 0
    li $t1, 1000
while:

    li $v0, inkey
    syscall
#delay com teclado
ifd:
    bne $v0, 'a', elseifd
    li $t1, 50              #20hz
    j ifs           
elseifd:1
    bne $v0, 'n', ifs
    li $t1, 100             #10hz

#stop com teclado
ifs:
    bne $v0, 'r', else
    move $t2, $v0
    j endd
else:
    bne $v0, 's', elseand
    move $t2, $v0
    j while
elseand:
    bne $t2, 's', endd
    j while

endd:
    move $a0, $t1	        
    jal delay
#####################################
#counters  
    addi $s0, $s0, 1		#cnt10

freq5:
    rem $t0, $s0, 2
    bne $t0, $0, freq1
    addi $s1, $s1, 1		#cnt5
    
freq1:
    rem $t0, $s0, 10
    bne $t0, $0, endf
    addi $s2, $s2, 1		#cnt1 



endf:

    ori $a1, $0, 5
    sll $a1, 16
    ori $a1, $a1, 10
    
    move $a0, $s0
    li $v0, printInt
    syscall

    li $a0, ' '
    li $v0, putChar
    syscall

    move $a0, $s1
    li $v0, printInt
    syscall
    
    li $a0, ' '
    li $v0, putChar
    syscall

    move $a0, $s2
    li $v0, printInt
    syscall
    
    li $a0, '\r'
    li $v0, putChar
    syscall

    j while
endw:

    lw $ra, 0($sp)
    lw $s0, 4($sp)
    lw $s1, 8($sp)
    lw $s2, 12($sp)
    addiu $sp , $sp, 16
    
    li $v0, 0
    jr $ra


############################################################### 
delay:
    li $v0, resetCoreTimer
    syscall
whiled:
    li $v0, readCoreTimer
    syscall

    li $t0, 20000	# k 
    mul $t0, $a0, $t0	#k *ms
    blt $v0, $t0, whiled
    jr $ra