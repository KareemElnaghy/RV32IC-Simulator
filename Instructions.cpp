//
// Created by Kareem Elnaghy on 6/29/24.
//
#include <iostream>
#include "Register.h"
#include "Instructions.h"
using namespace std;

void Instructions::rType(unsigned int instWord)
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
                cout << "\tSUB\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << registers[rs2].getABI() << "\n";
                registers[rd].setData(registers[rs1].getData() - registers[rs2].getData());
            } else {
                cout << "\tADD\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << registers[rs2].getABI() << "\n";
                registers[rd].setDataU(registers[rs1].getDataU() + registers[rs2].getDataU());
            }
            break;

        case 1:
            cout << "\tSLL\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << registers[rs2].getABI() << "\n";
            registers[rd].setData(registers[rs1].getData() << registers[rs2].getData());
            break;
        case 2:
            cout << "\tSLT\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << registers[rs2].getABI() << "\n";

        case 3:
            cout << "\tSLTU\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << registers[rs2].getABI() << "\n";

        case 4:
            cout << "\tXOR\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << registers[rs2].getABI() << "\n";
            registers[rd].setData(registers[rs1].getData() ^ registers[rs2].getData());
            break;

        case 5:
            if(funct7 == 32)
            {
                cout << "\tSRA\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << registers[rs2].getABI() << "\n";
                int temp = registers[rs1].getData();
                registers[rd].setData(temp>>registers[rs2].getDataU());
            }
            else
            {
                cout << "\tSRL\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << registers[rs2].getABI() << "\n";
                registers[rd].setData(registers[rs1].getData() >> registers[rs2].getData());
                break;
            }

        case 6:
            cout << "\tOR\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << registers[rs2].getABI() << "\n";
            registers[rd].setData(registers[rs1].getData() | registers[rs2].getData());
            break;
        case 7:
            cout << "\tAND\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << registers[rs2].getABI() << "\n";
            registers[rd].setData(registers[rs1].getData() & registers[rs2].getData());
            break;

        default:
            cout << "\tUnknown Instruction \n";
    }
}

void Instructions::iType(unsigned int instWord, Register registers[32], unsigned int pc)
{
    unsigned int rd, rs1, funct3, funct7, opcode,shamt, I_immU;
    signed int I_imm;
    unsigned int instPC = pc - 4;
    signed int temp;
    unsigned int tempU;
    opcode = instWord & 0x0000007F;
    rd = (instWord >> 7) & 0x0000001F;
    funct3 = (instWord >> 12) & 0x00000007;
    rs1 = (instWord >> 15) & 0x0000001F;
    funct7 = (instWord >> 25) & 0x0000007F;
    shamt= (instWord >> 20) & 0x0000001F;
    I_imm = ((instWord >> 20) & 0x7FF);
    I_immU = ((instWord >> 20) & 0x7FF);



    switch (funct3) {
        case 0:
            cout << "\tADDI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << I_imm << "\n";
            temp= registers[rs1].getData() + I_imm;
            registers[rd].setData(temp);
            break;
        case 2:
            cout << "\tSLTI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << I_imm << "\n";
             temp= (registers[rs1].getData() < I_imm)? 1 : 0;
            registers[rd].setData(temp);
            break;
        case 3:
            cout << "\tSLTIU\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << I_immU << "\n";
        temp= (registers[rs1].getData() < I_immU)? 1 : 0;
        registers[rd].setData(temp);
            break;
        case 4:
            cout << "\tXORI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << I_imm << "\n";
            temp = registers[rs1].getData() ^ I_imm;
            registers[rd].setData(temp);
            break;
        case 6:
            cout << "\tORI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << I_imm << "\n";
            temp = registers[rs1].getData() | I_imm;
            registers[rd].setData(temp);
            break;
        case 7:
            cout << "\tANDI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << I_imm << "\n";
            temp = registers[rs1].getData() & I_imm;
            registers[rd].setData(temp);
            break;
        case 1:
            cout << "\tSLLI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << shamt << "\n";
            temp = registers[rs1].getData() << shamt;
            registers[rd].setData(temp);
            break;
        case 5:
            if(funct7==0) {
                cout << "\tSRLI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << shamt << "\n";
                tempU = registers[rs1].getData() >> shamt;
                registers[rd].setData(tempU);
            }
            else {
                cout << "\tSRAI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << shamt << "\n";
                temp = registers[rs1].getData() >> shamt;
                registers[rd].setData(temp);
            }
            break;

        default:
            cout << "\tUnknown I Instruction \n";
    }
}

void Instructions::sType(unsigned int instWord)
{

}
void Instructions::bType(unsigned int instWord)
{

}

void Instructions::uType(unsigned int instWord, Register registers[32], unsigned int pc)
{
    unsigned int rd, opcode;
    signed int I_imm;
    unsigned int instPC = pc - 4;

    opcode = instWord & 0x0000007F;
    rd = (instWord >> 7) & 0x0000001F;
    I_imm = ((instWord >> 12) & 0xFFFFF);

    if(opcode == 0x37)
        cout << "\tLUI\t" << registers[rd].getABI() <<", " << I_imm;
    else if(opcode == 0x17)
        cout << "\tAUIPC\t" << registers[rd].getABI() <<", " << I_imm;
    else
        cout << "\tUnknown U Instruction \n";


}

void Instructions::jType(unsigned int instWord)
{

}

void Instructions::Load(unsigned int instWord, Register registers[32], unsigned int pc)
{
    unsigned int rd, rs1, funct3, opcode;
    signed int I_imm;
    unsigned int instPC = pc - 4;

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