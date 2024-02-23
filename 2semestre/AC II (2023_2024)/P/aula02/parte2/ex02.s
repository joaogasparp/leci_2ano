        .data
str10:  .asciiz "cnt10: "
str5:   .asciiz "cnt5: "
str1:   .asciiz "cnt1: "
str0:   .asciiz "\t"
        .text
        .globl main

main:   li $t7,0                    # cnt1 = 0;
        li $t8,0                    # cnt5 = 0;
        li $t9,0                    # cnt10 = 0;
        li $t5,100
    
while:  addiu $sp,$sp,-4
        sw $ra,0($sp)
        move $a0,$t5                # delay(100);
        jal delay
        lw $ra,0($sp)
        addiu $sp,$sp,4
        
        addiu $t9,$t9,1             # cnt10++;

        remu $t6,$t9,2              # se cnt10 for multiplo de 2
        bne $t6,0,endif             # cnt5++;
        addiu $t8,$t8,1
        
endif:  remu $t6,$t9,10             # se cnt10 for multiplo de 10
        bne $t6,0,endif2            # cnt1++;
        addiu $t7,$t7,1 
        
endif2: li $v0,6
        move $a0,$t7
        syscall                     # printInt(cnt1, 10 | 4 << 16);
        
        li $v0,8
        la $a0,str0
        syscall                     # printString("  ");

        li $v0,6
        move $a0,$t8
        syscall                     # printInt(cnt5, 10 | 4 << 16);

        li $v0,8
        la $a0,str0
        syscall                     # printString("  ");
        
        li $v0,6
        move $a0,$t9
        li $a1,0X0005000A
        syscall                     # printInt(cnt10, 10 | 4 << 16);

        li $v0,3
        la $a0,'\r'
        syscall                     # printStr("\r");

        j while                     # while(1)
        li $v0,0

        jr $ra

delay:  li $v0,12
        syscall
        mul $a0,$a0,20000

while2: li $v0,11
        syscall
        ble $v0,$a0,while2
        
        jr $ra
