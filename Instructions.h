//
// Created by Kareem Elnaghy on 6/29/24.

#include <iostream>
#include <bitset>
#include <cstdint>
#include <vector>
using namespace std;
//Global Variables
const int MEMORY_SIZE = 128*1024;
const int NUM_REGISTERS = 32;

signed int Pc;
int32_t dataAddr = 0x00010000;
int32_t textAddr =0x0;
unsigned char memory[MEMORY_SIZE];
Register registers[NUM_REGISTERS];
vector<string> output;
bool exitProgram = false;
bool s;

void emitError(const string& msg)
{
    cout<<msg;
    exit(0);
}

void rType(unsigned int rd, unsigned int rs1, unsigned int rs2, unsigned int funct3, unsigned int funct7) {
    switch (funct3) {
        case 0:
            if (funct7 == 32) {
                // SUB
                registers[rd].setData(registers[rs1].getData() - registers[rs2].getData());
            } else {
                // ADD
                registers[rd].setDataU(registers[rs1].getDataU() + registers[rs2].getDataU());
            }
            break;

        case 1:
            // SLL
            registers[rd].setData(registers[rs1].getData() << registers[rs2].getData());
            break;

        case 2:
            // SLT
            registers[rd].setData((registers[rs1].getData() < registers[rs2].getData())?1:0);

        case 3:
            // SLTU
            registers[rd].setDataU((registers[rs1].getDataU() < registers[rs2].getDataU())?1:0);

        case 4:
            // XOR
            registers[rd].setData(registers[rs1].getData() ^ registers[rs2].getData());
            break;

        case 5:
            if (funct7 == 32) {
                // SRA
                int temp = registers[rs1].getData();
                registers[rd].setData(temp >> registers[rs2].getDataU());
            } else {
                // SRL
                registers[rd].setData(registers[rs1].getData() >> registers[rs2].getData());
            }
            break;

        case 6:
            // OR
            registers[rd].setData(registers[rs1].getData() | registers[rs2].getData());
            break;

        case 7:
            // AND
            registers[rd].setData(registers[rs1].getData() & registers[rs2].getData());
            break;

        default:
            // Unknown R Instruction
            break;
    }
}

    int bType(unsigned int rs1, unsigned int rs2, unsigned int funct3,int16_t  b_imm, int instPC1) {

        int r;

        int signedBit = (b_imm >> 12) & 1;
        if (signedBit == 1) {
            b_imm |= 0xE000;
        }

        switch (funct3) {
            case 0: {
                if (registers[rs1].getData() == registers[rs2].getData())
                    r = b_imm + instPC1;
                else
                    r = Pc;
                break;
            }

            case 1: {
                if (registers[rs1].getData() != registers[rs2].getData())
                    r = b_imm + instPC1;
                else
                    r = Pc;
                break;
            }

            case 4: {
                if (registers[rs1].getData() < registers[rs2].getData())
                    r = b_imm + instPC1;
                else
                    r = Pc;
                break;
            }

            case 5: {
                if (registers[rs1].getData() >= registers[rs2].getData())
                    r = b_imm + instPC1;
                else
                    r = Pc;
                break;
            }

            case 6: {
                if (registers[rs1].getData() < registers[rs2].getData())
                    r = b_imm + instPC1;
                else
                    r = Pc;
                break;
            }

            case 7: {
                if (registers[rs1].getData() >= registers[rs2].getData())
                    r = b_imm + instPC1;
                else
                    r = Pc;
                break;
            }

            default:
                break;
        }

        return r;

    }

int jType(unsigned int rd,int16_t  j_imm, int instPC1)
{
    int r;

    int signedBit = (j_imm >> 12) & 1;
    if(signedBit == 1) {
        j_imm|= 0xE000;
    }

        registers[rd].setData(Pc);
        r = j_imm + instPC1;


    return r;
}


int JalrType(unsigned int rs1, unsigned int rd,int16_t  J_imm, int instPC1)
{
    int r;

    int signedBit = (J_imm >> 11) & 1;
    if(signedBit == 1) {
        J_imm|= 0xF000;
    }

        if(rd==0)
        {
                r = J_imm + registers[rs1].getData() ;

        }
        else if(rd!=0)
        {
                registers[rd].setData(instPC1+4);
                r = J_imm + registers[rs1].getData() ;
        }

    return r;
}


