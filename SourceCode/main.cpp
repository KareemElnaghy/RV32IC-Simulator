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
                cout << "\tLB\t" << registers[rd].getABI() << ", " << dec << I_imm << "(" << registers[rs1].getABI() << ")" << "\n";
                break;
            case 1:
                cout << "\tLH\t" << registers[rd].getABI() << ", " <<dec << I_imm << "(" << registers[rs1].getABI() << ")" << "\n";
                break;
            case 2:
                cout << "\tLW\t" << registers[rd].getABI() << ", " << dec << I_imm << "(" << registers[rs1].getABI() << ")" << "\n";
                break;
            case 4:
                cout << "\tLBU\t" << registers[rd].getABI() << ", " << dec << I_imm << "(" << registers[rs1].getABI() << ")" << "\n";
                break;
            case 5:
                cout << "\tLHU\t" << registers[rd].getABI() << ", " << dec << I_imm << "(" << registers[rs1].getABI() << ")" << "\n";
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
                cout << "\tBEQ\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex << setw(8) << b_imm + instPC1 << "\n";
                break;

            case 1:
                cout << "\tBNE\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex << setw(8) << b_imm + instPC1 << "\n";
                break;

            case 4:
                cout << "\tBLT\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex << setw(8) << b_imm + instPC1 << "\n";
                break;

            case 5:
                cout << "\tBGE\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex << setw(8) << b_imm + instPC1 << "\n";
                break;

            case 6:
                cout << "\tBLTU\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex << setw(8) << b_imm + instPC1 << "\n";
                break;

            case 7:
                cout << "\tBGEU\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex << setw(8) << b_imm + instPC1 << "\n";
                break;

            default:
                cout << "\tUnknown B Instruction \n";
        }

    }
    else if(opcode == 0x6F)
    {
        cout << "\tJAL\t" << registers[rd].getABI() << ", " << "0x" << hex<< setw(8)<< j_imm + instPC1 << endl;
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

    int signedBit = (b_imm >> 12) & 1;
    if(signedBit==1)
        b_imm|=0xE000;


    // I Type
    unsigned int shamt, I_immU;
    int16_t I_imm;
    shamt= (instWord >> 20) & 0x0000001F;
    I_imm = ((instWord >> 20) & 0xFFF);
    I_immU = ((instWord >> 20) & 0xFFF);
    signedBit = (I_imm >> 11) & 1;
    if(signedBit==1)
        I_imm|=0xF000;


    // S Type
    int32_t S_imm;
    S_imm = (instWord >> 7) & 0x0000001F;
    S_imm |= (instWord>>20) & 0xFE0;
     signedBit = (S_imm >> 11) & 1;
    if(signedBit==1)
        S_imm|=0xFFFFF00;

    // U Type
    int32_t U_imm;
    U_imm = ((instWord >> 12) & 0x000FFFFF);
    signedBit = (U_imm >> 19) & 1;
    if(signedBit==1)
        U_imm |= 0xFFF00000;

    // J Type
    int32_t j_imm;
    j_imm = ((instWord >> 31) & 0x1) << 20;
    j_imm |= ((instWord >> 12) & 0xFF) << 12;
    j_imm |= ((instWord >> 20) & 0x1) << 11;
    j_imm |= ((instWord >> 21) & 0x3FF) << 1;
    j_imm |= 0;
     signedBit = (j_imm >> 20) & 1;
    if (signedBit == 1) {
        j_imm |= 0xFFE00000;
    }
    int16_t J_imm;
    J_imm = ((instWord >> 20) & 0xFFF);

    printPrefix(instPC1, instWord);
    printIntInst(rd, rs1, rs2, opcode, funct3, funct7, b_imm, I_imm, I_immU, S_imm, j_imm, J_imm, U_imm, instPC1, shamt);

}

