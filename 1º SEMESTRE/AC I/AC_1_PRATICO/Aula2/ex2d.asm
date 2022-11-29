	.data
	.text
	.globl main
main:   li $t0, 7         # gray = 2

	or $t1, $0, $t0   # num = gray
	srl $t3, $t1, 4   # temp = (num >> 4)
	xor $t1, $t1, $t3 # num = num ^ temp
	
	srl $t3, $t1, 2   # temp = (num >> 2)
	xor $t1, $t1, $t3 # num = num ^ temp
	
    	srl $t3, $t1, 1   # temp = (num >> 1)
	xor $t1, $t1, $t3 # num = num ^ temp
	
	or $t2, $0, $t1   # bin = num
	jr $ra