void iType(unsigned int rd, unsigned int rs1, unsigned int funct3,unsigned int funct7, int16_t I_imm,int16_t I_immU,unsigned int shamt, unsigned int opcode)
{
    int temp;
    unsigned int tempU;

    int signedBit = (I_imm >> 11) & 1;
    if(signedBit == 1) {
        I_imm|= 0xF000;
    }

    switch (funct3) {
        case 0:
            if (opcode == 0x13) {
                temp = registers[rs1].getData() + I_imm;
                registers[rd].setData(temp);
            }
            break;

        case 2:
            temp = (registers[rs1].getData() < I_imm) ? 1 : 0;
            registers[rd].setData(temp);
            break;

        case 3:
            temp = (registers[rs1].getData() < I_immU) ? 1 : 0;
            registers[rd].setData(temp);
            break;

        case 4:
            temp = registers[rs1].getData() ^ I_imm;
            registers[rd].setData(temp);
            break;

        case 6:
            temp = registers[rs1].getData() | I_imm;
            registers[rd].setData(temp);
            break;

        case 7:
            temp = registers[rs1].getData() & I_imm;
            registers[rd].setData(temp);
            break;

        case 1:
            temp = registers[rs1].getData() << shamt;
            registers[rd].setData(temp);
            break;

        case 5:
            if (funct7 == 0) {
                tempU = registers[rs1].getData() >> shamt;
                registers[rd].setData(tempU);
            } else {
                temp = registers[rs1].getData() >> shamt;
                registers[rd].setData(temp);
            }
            break;

        default:
            break;
    }

}


void sType(unsigned int rs1, unsigned int rs2, unsigned int funct3, int16_t S_imm)
{
    int32_t address;
    int signedBit = (S_imm >> 11) & 1;
    if(signedBit == 1) {
        S_imm|= 0xF000;
    }

    switch (funct3) {
        case 0:
            address = S_imm + registers[rs1].getDataU();
            memory[address] = registers[rs2].getData() & 0xFF;
            break;
        case 1:
            address = S_imm + registers[rs1].getDataU();
            memory[address] = registers[rs2].getData() & 0xFF;
            memory[address + 1] = (registers[rs2].getData() >> 8) & 0xFF; // Corrected to shift right by 8 bits
            break;
        case 2:
            address = S_imm + registers[rs1].getDataU();
            for (int i = 0; i < 4; i++) {
                memory[address + i] = (registers[rs2].getData() >> (i * 8)) & 0xFF;
            }
            break;
        default:
            // No operation for unknown instruction
            break;
    }

}



void uType(unsigned int rd, unsigned int opcode, int16_t U_imm) {
    unsigned int tempU;
    int temp;

    int signedBit = (U_imm >> 19) & 1;
    if (signedBit == 1) {
        U_imm |= 0xFFF00000;
    }

    if (opcode == 0x37) {
        temp = U_imm << 12;
        registers[rd].setData(temp);
    } else if (opcode == 0x17) {
        tempU = Pc + (U_imm << 12) - 4;
        registers[rd].setDataU(tempU);
    }
        // No operation for unknown instruction

}



void Load(unsigned int rd, unsigned int rs1, unsigned int funct3, int16_t I_imm)
{
   int address;
   int32_t temp;
   int signedTempBit;


    int signedBit = (I_imm >> 11) & 1;
    if(signedBit == 1) {
        I_imm|= 0xF000;
    }

    switch (funct3) {
        case 0:
            address = I_imm + registers[rs1].getData();
            temp = memory[address];
            signedTempBit = (temp >> 7) & 1;
            if (signedTempBit == 1) {
                temp |= 0xFFFFFF00;
            }
            registers[rd].setData(temp);
            break;
        case 1:
            address = I_imm + registers[rs1].getData();
            temp = memory[address] | (memory[address + 1] << 8);
            signedTempBit = (temp >> 15) & 1;
            if (signedTempBit == 1) {
                temp |= 0xFFFF0000;
            }
            registers[rd].setData(temp);
            break;
        case 2:
            address = I_imm + registers[rs1].getData();
            temp = memory[address] | (memory[address + 1] << 8) | (memory[address + 2] << 16) | (memory[address + 3] << 24);
            registers[rd].setData(temp);
            break;
        case 4:
            address = I_imm + registers[rs1].getData();
            temp = memory[address];
            registers[rd].setData(temp);
            break;
        case 5:
            address = I_imm + registers[rs1].getData();
            temp = memory[address] | (memory[address + 1] << 8);
            registers[rd].setData(temp);
            break;
        default:
            // No operation for unknown instruction
            break;
    }

}

bool ecall()
{
        if(registers[17].getDataU() == 10)
        {
            s = true;
            return true;
        }
        else if(registers[17].getDataU() == 1)
        {
            output.push_back(to_string(registers[10].getData()));
            return false;
        }
        else if(registers[17].getDataU() == 4)
        {
            string str = "";
            int i = 0;
            unsigned int address = registers[10].getData();
            if(address > MEMORY_SIZE) emitError("Bad Access: Address does not exist");

            while (memory[address + i] != '\0') {
                str += memory[address + i];
                i++;
            }


            output.push_back(str);

            return false;
        }
        else
        {
            emitError("\tUnknown Call Number \n");
            return false;
        }

}