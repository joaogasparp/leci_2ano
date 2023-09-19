# typedef struct
# {				Align	Size		Offset
#	int acc;		4	4		0
#	unsigned char nm;	1	1		0+4
#	double grade;		8	8		4+1=5->8
#	char quest[14];		1	14		8+8=16->16
#	int cp;			4	4		16+14=30->32
# } t_kvd;			8	32+4=36->40

# Mapa de registo
# nv	: $a0
# pt	: $a1
# i	: $t0
# j	: $t1
# sum	: $f0

	.data
f1:	.double 0.0
	.text
	.globl func4
	
func4:	l.d $f4,f1
	li $t0,0
	
for:	bge $t0,$a0,endf
	li $t1,0

do:	addi $t2,$a1,16		# // $t2 = pt->quest[0]
	addu $t2,$t2,$t1	# // $t2 = pt->quest[0]+j
	lb $t2,0($t2)		# // $t2 = pt->quest[j]
	mtc1 $t2,$f6
	cvt.d.w $f6,$f6		# // (double) pt->quest[j]
	add.d $f4,$f4,$f6	# sum += (double) pt->quest[j]
	addi $t1,$t1,1		# // j++
	lb $t2,4($a1)		# // $t2 = pt->nm
	blt $t1,$t2,do
	
	l.d $f6,8($a1)		# // $f6 = pt->grade
	div.d $f6,$f4,$f6	# // $f6 = sum / pt->grade
	cvt.w.d $f6,$f6		# // (int) sum / pt->grade
	mfc1 $t2,$f6
	sw $t2,0($a1)		# pt->acc = (int) sum / pt->grade
	
	addi $t0,$t0,1		# // i++
	addi $a1,$a1,40		# // $a1 += 40
	
	j for

endf:	lw $t0,32($a1)		# // pt->cq
	mtc1 $t0,$f0
	cvt.d.w $f0,$f0
	l.d $f6,8($a1)
	mul.d $f0,$f6,$f0
	
	jr $ra