//
// Created by Kareem Elnaghy on 6/29/24.
//
#include <iostream>
#include "Instructions.h"
using namespace std;

void Instructions::rType(unsigned int instWord)
{

}

void Instructions::iType(unsigned int instWord)
{
    unsigned int rd, rs1, func3, func7, opcode,shamt, I_immU;
    signed int I_imm;
    unsigned int instPC = pc - 4;

    opcode = instWord & 0x0000007F;
    rd = (instWord >> 7) & 0x0000001F;
    func3 = (instWord >> 12) & 0x00000007;
    rs1 = (instWord >> 15) & 0x0000001F;
    func7 = (instWord >> 25) & 0x0000007F;
    shamt= (instWord >> 20) & 0x0000001F;
    I_imm = ((instWord >> 20) & 0x7FF);
    I_immU = ((instWord >> 20) & 0x7FF);



    switch (funct3) {
        case 0:
            cout << "\tADDI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << I_imm << "\n";
            break;
        case 2:
            cout << "\tSLTI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << I_imm << "\n";
            break;
        case 3:
            cout << "\tSLTIU\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << I_immU << "\n";
            break;
        case 4:
            cout << "\tXORI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << I_imm << "\n";
            break;
        case 6:
            cout << "\tORI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << I_imm << "\n";
            break;
        case 7:
            cout << "\tANDI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << I_imm << "\n";
            break;
        case 1:
            cout << "\tSLLI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << shamt << "\n";
            break;
        case 5:
            if(func7==0)
                cout << "\tSRLI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << shamt << "\n";
            else
            cout << "\tSRAI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << shamt << "\n";
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

void Instructions::uType(unsigned int instWord)
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

void Instructions::Load(unsigned int instWord)
{
    unsigned int rd, rs1, func3, opcode;
    signed int I_imm;
    unsigned int instPC = pc - 4;

    opcode = instWord & 0x0000007F;
    rd = (instWord >> 7) & 0x0000001F;
    func3 = (instWord >> 12) & 0x00000007;
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