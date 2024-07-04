#include <iostream>
#include <fstream>
#include <iomanip>
#include "Register.h"
#include "Instructions.h"
using namespace std;


void initialiseRegs()
{
    for(int i = 0; i<NUM_REGISTERS; i++)
    {
        registers[i] = Register(i);
    }
    registers[2].setData(128*1024-1);
}

void printRegContent()
{
    cout<<endl;
    for(int i = 0; i<NUM_REGISTERS; i++)
    {
        registers[i].printRegData();
    }
};


void printPrefix(unsigned int instA, unsigned int instW) {
    std::cout << "0x" << std::hex << std::setfill('0') << std::setw(8)
              << instA << "\t0x" << std::setw(8) << instW;
}

void printIntInst(unsigned int rd, unsigned int rs1, unsigned int rs2, unsigned int opcode, unsigned int funct3, unsigned int funct7,int16_t  b_imm,int16_t I_imm,int16_t I_immU, int16_t S_imm, int16_t j_imm,int16_t J_imm, int16_t U_imm, int instPC1, unsigned int shamt )
{
    if(opcode == 0x33 )
    {

        switch (funct3) {
            case 0:
                if (funct7 == 32) {
                    cout << "\tSUB\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", "
                         << registers[rs2].getABI() << "\n";
                } else {
                    cout << "\tADD\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", "
                         << registers[rs2].getABI() << "\n";
                }
                break;

            case 1:
                cout << "\tSLL\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", "
                     << registers[rs2].getABI() << "\n";
                break;

            case 2:
                cout << "\tSLT\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", "
                     << registers[rs2].getABI() << "\n";

            case 3:
                cout << "\tSLTU\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", "
                     << registers[rs2].getABI() << "\n";
                break;

            case 4:
                cout << "\tXOR\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", "
                     << registers[rs2].getABI() << "\n";
                break;

            case 5:
                if (funct7 == 32) {
                    cout << "\tSRA\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", "
                         << registers[rs2].getABI() << "\n";
                } else {
                    cout << "\tSRL\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", "
                         << registers[rs2].getABI() << "\n";
                }
                break;
            case 6:
                cout << "\tOR\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", "
                     << registers[rs2].getABI() << "\n";
                break;
            case 7:
                cout << "\tAND\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", "
                     << registers[rs2].getABI() << "\n";
                break;

            default:
                cout << "\tUnknown R Instruction \n";
        }
    }
    else if(opcode == 0x13)
    {
        switch (funct3) {
            case 0:
                if(opcode==0x13) {
                    cout << "\tADDI\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << "0x"
                         << hex << setw(3) << (I_imm & 0x00000FFF) << "\n";
                }
                break;
            case 2:
                cout << "\tSLTI\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << "0x" << hex << setw(3) << (I_imm & 0x00000FFF) << "\n";
                break;
            case 3:
                cout << "\tSLTIU\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << "0x" << hex << setw(3) << (I_immU & 0x00000FFF) << "\n";
                break;
            case 4:
                cout << "\tXORI\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << "0x" << hex << setw(3) << (I_imm & 0x00000FFF) << "\n";
                break;
            case 6:
                cout << "\tORI\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << "0x" << hex << setw(3) << (I_imm & 0x00000FFF) << "\n";
                break;
            case 7:
                cout << "\tANDI\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << "0x" << hex << setw(3) << (I_imm & 0x00000FFF) << "\n";
                break;
            case 1:
                cout << "\tSLLI\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << "0x" << hex << setw(2) << shamt << "\n";
                break;
            case 5:
                if(funct7==0) {
                    cout << "\tSRLI\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << "0x" << hex << setw(2) << shamt << "\n";
                } else {
                    cout << "\tSRAI\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", " << "0x" << hex << setw(2) << shamt << "\n";
                }
                break;
            default:
                cout << "\tUnknown I Instruction \n";
        }

    }
    else if(opcode == 0x03)
    {
        switch (funct3) {
            case 0:
                cout << "\tLB\t" << registers[rd].getABI() << ", " << "0x" << hex << setw(3) << (I_imm & 0x00000FFF) << "(" << registers[rs1].getABI() << ")" << "\n";
                break;
            case 1:
                cout << "\tLH\t" << registers[rd].getABI() << ", " << "0x" << hex << setw(3) << (I_imm & 0x00000FFF) << "(" << registers[rs1].getABI() << ")" << "\n";
                break;
            case 2:
                cout << "\tLW\t" << registers[rd].getABI() << ", " << "0x" << hex << setw(3) << (I_imm & 0x00000FFF) << "(" << registers[rs1].getABI() << ")" << "\n";
                break;
            case 4:
                cout << "\tLBU\t" << registers[rd].getABI() << ", " << "0x" << hex << setw(3) << (I_imm & 0x00000FFF) << "(" << registers[rs1].getABI() << ")" << "\n";
                break;
            case 5:
                cout << "\tLHU\t" << registers[rd].getABI() << ", " << "0x" << hex << setw(3) << (I_imm & 0x00000FFF) << "(" << registers[rs1].getABI() << ")" << "\n";
                break;
            default:
                cout << "\tUnknown Load Instruction \n";
                break;
        }

    }
    else if(opcode == 0x23)
    {
        switch (funct3) {
            case 0:
                cout << "\tSB\t" << registers[rs2].getABI() << ", " << S_imm << "(" << registers[rs1].getABI() << ")" << "\n";
                break;
            case 1:
                cout << "\tSH\t" << registers[rs2].getABI() << ", " << S_imm << "(" << registers[rs1].getABI() << ")" << "\n";
                break;
            case 2:
                cout << "\tSW\t" << registers[rs2].getABI() << ", " << S_imm << "(" << registers[rs1].getABI() << ")" << "\n";
                break;
            default:
                cout << "\tUnknown Load Instruction \n";
                break;
        }

    }
    else if(opcode == 0x63)
    {
        switch (funct3)
        {
            case 0:
                cout << "\tBEQ\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex << setw(13) << b_imm + instPC1 << "\n";
                break;

            case 1:
                cout << "\tBNE\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex << setw(13) << b_imm + instPC1 << "\n";
                break;

            case 4:
                cout << "\tBLT\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex << setw(13) << b_imm + instPC1 << "\n";
                break;

            case 5:
                cout << "\tBGE\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex << setw(13) << b_imm + instPC1 << "\n";
                break;

            case 6:
                cout << "\tBLTU\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex << setw(13) << b_imm + instPC1 << "\n";
                break;

            case 7:
                cout << "\tBGEU\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex << setw(13) << b_imm + instPC1 << "\n";
                break;

            default:
                cout << "\tUnknown B Instruction \n";
        }

    }
    else if(opcode == 0x6F)
    {
        cout << "\tJAL\t" << registers[rd].getABI() << ", " << "0x" << hex<< setw(13)<< j_imm + instPC1 << endl;
    }
    else if(opcode == 0x37 || opcode == 0x17)
    {
        if(opcode == 0x37) {
            cout << "\tLUI\t" << registers[rd].getABI() << ", " << "0x" << hex << setw(5) << (U_imm & 0x000FFFFF) << endl;
        } else if(opcode == 0x17) {
            cout << "\tAUIPC\t" << registers[rd].getABI() << ", " << "0x" << hex << setw(5) << (U_imm & 0x000FFFFF) << endl;
        } else {
            cout << "\tUnknown U Instruction \n";
        }

    }
    else if(opcode == 0x67)
    {
        if(rd==0)
        {
            cout << "\tJALR\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", "<< "0x" << hex << setw(3)<<
                 ( J_imm & 0x00000FFF)<<endl;
        }
        else if(rd!=0)
        {
            cout << "\tJALR\t" << registers[rd].getABI() << ", " << registers[rs1].getABI() << ", "<< "0x" << hex << setw(3)<<
                 ( J_imm & 0x00000FFF)<<endl;
        }
    }
    else if(opcode==0x73)
    {
        cout<<"\tECALL\t"<<endl;
    }
    else cout<<"\tUnknown Instruction \n";
}


