//
// Created by Kareem Elnaghy on 6/29/24.
//
#include <iostream>
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
                cout << "\tSUB\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
            } else {
                cout << "\tADD\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
            }
            break;

        case 1:
            cout << "\tSLL\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";

        case 2:
            cout << "\tSLT\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";

        case 3:
            cout << "\tSLTU\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";

        case 4:
            cout << "\tXOR\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";

        case 5:
            if(funct7 == 32)
            {
                cout << "\tSRA\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
            }
            else
            {
                cout << "\tSRL\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
            }

        case 6:
            cout << "\tOR\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";

        case 7:
            cout << "\tAND\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";

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