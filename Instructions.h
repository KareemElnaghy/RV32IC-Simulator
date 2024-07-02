//
// Created by Kareem Elnaghy on 6/29/24.
//

#include <iostream>
using namespace std;
//Global Variables
const int MEMORY_SIZE = 64*1024;
const int NUM_REGISTERS = 32;

unsigned int printPc;
unsigned int exPc;
unsigned char memory[MEMORY_SIZE];
Register registers[NUM_REGISTERS];


void rType(unsigned int instWord, bool s)
{
    unsigned int rd, rs1, rs2, funct3, funct7;

    rd = (instWord >> 7) & 0x0000001F;
    funct3 = (instWord >> 12) & 0x00000007;
    rs1 = (instWord >> 15) & 0x0000001F;
    rs2 = (instWord >> 20) & 0x0000001F;
    funct7 = (instWord >> 25)  & 0x0000007F;

    switch (funct3)
    {
        case 0:
            if (funct7 == 32) {
                if(s)
                cout << "\tSUB\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << registers[rs2].getABI() << "\n";
                else
                registers[rd].setData(registers[rs1].getData() - registers[rs2].getData());
            } else {
                if(s)
                cout << "\tADD\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << registers[rs2].getABI() << "\n";
                else
                    registers[rd].setDataU(registers[rs1].getDataU() + registers[rs2].getDataU());
            }
            break;

        case 1:
            if(s)
            cout << "\tSLL\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << registers[rs2].getABI() << "\n";
            else
                registers[rd].setData(registers[rs1].getData() << registers[rs2].getData());
            break;
        case 2:
            if(s)
            cout << "\tSLT\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << registers[rs2].getABI() << "\n";


        case 3:
            if(s)
            cout << "\tSLTU\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << registers[rs2].getABI() << "\n";

        case 4:
            if(s)
            cout << "\tXOR\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << registers[rs2].getABI() << "\n";
            else
                registers[rd].setData(registers[rs1].getData() ^ registers[rs2].getData());
            break;

        case 5:
            if(funct7 == 32)
            {
                if(s)
                cout << "\tSRA\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << registers[rs2].getABI() << "\n";
               else {
                    int temp = registers[rs1].getData();
                    registers[rd].setData(temp >> registers[rs2].getDataU());
                }
            }
            else
            {
                if(s)
                cout << "\tSRL\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << registers[rs2].getABI() << "\n";
               else
                   registers[rd].setData(registers[rs1].getData() >> registers[rs2].getData());
                break;
            }

        case 6:
            if(s)
            cout << "\tOR\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << registers[rs2].getABI() << "\n";
            else
                registers[rd].setData(registers[rs1].getData() | registers[rs2].getData());
            break;
        case 7:
           if(s)
            cout << "\tAND\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << registers[rs2].getABI() << "\n";
            else
                registers[rd].setData(registers[rs1].getData() & registers[rs2].getData());
            break;

        default:
            cout << "\tUnknown Instruction \n";
    }
}