void instDecPrint(unsigned int instWord) {
    unsigned int instPC = Pc - 4;
    unsigned int opcode = instWord & 0x0000007F;
    unsigned int rd, rs1, rs2, funct3, funct7;
    int16_t b_imm;
    rd = (instWord >> 7) & 0x0000001F;
    funct3 = (instWord >> 12) & 0x00000007;
    rs1 = (instWord >> 15) & 0x0000001F;
    rs2 = (instWord >> 20) & 0x0000001F;

    // R Type
    funct7 = (instWord >> 25)  & 0x0000007F;

    // B Type
    int instPC1 = Pc - 4;
    b_imm = ((instWord >> 31) & 0x1) << 12;
    b_imm |= ((instWord >> 7) & 0x1) << 11;
    b_imm |= ((instWord >> 25) & 0x3F) << 5;
    b_imm |= ((instWord >> 8) & 0xF) << 1;
    b_imm |= 0;

    // I Type
    unsigned int shamt, I_immU;
    int16_t I_imm;
    shamt= (instWord >> 20) & 0x0000001F;
    I_imm = ((instWord >> 20) & 0xFFF);
    I_immU = ((instWord >> 20) & 0xFFF);


    // S Type
    int32_t S_imm;
    S_imm = (instWord >> 7) & 0x0000001F;
    S_imm |= (instWord>>13) & 0x0007F000;

    // U Type
    int U_imm;
    U_imm = ((instWord >> 12) & 0x000FFFFF);

    // J Type
    int16_t j_imm;
    j_imm = ((instWord >> 31) & 0x1) << 20;
    j_imm |= ((instWord >> 12) & 0xFF) << 12;
    j_imm |= ((instWord >> 20) & 0x1) << 11;
    j_imm |= ((instWord >> 21) & 0x3FF) << 1;
    j_imm |= 0;
    int16_t J_imm;
    J_imm = ((instWord >> 20) & 0xFFF);

    printPrefix(instPC, instWord);
    printIntInst(rd, rs1, rs2, opcode, funct3, funct7, b_imm, I_imm, I_immU, S_imm, j_imm, J_imm, U_imm, instPC1, shamt);

}

