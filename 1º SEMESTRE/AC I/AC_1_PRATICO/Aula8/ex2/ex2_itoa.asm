# Mapa de registos
# n: $a0 -> $s0
# b: $a1 -> $s1
# s: $a2 -> $s2
# p: $s3
# digit: $t0
# Sub-rotina intermédia

	.data
	.text
	.globl itoa
	
itoa: 	addiu $sp,$sp,-20	# reserva espaço na stack
	sw $ra,0($sp)		# guarda registos $sx e $ra
	sw $s0,4($sp)
	sw $s1,8($sp)
	sw $s2,12($sp)
	sw $s3,16($sp)
	move $s0,$a0		# copia n, b e s para registos | $s0 = n
	move $s1,$a1		# $s1 = b;
	move $s2,$a2		# $s2 = s;
	move $s3,$s2		# *p = s;

do:	rem $t0, $s0, $s1	# do { digit = n % b;
	div $s0,$s0,$s1		# n = n / b;
	
	move $a0,$t0
	jal toascii		# chamar função toascii(digit);
	
	sb $v0,0($s3)		# toascii(digit) = *p;
	addiu $s3,$s3,1		# p++;
	
	bgtz $s0,do		# } while(n > 0);
	
	li $t0,'\0'
	sb $t0,0($s3)		# *p = '\0';

	move $a0,$s2
	jal strrev		# strrev(s);
	move $v0,$s2		# return s;
	
	lw $ra,0($sp)		# repõe registos $sx e $ra
	lw $s0,4($sp)
	lw $s1,8($sp)
	lw $s2,12($sp)
	lw $s3,16($sp)
	addiu $sp,$sp,-20	# liberta espaço na stack
	
	jr $ra