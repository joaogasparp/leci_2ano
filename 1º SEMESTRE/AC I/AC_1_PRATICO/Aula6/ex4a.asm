# $a0: $t0
	
	.data
	.eqv print_string,4
	.eqv print_int10,1
str1:	.asciiz "Nr. de paramentros: "
str2:	.asciiz "\nP"
str3:	.asciiz ": "
	.text
	.globl main
	
main:	addi $t1,$a0,0	# $t1 = argc
	li $v0,print_string
	la $a0,str1
	syscall
	li $v0,print_int10
	addi $a0,$t1,0
	syscall
	li $t0,0
	addiu $t2,$a1,0	# $t2 = &(argv[0])

for:	bge $t0,$t1,endf
	li $v0,print_string
	la $a0,str2
	syscall	# printString(str2)
	li $v0,print_int10
	addi $a0,$t0,0
	syscall	# printInt(i)
	li $v0,print_string
	la $a0,str3
	syscall	# printString(str3)
	sll $t3,$t0,2	# t3 = i * 4
	addu $t3,$t3,$t2	# $t3 = &(argv[i])
	lw $a0,0($t3)	# a0 = argv[i]
	li $v0,print_string
	syscall	# printString(argv[0])
	addi $t0,$t0,1	# i = i + 1
	j for
	
endf:	jr $ra