	.data
	.text
	.globl main
main:   ori $v0,$0,5   #a system call read_int() é
                       #identificada com o número 5;
	syscall        #a system call read_int() é chamada;
	or $t0,$0,$v0  #o valor lido do teclado é armazenado
	               #no registo $t0;
	ori $t2,$0,8   
	add $t1,$t0,$t0
	sub $t1,$t1,$t2
	or $a0,$0,$t1  #o registo $t1 é armazenado
	               #no registo $a0;
	ori $v0,$0,1   #a system call print_int10() é
                       # identificada com o número 1;
	syscall        #a system call print_int10() é chamada;
	ori $v0,$0,34
	syscall
	ori $v0,$0,36
	syscall
	jr $ra
