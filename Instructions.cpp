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
    unsigned int rd, rs1, rs2, func3, func7, opcode,shamt, I_immU;
    unsigned int I_imm;
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
            std::cout << "\tUnknown R Instruction \n";
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

}

void Instructions::jType(unsigned int instWord)
{

}

void Instructions::Load(unsigned int instWord)
{

}