.text
.globl main

main:
li t0,100
andi t1,t0,1
beq, t1,zero, even
add t1,t0,t1

exit:
mv a0, t1   
li a7, 1   
ecall
li a7, 10   
ecall

even:
srli t0,t0,1
li t2,5
loop: bgeu t1,t2,next
addi t1,t1,1
j loop

next:
add t1,t0,t1
slli t1,t1,1
li t3,8
sub t1,t1,t3
j exit




