# Mapa de registos
# num:			$t0
# i:			$t1
# &str[0] ou str:	$t2
# &str[i] ou str + i:	$t3
# str[i]:		$t4

	.data
	.eqv SIZE,20
str:	.space 21
	.eqv read_string,8
	.eqv print_int10,1
	.text
	.globl main
	
main:	la $a0,str
	li $a1,SIZE
	li $v0,8
	syscall	
	li $t0,0
	li $t1,0
	
while:	la $t2,str # $t2 = &str[0] ou str			(1)
	addu $t3,$t2,$t1 # $t3 = &str[i] ou str + i		(3)
	lb $t4,0($t3) # $t4 = str[i]				(4)
	
	# basicamente (1) "inicializa" o endereço do endereço 0;
	# o (2) multiplica o i por 4 por causa dos bytes a serem usados;
	# o (3) vai fazer que $t3 = &str[0] + i == &str[i]
	# ou que $t3 = str + i;
	# o (4) dá store à word.

	beq $t4,'\0',endw
	
if:	blt $t4,'0',endif
	bgt $t4,'9',endif
	addi $t0,$t0,1
	
endif:	addi $t1,$t1,1
	j while
	
endw:	or $a0,$0,$t0
	li $v0,1
	syscall
	
	jr $ra