# Mapa de registo
# array_size: $s0
# insert_value: $s1
# insert_pos: $s2

	.data
	.eqv print_string,4
	.eqv read_int,5
	.eqv print_int10,1
str1:	.asciiz "Size of array: "
str2:	.asciiz "array["
str3:	.asciiz "] = "
str4:	.asciiz "Enter the value to be inserted: "
str5:	.asciiz "Enter the position: "
str6:	.asciiz "\nOriginal array: "
str7:	.asciiz "\nModified array: "
array:	.space 200
	.text
	.globl main

main:	addiu $sp,$sp,-16
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	sw $s2,12($sp)

	la $a0,str1
	li $v0,print_string
	syscall
	li $v0,read_int
	syscall
	move $s0,$v0
	li $t0,0

for:	bge $t0,$s0,endfor
	la $a0,str2
	li $v0,print_string
	syscall
	move $a0,$t0
	li $v0,print_int10
	syscall
	la $a0,str3
	li $v0,print_string
	syscall
	la $t1,array		# // $t1 = array
	sll $t3,$t0,2		# // $t3 = i*4
	addu $t2,$t1,$t3	# // $t2 = array+i*4
	li $v0,read_int
	syscall
	sw $v0,0($t2)		# array[i] = read_int()
	addiu $t0,$t0,1
	j for

endfor:	la $a0,str4
	li $v0,print_string
	syscall
	li $v0,read_int
	syscall
	move $s1,$v0
	la $a0,str5
	li $v0,print_string
	syscall
	li $v0,read_int
	syscall
	move $s2,$v0

	la $a0,str6
	li $v0,print_string
	syscall
	la $a0,array
	move $a1,$s0
	jal parray

	la $a0,array
	move $a1,$s1
	move $a2,$s2
	move $a3,$s0
	jal insert

	la $a0,str6
	li $v0,print_string
	syscall
	la $a0,array
	addiu $a1,$s0,1
	jal parray
	li $v0,0
	
	lw $ra,0($sp)
	lw $s0,4($sp)
	lw $s1,8($sp)
	lw $s2,12($sp)
	addiu $sp,$sp,16
	jr $ra