int bType(unsigned int instWord, bool s) {


    unsigned int rs1, rs2, funct3, opcode;
    signed int b_imm;
    unsigned int instPC1 = printPc - 4;
    unsigned int instPC2 = exPc - 4;
    int r;


    opcode = instWord & 0x0000007F;
    rs1 = (instWord >> 15) & 0x0000001F;
    rs2 = (instWord >> 20) & 0x0000001F;
    funct3 = (instWord >> 12) & 0x00000007;


    b_imm = ((instWord >> 31) & 0x1) << 12;
    b_imm |= ((instWord >> 7) & 0x1) << 11;
    b_imm |= ((instWord >> 25) & 0x3F) << 5;
    b_imm |= ((instWord >> 8) & 0xF) << 1;
    b_imm |= 0;

    if (b_imm & 0x1000) {
        b_imm |= 0xFFFFE000;
    }

    switch (funct3) {
        case 0:
            if(s)
            cout << "\tBEQ\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex
                 << b_imm + instPC1 <<"\n";
            else {
                if(registers[rs1].getData() == registers[rs2].getData())
                r = b_imm + instPC2;
                else
                    r=exPc - 4;
            }
            break;
        case 1:
                if(s)
            cout << "\tBNE\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex
                 << b_imm + instPC1 <<"\n";
                else {
                    if(registers[rs1].getData() != registers[rs2].getData())
                        r = b_imm + instPC2;
                    else
                        r=exPc - 4;
                }
            break;
        case 2:
if(s)
            cout << "\tBLT\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex
                 << b_imm + instPC1 <<"\n";
else {
    if(registers[rs1].getData() < registers[rs2].getData())
        r = b_imm + instPC2;
    else
        r=exPc - 4;
}
            break;
        case 3:
if(s)
            cout << "\tBGE\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex
                 << b_imm + instPC1 <<"\n";
else {
    if(registers[rs1].getData()>= registers[rs2].getData())
        r = b_imm + instPC2;
    else
        r=exPc - 4;
}
            break;
        case 4:
if(s)
            cout << "\tBLTU\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex
                 << b_imm + instPC1 <<"\n";
else {
    if(registers[rs1].getData() < registers[rs2].getData())
        r = b_imm + instPC2;
    else
        r=exPc - 4;
}
            break;
        case 5:
if(s)
            cout << "\tBGEU\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex
                 << b_imm + instPC1 <<"\n";
else {
    if(registers[rs1].getData() >= registers[rs2].getData())
        r = b_imm + instPC2;
    else
        r=exPc - 4;
}
            break;
        default:
            cout << "\tUnknown B Instruction \n";

    }
    return r;

}

int jType(unsigned int instWord, bool s)
{
    unsigned int rd, opcode;
    signed int j_imm;
    unsigned int instPC1 = printPc - 4;
    unsigned int instPC2 = exPc - 4;
    int r;

    opcode = instWord & 0x0000007F;
    rd = (instWord >> 7) & 0x0000001F;


    j_imm = ((instWord >> 31) & 0x1) << 20;
    j_imm |= ((instWord >> 12) & 0xFF) << 12;
    j_imm |= ((instWord >> 20) & 0x1) << 11;
    j_imm |= ((instWord >> 21) & 0x3FF) << 1;
    j_imm |= 0;


    if (j_imm & 0x100000) {
        j_imm |= 0xFFE00000;
    }
    if(s)
    cout << "\tJAL\t" << registers[rd].getABI() << ", " << "0x" << hex << j_imm + instPC1<<endl;
    else
        r=j_imm + instPC2;

    return r;
}