void instDecExe(unsigned int instWord) {
    bool c=false;
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
    int signedBit = (b_imm >> 12) & 1;
    if(signedBit==1)
        b_imm|=0xE000;

    // I Type
    unsigned int shamt, I_immU;
    int16_t I_imm;
    shamt= (instWord >> 20) & 0x0000001F;
    I_imm = ((instWord >> 20) & 0xFFF);
    I_immU = ((instWord >> 20) & 0xFFF);
     signedBit = (I_imm >> 11) & 1;
    if(signedBit==1)
        I_imm|=0xF000;


    // S Type
    int32_t S_imm;
    S_imm = (instWord >> 7) & 0x0000001F;
    S_imm |= (instWord>>20) & 0xFE0;
     signedBit = (S_imm >> 11) & 1;
    if(signedBit==1)
        S_imm|=0xFFFFF00;

    // U Type
    int U_imm;
    U_imm = ((instWord >> 12) & 0x000FFFFF);
    signedBit = (U_imm >> 19) & 1;
    if(signedBit==1)
        U_imm |= 0xFFF00000;

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
        printPrefix(instPC1, instWord);
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
            Pc=bType(rs1, rs2, funct3, b_imm,c);
        }
        else if(opcode == 0x6F)
        {
            Pc=jType(rd, j_imm, c);
        }
        else if(opcode == 0x37 || opcode == 0x17)
        {
            uType(rd, opcode, U_imm);
        }
        else if(opcode == 0x67)
        {
            Pc=JalrType(rs1, rd, J_imm, c);
        }
        else if(opcode==0x73)
        {
            exitProgram = ecall();
        }
        printIntInst(rd, rs1, rs2, opcode, funct3, funct7, b_imm, I_imm, I_immU, S_imm, j_imm, J_imm, U_imm, instPC1, shamt);
    }
}
void compressPrint(unsigned int instHalf, int16_t imm, int instPC)
{
    // unsigned int instPC = Pc - 2;
    int signedBit;
    unsigned int rd_rs1, rs2, rd_rs1D,rs1_D,rd_D,rs2_d, funct3,funct4,funct8, opcode;
    rd_rs1 = (instHalf >> 7)&0x1F;
    rs2 = (instHalf >> 2) & 0x1F;
    opcode = instHalf & 3;
    funct3 = (instHalf>>13)&0x7;
    funct4 = (instHalf >> 12)& 0x1F;
    rs1_D = (instHalf >> 7) & 0x7;
    rs1_D+=8;
    rd_rs1D = rs1_D;
    rd_D = (instHalf>> 2) & 0x3;
    rd_D += 8;
    rs2_d = rd_D;
    funct8 = ((instHalf >> 10) & 0x3) | (((instHalf >> 13) & 0x7) << 3);


    switch (opcode){
        case 0:
            if(funct3==0) {
                cout<<"\tC.ADDI4SPN\t"<<registers[rd_D].getABI()<<", "<<dec<<imm<<endl;

            }
            else if(funct3==0x2) {
                    cout<<"\tC.LW\t"<<registers[rd_D].getABI()<<", "<<dec<<imm<<"("<<registers[rd_D].getABI()<<")"<<endl;
            }
            else if(funct3 == 0b110)
                cout<<"\tC.SW\t"<<registers[rd_D].getABI()<<", "<<dec<<imm<<"("<<registers[rs2_d].getABI()<<")"<<endl;
        break;

        case 1:
            if(funct3==0) {
                if(rd_rs1==0)
                    cout << "\tC.NOP\t"<<endl;
                else
                    cout<<"\tC.ADDI\t"<<registers[rd_rs1].getABI()<<", "<<"0x"<<hex<<setw(3)<<(imm & 0x0FFF)<<endl;
            }
            else if(funct3==0x2) {
                cout<<"\tC.LI\t"<<registers[rd_rs1].getABI()<<", "<<"0x"<<hex<<setw(3)<<(imm & 0x0FFF)<<endl;
            }
            else if(funct3==0x3) {
                if(rd_rs1 == 0x2)
                    cout<<"\tC.ADDI16SP\t"<<"0x"<<hex<<imm<<endl;
                else
                    cout<<"\tC.LUI\t"<<registers[rd_rs1].getABI()<<", "<<"0x"<<hex<<setw(3)<<(imm & 0x0FFF)<<endl;

            }
            else if (imm == 0b10001111)
                cout<<"\tC.AND\t"<<registers[rd_rs1D].getABI()<<", "<<registers[rs2_d].getABI()<<endl;

            else if (imm == 0b10001110)
                cout<<"\tC.OR\t"<<registers[rd_rs1D].getABI()<<", "<<registers[rs2_d].getABI()<<endl;

            else if (imm == 0b10001101)
                cout<<"\tC.XOR\t"<<registers[rd_rs1D].getABI()<<", "<<registers[rs2_d].getABI()<<endl;
            else if (imm == 0b10001100)
                cout<<"\tC.SUB\t"<<registers[rd_rs1D].getABI()<<", "<<registers[rs2_d].getABI()<<endl;
            else if(funct3==1)
                cout << "\tC.JAL\t" << "0x" << hex << setw(8) << Pc << endl;

            else if(funct3==5)
                cout << "\tC.J\t"  << "0x" << hex<< setw(8)<< Pc << endl;
            else if(funct3==6) {
                cout << "\tC.BEQZ\t" << registers[rs1_D].getABI() << ", " << registers[0].getABI() << ", " << "0x" << hex << setw(8) << imm + instPC << "\n";
            }
            else if(funct3==7) {
                cout << "\tC.BNEZ\t" << registers[rs1_D].getABI() << ", " << registers[0].getABI() << ", " << "0x" << hex << setw(8) << imm + instPC << "\n";
            }

        else if(funct8==0x20 | funct8==0x24)
            cout<<"\tC.SRLI\t"<<registers[rd_rs1].getABI()<<", "<<"0x"<<hex<<setw(3)<<(imm & 0x0FFF)<<endl;

        else if(funct8==0x25 | funct8==0x21)
            cout<<"\tC.SRAI\t"<<registers[rd_rs1].getABI()<<", "<<"0x"<<hex<<setw(3)<<(imm & 0x0FFF)<<endl;
            else if (funct8 == 0x26 | funct8 == 0x22)
                cout << "\tC.ANDI\t" << registers[rd_rs1].getABI() << ", " <<(imm & 0x0FFF)<< "\n";
        break;

        case 2:
            if(funct4 == 0b1000)
            {
                if(rs2 == 0)
                    cout<<"\tC.JR\t"<<registers[rd_rs1].getABI()<<endl;
                else
                    cout<<"\tC.MV\t"<<registers[rd_rs1].getABI()<<", "<<registers[rs2].getABI()<<endl;
            }
            else if(funct4 == 0b1001)
            {
                if(rs2 == 0)
                    cout<<"\tC.JALR\t"<<registers[rd_rs1].getABI()<<endl;
                else
                    cout<<"\tC.ADD\t"<<registers[rd_rs1].getABI()<<", "<<registers[rs2].getABI()<<endl;
            }
            else if(funct3==0)
            {
                cout<<"\tC.SLLI\t"<<registers[rd_rs1].getABI()<<", "<<"0x"<<hex<<setw(3)<<(imm & 0x0FFF)<<endl;
            }
            else if(funct3==0x2)
            {
                cout<<"\tC.LWSP\t"<<registers[rd_rs1].getABI()<<", "<<dec<<imm<<endl;
            }
            else if (funct3 == 0b110)
            {
                cout<<"\tC.SWSP\t"<<registers[rs2].getABI()<<", "<<dec<<imm<<"("<<registers[2].getABI()<<")"<<endl;
            }
        break;

    }
}