void instDecExe(unsigned int instWord) {
    unsigned int instPC = Pc - 4;
    unsigned int opcode = instWord & 0x0000007F;
    unsigned int rd, rs1, rs2, funct3, funct7;
    int16_t b_imm;
    rd = (instWord >> 7) & 0x0000001F;
    funct3 = (instWord >> 12) & 0x00000007;
    rs1 = (instWord >> 15) & 0x0000001F;
    rs2 = (instWord >> 20) & 0x0000001F;

    // R Type
    funct7 = (instWord >> 25)  & 0x0000007F;

    // B Type
    int instPC1 = Pc - 4;
    b_imm = ((instWord >> 31) & 0x1) << 12;
    b_imm |= ((instWord >> 7) & 0x1) << 11;
    b_imm |= ((instWord >> 25) & 0x3F) << 5;
    b_imm |= ((instWord >> 8) & 0xF) << 1;
    b_imm |= 0;

    // I Type
    unsigned int shamt, I_immU;
    int16_t I_imm;
    shamt= (instWord >> 20) & 0x0000001F;
    I_imm = ((instWord >> 20) & 0xFFF);
    I_immU = ((instWord >> 20) & 0xFFF);


    // S Type
    int32_t S_imm;
    S_imm = (instWord >> 7) & 0x0000001F;
    S_imm |= (instWord>>13) & 0x0007F000;

    // U Type
    int U_imm;
    U_imm = ((instWord >> 12) & 0x000FFFFF);

    // J Type
    int16_t j_imm;
    j_imm = ((instWord >> 31) & 0x1) << 20;
    j_imm |= ((instWord >> 12) & 0xFF) << 12;
    j_imm |= ((instWord >> 20) & 0x1) << 11;
    j_imm |= ((instWord >> 21) & 0x3FF) << 1;
    j_imm |= 0;
    int16_t J_imm;
    J_imm = ((instWord >> 20) & 0xFFF);

    if(!exitProgram)
    {
        printPrefix(instPC, instWord);
        std::cout << std::dec; // Switch back to decimal for register identifiers
        if (opcode == 0x33) { // R Instructions
            rType(rd, rs1, rs2, funct3,funct7);
        }
        else if(opcode == 0x13)
        {
            iType(rd, rs1, funct3,funct7, I_imm, I_immU, shamt, opcode);
        }
        else if(opcode == 0x03)
            Load(rd, rs1, funct3, I_imm);
        else if(opcode == 0x23)
        {
            sType(rs1, rs2, funct3, S_imm);
        }
        else if(opcode == 0x63)
        {
            Pc=bType(rd, rs1, rs2, funct3, b_imm, instPC1);
        }
        else if(opcode == 0x6F)
        {
            Pc=jType(rd, j_imm, instPC1);
        }
        else if(opcode == 0x37 || opcode == 0x17)
        {
            uType(rd, opcode, U_imm);
        }
        else if(opcode == 0x67)
        {
            Pc=JalrType(rs1, rd, J_imm, instPC1);
        }
        else if(opcode==0x73)
        {
            exitProgram = ecall();
        }
        printIntInst(rd, rs1, rs2, opcode, funct3, funct7, b_imm, I_imm, I_immU, S_imm, j_imm, J_imm, U_imm, instPC1, shamt);
    }
}
void compressPrint(unsigned int instHalf)
{
    unsigned int instPC = Pc - 2;
    unsigned int opcode = instHalf & 0x3;
    unsigned int rd, rs1,funct3;
}


