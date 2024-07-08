.text
.globl main


main:
   
    li a0, 100   
    li a1, 48  
    jal ra, gcd 
   mv a0, s0   
    li a7, 1   
    ecall
     li a7, 10   
    ecall

gcd:
    
    addi sp, sp, -12
    sw ra, 0(sp)  
    sw a0, 4(sp)  
    sw a1, 8(sp)  
    

   
loop:
    beq a1, zero, base_Case  
    blt a0, a1, swap        
    sub a0, a0, a1          
    j loop              

swap:
xor a0,a0,a1
xor a1,a0,a1
xor a0,a0,a1
    
    j loop

base_Case:
    mv s0, a0       
    lw ra, 0(sp)    
    lw a0, 4(sp)    
    lw a1, 8(sp)    
   
    addi sp, sp, 12 
    ret