void iType(unsigned int instWord, bool s)
{
    unsigned int rd, rs1, funct3, funct7, opcode,shamt, I_immU;
    int16_t I_imm, I_immPrint;
   // unsigned int instPC = pc - 4;
    signed int temp;
    unsigned int tempU;
    opcode = instWord & 0x0000007F;
    rd = (instWord >> 7) & 0x0000001F;
    funct3 = (instWord >> 12) & 0x00000007;
    rs1 = (instWord >> 15) & 0x0000001F;
    funct7 = (instWord >> 25) & 0x0000007F;
    shamt= (instWord >> 20) & 0x0000001F;
    I_imm = ((instWord >> 20) & 0xFFF);
    I_immPrint = ((instWord >> 20) & 0xFFF);
    I_immU = ((instWord >> 20) & 0x7FF);


    int signedBit = (I_imm >> 11) & 1;
    if(signedBit == 1) {
        I_imm|= 0xF000;
    }



    switch (funct3) {
        case 0:
            if(s)
            cout << "\tADDI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << I_imm << "\n";
           else {
                temp = registers[rs1].getData() + I_imm;
                registers[rd].setData(temp);
            }
            break;
        case 2:
            if(s)
            cout << "\tSLTI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << I_imm << "\n";
           else
            {temp= (registers[rs1].getData() < I_imm)? 1 : 0;
            registers[rd].setData(temp);}
            break;
        case 3:
            if(s)
            cout << "\tSLTIU\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << I_immU << "\n";
           else{ temp= (registers[rs1].getData() < I_immU)? 1 : 0;
            registers[rd].setData(temp);}
            break;
        case 4:
            if(s)
            cout << "\tXORI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << I_imm << "\n";
           else{ temp = registers[rs1].getData() ^ I_imm;
            registers[rd].setData(temp);}
            break;
        case 6:
            if(s)
            cout << "\tORI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << I_imm << "\n";

           else{ temp = registers[rs1].getData() | I_imm;
            registers[rd].setData(temp);}
            break;
        case 7:
           if(s) cout << "\tANDI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << I_imm << "\n";
            else
           {temp = registers[rs1].getData() & I_imm;
            registers[rd].setData(temp);}
            break;
        case 1:
            if(s)
            cout << "\tSLLI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << shamt << "\n";
            else{temp = registers[rs1].getData() << shamt;
            registers[rd].setData(temp);}
            break;
        case 5:
            if(funct7==0) {
               if(s)
                   cout << "\tSRLI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << shamt << "\n";
                else{tempU = registers[rs1].getData() >> shamt;
                registers[rd].setData(tempU);}
            }
            else {
               if(s)
                cout << "\tSRAI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << shamt << "\n";
              else
               {temp = registers[rs1].getData() >> shamt;
                registers[rd].setData(temp);}
            }
            break;

        default:
            cout << "\tUnknown I Instruction \n";
    }
}

void sType(unsigned int instWord,bool s)
{

}

/*
void uType(unsigned int instWord, bool s)
{
    unsigned int rd, opcode;
    unsigned int I_imm;
    unsigned int instPC = pc - 4;
    unsigned int tempU;

    opcode = instWord & 0x0000007F;
    rd = (instWord >> 7) & 0x0000001F;
    I_imm = ((instWord >> 12) & 0xFFFFF);

    if(opcode == 0x37) {
       if(s) cout << "\tLUI\t" << registers[rd].getABI() <<", " << I_imm;
        else
       {tempU = I_imm << 12;
        registers[rd].setDataU(tempU);}
    }

    else if(opcode == 0x17) {
        if(s)
            cout << "\tAUIPC\t" << registers[rd].getABI() <<", " << I_imm;
       else{ tempU = pc + (I_imm << 12);
        registers[rd].setDataU(tempU);}
    }
    else
        cout << "\tUnknown U Instruction \n";


}

*/
void Load(unsigned int instWord, bool s)
{
    unsigned int rd, rs1, funct3, opcode;
    signed int I_imm;
   // unsigned int instPC = pc - 4;

    opcode = instWord & 0x0000007F;
    rd = (instWord >> 7) & 0x0000001F;
    funct3 = (instWord >> 12) & 0x00000007;
    rs1 = (instWord >> 15) & 0x0000001F;
    I_imm = ((instWord >> 20) & 0x7FF);

    switch (funct3) {
        case 0:
            cout << "\tLB\t" << registers[rd].getABI() <<", " << I_imm<< "(" << registers[rs1].getABI() << ")"<<"\n";
            break;
        case 1:
            cout << "\tLH\t" << registers[rd].getABI() <<", " << I_imm<< "(" << registers[rs1].getABI() << ")"<<"\n";
            break;
        case 2:
            cout << "\tLW\t" << registers[rd].getABI() <<", " << I_imm<< "(" << registers[rs1].getABI() << ")"<<"\n";
            break;
        case 3:
            cout << "\tLBU\t" << registers[rd].getABI() <<", " << I_imm<< "(" << registers[rs1].getABI() << ")"<<"\n";
            break;
        case 4:
            cout << "\tLHU\t" << registers[rd].getABI() <<", " << I_imm<< "(" << registers[rs1].getABI() << ")"<<"\n";
            break;
        default:
            cout << "\tUnknown Load Instruction \n";

    }
}