void compressLog(unsigned int instHalf)
{
    unsigned int instPC = Pc - 2;
    unsigned int rd, rs1,funct3;
}


int main(int argc, char *argv[]) {
    unsigned int instWord1 = 0;
    unsigned int instWord2 = 0; // Variable to store instruction word
    unsigned int check;
    ifstream iFile;
    if (argc < 1) emitError("use: rvsim <machine_code_file_name> [data_section_file_name]\n");

    if(argv[2] != nullptr) {
        iFile.open(argv[2], ios::in | ios::binary | ios::ate);

        if (iFile.is_open()) {

            int fsize = iFile.tellg();
            if(fsize > 64*1024) emitError("Data section file is larger than data memory");
            iFile.seekg(0, iFile.beg);

            if (!iFile.read((char *) (memory + dataAddr), fsize)) emitError("Cannot read from data file\n");
        } else emitError("Cannot read from data file\n");
        iFile.close();
    }

    iFile.open(argv[1], ios::in | ios::binary | ios::ate);

    if (iFile.is_open())
    {
        initialiseRegs();
        int fsize = iFile.tellg();
        if(fsize > 64*1024) emitError("machine code file is larger than data memory");
        iFile.seekg(0, iFile.beg);

        if (!iFile.read((char *) (memory + textAddr), fsize)) emitError("Cannot read from machine code file\n");
        cout<<"translate"<<endl;
        while (Pc < fsize || Pc < fsize) {
            if (Pc < fsize) {
                check=(unsigned char) memory[Pc];
                if(check&3==3)
                {
                    instWord1 = (unsigned char) memory[Pc] | (((unsigned char) memory[Pc + 1]) << 8) | (((unsigned char) memory[Pc + 2]) << 16) | (((unsigned char) memory[Pc + 3]) << 24);
                    Pc += 4;
                    instDecPrint(instWord1);
                }
                else
                {
                    instWord1 = (unsigned char) memory[Pc] | (((unsigned char) memory[Pc + 1]) << 8) | (((unsigned char) memory[Pc + 2]) << 16) | (((unsigned char) memory[Pc + 3]) << 24);
                    Pc += 2;
                    compressPrint(instWord1);

                }

            }

        }
        Pc=0;
        cout<<"log "<<endl;
        iFile.seekg(0, iFile.beg);
        while (Pc < fsize || Pc < fsize)
        {
            if (Pc < fsize) {
                check=(unsigned char) memory[Pc];
                if(check&3==3)
                {
                    instWord1 = (unsigned char) memory[Pc] | (((unsigned char) memory[Pc + 1]) << 8) | (((unsigned char) memory[Pc + 2]) << 16) | (((unsigned char) memory[Pc + 3]) << 24);
                    Pc += 4;
                    instDecExe(instWord1);
                }
                else
                {
                    instWord1 = (unsigned char) memory[Pc] | (((unsigned char) memory[Pc + 1]) << 8) | (((unsigned char) memory[Pc + 2]) << 16) | (((unsigned char) memory[Pc + 3]) << 24);
                    Pc += 2;
                    compressLog(instWord1);

                }
            }
        }

    }
    else emitError("Cannot access input file\n");

    printRegContent();

    cout<<"\n==============================Console Output=============================="<<endl;
    for (int i =0; i<output.size(); i++)
        cout << output[i] << endl;


}