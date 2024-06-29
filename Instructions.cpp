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

void Instructions::iType(unsigned int instWord)
{

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