void compressLog(uint16_t instHalf) {
    unsigned int instPC = Pc -2;
    bool c = true;
    int signedBit;
    unsigned int rd_rs1, rs2, rd_rs1D, rs1_D, rd_D, rs2_d, funct3, funct4, funct8, funct8_s, opcode;
    rd_rs1 = (instHalf >> 7) & 0x1F;
    rs2 = (instHalf >> 2) & 0x1F;
    opcode = instHalf & 3;
    funct3 = (instHalf >> 13) & 0x7;
    funct4 = (instHalf >> 12) & 0x1F;
    rs1_D = (instHalf >> 7) & 0x7;
    rs1_D += 8;
    rd_rs1D = rs1_D;
    rd_D = (instHalf >> 2) & 0x3;
    rd_D += 8;
    rs2_d = rd_D;
    int16_t imm;
    funct8_s = ((instHalf >> 5) & 0x3) | ((instHalf >> 8) & 0xFC);
    uint16_t immU;
    funct8 = ((instHalf >> 10) & 0x3) | (((instHalf >> 13) & 0x7) << 3);

if(!exitProgram){
    printPrefix(instPC, instHalf);
    switch (opcode) {
        case 0:
            if (funct3 == 0) {
                //C.ADDI4SPN
                imm = ((instHalf >> 4) & 0x4) | ((instHalf >> 2) & 0x8) | ((instHalf >> 7) & 0x30) |
                      ((instHalf >> 1) & 0x3C0);
                signedBit = (imm >> 9) & 1;
                if (signedBit == 1)
                    imm |= 0xFC00;
                iType(rd_D, 0x2, 0, 0, imm, imm, 0, 0x13);
            } else if (funct3 == 0x2) {
                //C.LW
                imm = ((instHalf >> 4) & 0x4) | ((instHalf >> 7) & 0x38) | ((instHalf << 1) & 0x40);
                signedBit = (imm >> 6) & 1;
                if (signedBit == 1)
                    imm |= 0xFF80;
                Load(rd_D, rs1_D, 0x2, imm);
            } else if (funct3 == 6) {
                // C.SW
                imm |= ((instHalf >> 6) & 0x1) << 2;
                imm |= ((instHalf >> 10) & 0x7) << 3;
                imm |= ((instHalf >> 5) & 0x1) << 6;


                if ((imm >> 6) & 0x1)
                    imm |= 0xF800;
                sType(rs1_D, rs2_d, 0x2, imm);
            }
        break;
        case 1:
            if (funct3 == 0) {
                //C.NOP - C.ADDI
                imm = ((instHalf >> 2) & 0x1F) | ((instHalf >> 7) & 0x20);
                signedBit = (imm >> 5) & 1;
                if (signedBit == 1)
                    imm |= 0xFFC0;
                iType(rd_rs1, rd_rs1, 0, 0, imm, 0, 0, 0x13);
            } else if (funct3 == 0x2) {
                //C.LI
                imm = ((instHalf >> 2) & 0x1F) | ((instHalf >> 7) & 0x20);

                signedBit = (imm >> 5) & 1;
                if (signedBit == 1)
                    imm |= 0xFFC0;
                iType(rd_rs1, 0, 0, 0, imm, imm, 0, 0x13);
            }
        else if (funct3 == 0x3) {
                if (rd_rs1 == 0x2) {
                    //C.ADDI16SP
                    imm = ((instHalf >> 2) & 0x10) | ((instHalf << 3) & 0x20) | ((instHalf << 1) & 0x40) |
                          ((instHalf << 4) & 0x180) | ((instHalf >> 3) & 0x200);
                    signedBit = (instHalf >> 9) & 1;
                    if (signedBit == 1)
                        imm |= 0xFC00;
                    iType(rd_rs1, rd_rs1, 0, 0, imm, imm, 0, 0x13);
                }
            else {
                    //C.LUI
                    imm = ((instHalf >> 2) & 0x1F) | ((instHalf >> 7) & 0x20);
                    signedBit = (imm >> 5) & 1;
                    if (signedBit == 1)
                        imm |= 0xFFC0;
                    uType(rd_rs1, 0x37, imm);
                }
            }
        else if (funct3 == 1) {
            //C.JAL
            imm = ((instHalf >> 3) & 0x7) | ((instHalf >> 8) & 0x8) | ((instHalf << 2) & 0x10) |
                  ((instHalf >> 2) & 0x20) | (instHalf & 0x40) | ((instHalf >> 2) & 0x180) |
                  ((instHalf << 1) & 0x200) | ((instHalf >> 2) & 0x400);
            imm*=2;
            signedBit = imm >> 11;
            if (signedBit == 1) {
                imm |= 0xF000;
            }
                Pc = jType(1, imm, c);

        }
                else if (funct3 == 5) {
                    //C.J
                    imm = ((instHalf >> 3) & 0x7) | ((instHalf >> 8) & 0x8) | ((instHalf << 2) & 0x10) |
                          ((instHalf >> 2) & 0x20) | (instHalf & 0x40) | ((instHalf >> 2) & 0x180) |
                          ((instHalf << 1) & 0x200) | ((instHalf >> 2) & 0x400);
                    signedBit = imm >> 11;
                    if (signedBit == 1)
                        imm |= 0xF000;
                    imm*=2;
                    Pc = jType(0, imm, c);
                }
                else if (funct3 == 6) {
                //C.BEQZ
                    imm = ((instHalf>>2) & 0xC) | ((instHalf >> 7) & 0x18) | ((instHalf << 3) & 0x20) | ((instHalf << 1)&0xC0) | ((instHalf >>4) &0x100);
                    //sign extension
                    signedBit = imm >> 8;
                    if (signedBit == 1)
                        imm |= 0xFE00;
                    Pc = bType(rs1_D, 0, 0, imm, c);
                }
        else if (funct3 == 7) {
            //C.BNEZ
            imm = ((instHalf>>2) & 0xC) | ((instHalf >> 7) & 0x18) | ((instHalf << 3) & 0x20) | ((instHalf << 1)&0xC0) | ((instHalf >>4) &0x100);
            //sign extension
            signedBit = imm >> 8;
            if (signedBit == 1)
                imm |= 0xFE00;


                    Pc = bType(rs1_D, 0, 1, imm, c);
                } else if (funct8 == 0x20 | funct8 == 0x24)
                {
                    //C.SRLI
                    imm = ((instHalf >> 2) & 0x1F);
                    imm |= ((instHalf >> 7) & 0x1) << 5;
                    imm &= 0b011111;
                    iType(rs1_D, rs1_D, 5, 1, 0, 0, imm, 0x13);
                } else if (funct8 == 0x25 | funct8 == 0x21) {
                    imm = ((instHalf >> 2) & 0x1F);
                    imm |= ((instHalf >> 7) & 0x1) << 5;
                    iType(rs1_D, rs1_D, 5, 0, 0, 0, imm, 0x13);

                }
                else if (funct8 == 0x26 | funct8 == 0x22) {
                    imm = ((instHalf >> 2) & 0x1F);
                    imm |= ((instHalf >> 7) & 0x1) << 5;
                    imm &= 0b011111;
                    iType(rs1_D, rs1_D, 7, 0, imm, imm, 0, 0x13);

                }
                else if (funct8_s == 0b10001111) {
                    //C.AND
                    imm=funct8_s;
                    rType(rd_rs1D, rd_rs1D, rs2_d,0x7, 0x00);
                }
                else if(funct8_s == 0b10001110)
                {
                    //C.OR
                    imm=funct8_s;
                    rType(rd_rs1D, rd_rs1D, rs2_d,0x6, 0x00);
                }
                else if(funct8_s == 0b10001101)
                {
                    //C.XOR
                    imm=funct8_s;
                    rType(rd_rs1D, rd_rs1D, rs2_d,0x4, 0x00);
                }
                else if(funct8_s == 0b10001100)
                {
                    //C.SUB
                    imm=funct8_s;
                    rType(rd_rs1D, rd_rs1D, rs2_d,0x0, 0x20);
                }
                break;
                case 2:
                    if(funct4 == 0b1000)
                    {
                        if(rs2 == 0) {
                            //C.JR
                            Pc=JalrType(rd_rs1, 0, 0, c);
                        }
                        else
                            //C.MV
                                rType(rd_rs1, 0, rs2, 0, 0x00);
                    }
                    else if(funct4 == 0b1001)
                    {
                        if(rs2 == 0)
                            //C.JALR
                                Pc=JalrType(rd_rs1, 1, 0, c);
                        else
                            //C.ADD
                                rType(rd_rs1, rd_rs1, rs2, 0, 0x00);
                    }
                    else if (funct3 == 0b110)
                    {
                        //C.SWSP
                        imm = ((instHalf >>1)&0xC0);
                        imm |= ((instHalf >> 7)&0x3C);

                        if ((imm >> 7) & 0x1)
                            imm |= 0xFF00;

                        sType(2, rs2, 0x2, imm);
                    } else if (funct3 == 0) {
                        //C.SLLI
                        imm = ((instHalf >> 2) & 0x1F) | ((instHalf >> 7) & 0x20);
                        imm &= 0b011111;

                        iType(rd_rs1, rd_rs1, 0x1, 0, 0, 0, imm, 0x13);
                    } else if (funct3 == 0x2) {
                        //C.LWSP
                        imm = ((instHalf >> 2) & 0x1C) | ((instHalf << 3) & 0x60);
                        signedBit = (imm >> 7) & 1;
                        if (signedBit == 1)
                            imm |= 0xFF00;
                        Load(rd_rs1, 0x2, 0x2, imm);

                    }
                break;

            }
    compressPrint(instHalf,imm,instPC);

    }

    }


int main(int argc, char *argv[]) {
    uint32_t instWord1 = 0;
    uint16_t instHalf = 0; // Variable to store instruction word
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

        if (!iFile.read((char *) (memory), fsize)) emitError("Cannot read from machine code file\n");

        cout<<"=================LOG=================== "<<endl;
        iFile.seekg(0, iFile.beg);
        while (Pc<fsize)
        {
                instWord1 = (unsigned char) memory[Pc] | (((unsigned char)memory[Pc+1])<<8);
            Pc+=2;
             if ((instWord1 & 0x0003)==0x3)
            {
                instWord1 = instWord1 | (((unsigned char)memory[Pc]<<16)| ((unsigned char)memory[Pc+1])<<24);
                Pc+=2;
                //cout<<"Instruction Word: "<<instWord1<<endl;
                instDecExe(instWord1);
            }
            else {
                //cout<<" Instruction Half Word: "<<instWord1<<endl;

                compressLog(instWord1);
            }
            //printRegContent();

            }


    }
    else emitError("Cannot access input file\n");

    //printRegContent();
    cout<<"\n==============================Console Output=============================="<<endl;
    for (int i =0; i<output.size(); i++)
        cout << output[i] << endl;


}
