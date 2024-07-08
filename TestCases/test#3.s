 .text
.globl main

main:
    # Load immediate values
    li x1, 0x13           
    li x2, 0x1            
    li x3, 0x12345678     
    li x4, 0x87654321    
    
    # R-Type
    add x5, x3, x4        
    sub x6, x1, x2        
    and x9, x3, x4        
    or x10, x1, x2        
    xor x11, x10, x11       
    sll x12, x10, x11      
    srl x13, x12, x2      
    sra x14, x13, x1      

    # B-Type
    beq x3, x4, label1    
    bne x12, x1, label2    
    blt x14, x4, label3  
    bge x9, x10, label4    
    

    li a7, 10
    ecall               

    
label1:
    addi x16, x1, 10      
    j end               
    
label2:
    addi x16, x2, 20      
    j end                
    
label3:
    addi x16, x3, 30     
    j end               
    
label4:
    addi x16, x4, 40    
    
end:
    add a0,x14,x13
    li a7,1
    ecall
    li a7, 10
    ecall               
