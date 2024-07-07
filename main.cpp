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

void printIntInst(unsigned int rd, unsigned int rs1, unsigned int rs2, unsigned int opcode, unsigned int funct3, unsigned int funct7,int16_t  b_imm,int16_t I_imm,int16_t I_immU, int16_t imm, int16_t j_imm,int16_t J_imm, int16_t U_imm, int instPC1, unsigned int shamt )
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
                cout << "\tSB\t" << registers[rs2].getABI() << ", " << imm << "(" << registers[rs1].getABI() << ")" << "\n";
                break;
            case 1:
                cout << "\tSH\t" << registers[rs2].getABI() << ", " << imm << "(" << registers[rs1].getABI() << ")" << "\n";
                break;
            case 2:
                cout << "\tSW\t" << registers[rs2].getABI() << ", " << imm << "(" << registers[rs1].getABI() << ")" << "\n";
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
    int32_t imm;
    imm = (instWord >> 7) & 0x0000001F;
    imm |= (instWord>>13) & 0x0007F000;

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

    printPrefix(instPC1, instWord);
    printIntInst(rd, rs1, rs2, opcode, funct3, funct7, b_imm, I_imm, I_immU, imm, j_imm, J_imm, U_imm, instPC1, shamt);

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

    // I Type
    unsigned int shamt, I_immU;
    int16_t I_imm;
    shamt= (instWord >> 20) & 0x0000001F;
    I_imm = ((instWord >> 20) & 0xFFF);
    I_immU = ((instWord >> 20) & 0xFFF);


    // S Type
    int32_t imm;
    imm = (instWord >> 7) & 0x0000001F;
    imm |= (instWord>>13) & 0x0007F000;

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
            sType(rs1, rs2, funct3, imm);
        }
        else if(opcode == 0x63)
        {
            Pc=bType(rs1, rs2, funct3, b_imm, instPC1);
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
        printIntInst(rd, rs1, rs2, opcode, funct3, funct7, b_imm, I_imm, I_immU, imm, j_imm, J_imm, U_imm, instPC1, shamt);
    }
}
void compressPrint(unsigned int instHalf, int16_t imm)
{
    unsigned int instPC = Pc - 2;
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



    printPrefix(instPC, instHalf);

    switch (opcode){
        case 0:
            if(funct3==0) {
                cout<<"\tC.ADDI4SP\t"<<registers[rd_D].getABI()<<", "<<imm<<endl;

            }
            else if(funct3==0x2) {
                    cout<<"\tC.LW\t"<<registers[rd_D].getABI()<<", "<<imm<<"("<<registers[rd_D].getABI()<<")"<<endl;
            }
            else if(funct3 == 0b110)
                cout<<"\tC.SW\t"<<registers[rd_D].getABI()<<", "<<imm<<"("<<registers[rs2_d].getABI()<<")"<<endl;
        break;

        case 1:
            if(funct3==0) {
                if(rd_rs1==0)
                    cout << "\tC.NOP\t";
                else
                    cout<<"\tC.ADDI\t"<<registers[rd_rs1].getABI()<<", "<<hex<<imm<<endl;
            }
            else if(funct3==0x2) {
                cout<<"\tC.LI\t"<<registers[rd_rs1].getABI()<<", "<<hex<<imm<<endl;
            }
            else if(funct3==0x3) {
                if(rd_rs1 == 0x2)
                    cout<<"\tC.ADDI16SP\t"<<hex<<imm<<endl;
                else
                    cout<<"\tC.LUI\t"<<registers[rd_rs1].getABI()<<", "<<hex<<imm<<endl;

            }
            else if (imm == 0b10001111)
                cout<<"\tC.AND\t"<<registers[rd_D].getABI()<<", "<<registers[rs2_d].getABI()<<endl;

            else if (imm == 0b10001110)
                cout<<"\tC.OR\t"<<registers[rd_D].getABI()<<", "<<registers[rs2_d].getABI()<<endl;

            else if (imm == 0b10001101)
                cout<<"\tC.XOR\t"<<registers[rd_D].getABI()<<", "<<registers[rs2_d].getABI()<<endl;
            else if (imm == 0b10001100)
                cout<<"\tC.SUB\t"<<registers[rd_D].getABI()<<", "<<registers[rs2_d].getABI()<<endl;
            else if(funct3==1)
                cout << "\tC.JAL\t" << "0x" << hex << setw(13) << imm + instPC << endl;

            else if(funct3==5)
                cout << "\tC.J\t"  << "0x " << hex<< setw(13)<< imm + instPC << endl;
            else if(funct3==6)
                cout << "\tC.BEQZ\t" << registers[rs1_D].getABI() << ", " << registers[0].getABI() << ", " << "0x" << hex << setw(13) << imm + instPC << "\n";
            else if(funct3==7)
                cout << "\tC.BNEZ\t" << registers[rs1_D].getABI() << ", " << registers[0].getABI() << ", " << "0x" << hex << setw(13) << imm + instPC << "\n";

        else if(funct8==0x20 | funct8==0x24)
            cout<<"\tC.SRLI\t"<<registers[rd_rs1].getABI()<<", "<<imm<<endl;

        else if(funct8==0x25 | funct8==0x21)
            cout<<"\tC.SRAI\t"<<registers[rd_rs1].getABI()<<", "<<imm<<endl;
            else if (funct8 == 0x26 | funct8 == 0x22)
                cout << "\tAND\t" << registers[rd_rs1].getABI() << ", " << imm<< "\n";
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
                cout<<"\tC.SLLI\t"<<registers[rd_rs1].getABI()<<", "<<imm<<endl;
            }
            else if(funct3==0x2)
            {
                cout<<"\tC.LWSP\t"<<registers[rd_rs1].getABI()<<", "<<imm<<endl;
            }
            else if (funct3 == 0b110)
            {
                sType(rs2, 2, 0b011,imm);
                cout<<"\tC.SWSP\t"<<registers[rs2].getABI()<<", "<<imm<<"("<<registers[2].getABI()<<")"<<endl;
            }
        break;

    }
}


void compressLog(uint16_t instHalf) {
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
    funct8 = (instHalf >> 10) & 0x3 | ((instHalf >> 13) & 0x7) << 3;
//int16_t cj = (instHalf >> 2) & 0x7FF;
//
//    //CI parsing
//    int16_t CI_imm = ((instHalf >> 2) & 0x1F) | ((instHalf >> 6) & 0x20);
//    int16_t CI_immU = CI_imm;
//    signedBit = (CI_imm >> 5) & 1;
//    if(signedBit == 1)
//        CI_imm|= 0xFFC0;
//
//    //CIW parsing
//    int16_t CIW_imm = (instHalf >> 5) & 0xFF;
//    signedBit = (CIW_imm >> 7) & 1;
//    if(signedBit == 1)
//        CI_imm|= 0xFF00;
//
//    //CL parsing
//    int16_t CL_imm = ((instHalf >> 5) & 3) | ((instHalf >> 8) & 0x1C);
//    signedBit = (CL_imm >> 4) & 1;
//    if(signedBit == 1)
//        CL_imm|= 0xFF70;
//
//    //CB parsing
//    int16_t B_imm = (instHalf >> 2) & 0x1F;
//    B_imm |= (instHalf >> 10) & 0xF<<4;
//
//    int16_t shift=B_imm & 0x1F;
//    shift|= (B_imm >> 12) & 0x1;
//    funct8= B_imm & 0xFC00;

    //  imm = ((instHalf >> 10) & 0x7)  << 6 | ((instHalf >> 3) & 0x7)  << 1 | ((instHalf >> 2) & 0x1)   << 5;





//    signedBit = (B_imm >> 7) & 1;
//    if(signedBit == 1)
//        B_imm|= 0xFF00;
//
//
//    //CJ parsing
//    int16_t J_imm;
//
//    // Extract each bit and place it in the correct position in J_imm
//    J_imm = ((instHalf >> 3) & 0x7) | ((instHalf >> 8) & 0x8) | ((instHalf << 2) & 0x10) | ((instHalf>>2) & 0x20) | (instHalf&0x40) | ((instHalf>>2)&0x180) | ((instHalf <<1) & 0x200) | ((instHalf>>2)&0x400);
//
//
//    // Sign extend J_imm to 16 bits
//    signedBit=imm>>11;
//    if (signedBit==1) {
//        J_imm |= 0xF000;
//    }
//
//    // CSS parsing
//    int16_t SS_imm = (instHalf>>7)& 0x3F;
//    signedBit = (SS_imm >> 7) & 1;
//    if(signedBit == 1)
//        SS_imm|= 0x70;
//
//    // CS Parsing
//    int16_t S_imm = ((instHalf >> 5) & 3) | ((instHalf >> 8) & 0x1C) | (funct3>>7);
//    compressPrint(instHalf);

    switch (opcode) {
        case 0:
            if (funct3 == 0) {
                //C.ADDI4SPN
                imm = ((instHalf >> 4) & 0x4) | ((instHalf >> 2) & 0x8) | ((instHalf >> 7) & 0x30) |
                      ((instHalf >> 1) & 0x3C0);
                signedBit = (imm >> 9) & 1;
                if (signedBit == 1)
                    imm |= 0xFC00;
                iType(rd_D, 0x0, 0, 0, imm, imm, 0, 0x13);
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
                imm = ((instHalf >> 2) & 0x1F) | ((instHalf >> 6) & 0x20);
                signedBit = (imm >> 5) & 1;
                if (signedBit == 1)
                    imm |= 0xFFC0;
                iType(rd_rs1, rd_rs1, 0, 0, imm, 0, 0, 0x13);
            } else if (funct3 == 0x2) {
                //C.LI
                imm = ((instHalf >> 2) & 0x1F) | ((instHalf >> 6) & 0x20);
                signedBit = (imm >> 5) & 1;
                if (signedBit == 1)
                    imm |= 0xFFC0;
                iType(rd_rs1, 0, 0, 0, imm, imm, 0, 0x13);
            } else if (funct3 == 0x3) {
                if (rd_rs1 == 0x2) {
                    //C.ADDI16SP
                    imm = ((instHalf >> 2) & 0x10) | ((instHalf << 3) & 0x20) | ((instHalf << 1) & 0x40) |
                          ((instHalf << 4) & 0x180) | ((instHalf >> 3) & 0x200);
                    signedBit = (instHalf >> 9) & 1;
                    if (signedBit == 1)
                        imm |= 0xFC00;
                    iType(rd_rs1, rd_rs1, 0, 0, imm, imm, 0, 0x13);
                } else {
                    //C.LUI
                    imm = ((instHalf >> 2) & 0x1F) | ((instHalf >> 6) & 0x20);
                    signedBit = (imm >> 5) & 1;
                    if (signedBit == 1)
                        imm |= 0xFFC0;
                    uType(rd_rs1, 0x37, imm);
                }
            } else if (funct3 == 1) {
                imm = ((instHalf >> 3) & 0x7) | ((instHalf >> 8) & 0x8) | ((instHalf << 2) & 0x10) |
                      ((instHalf >> 2) & 0x20) | (instHalf & 0x40) | ((instHalf >> 2) & 0x180) |
                      ((instHalf << 1) & 0x200) | ((instHalf >> 2) & 0x400);
                signedBit = imm >> 11;
                if (signedBit == 1) {
                    imm |= 0xF000;

                    Pc = jType(1, imm, c);
                } else if (funct3 == 5)
                {
                    imm = ((instHalf >> 3) & 0x7) | ((instHalf >> 8) & 0x8) | ((instHalf << 2) & 0x10) |
                          ((instHalf >> 2) & 0x20) | (instHalf & 0x40) | ((instHalf >> 2) & 0x180) |
                          ((instHalf << 1) & 0x200) | ((instHalf >> 2) & 0x400);
                    signedBit = imm >> 11;
                    if (signedBit == 1)
                        imm |= 0xF000;
                    Pc = jType(0, imm, c);
                } else if (funct3 == 6) {

                    imm = ((instHalf >> 10) & 0x7) << 6 | ((instHalf >> 3) & 0x7) << 1 | ((instHalf >> 2) & 0x1) << 5;
                    //sign extension
                    signedBit = imm >> 8;
                    if (signedBit == 1)
                        imm |= 0xFE00;
                    Pc = bType(rs1_D, 0, 0, imm, c);
                } else if (funct3 == 7) {
                    imm = ((instHalf >> 10) & 0x7) << 6 | ((instHalf >> 3) & 0x7) << 1 | ((instHalf >> 2) & 0x1) << 5;
                    //sign extension

                    Pc = bType(rs1_D, 0, 1, imm, c);
                } else if (funct8 == 0x20 | funct8 == 0x24)
                {
                    immU = ((instHalf >> 2) & 0x1F);
                    immU |= ((instHalf >> 7) & 0x1) << 5;
                    iType(rs1_D, rs1_D, 5, 1, imm, imm, immU, 0x13);
                } else if (funct8 == 0x25 | funct8 == 0x21) {
                    immU = ((instHalf >> 2) & 0x1F);
                    immU |= ((instHalf >> 7) & 0x1) << 5;
                    iType(rs1_D, rs1_D, 5, 0, imm, imm, immU, 0x13);

                }
                else if (funct8 == 0x26 | funct8 == 0x22) {
                    imm = ((instHalf >> 2) & 0x1F);
                    imm |= ((instHalf >> 7) & 0x1) << 5;
                    iType(rs1_D, rs1_D, 7, 0, imm, imm, immU, 0x13);

                }
                else if (funct8_s == 0b10001111) {
                    //C.AND
                    rType(rd_D, rd_D, rs2_d, 0x7, 0x00);
                } else if (funct8_s == 0b10001110) {
                    //C.OR
                    rType(rd_D, rd_D, rs2_d, 0x6, 0x00);
                } else if (funct8_s == 0b10001101) {
                    //C.XOR
                    rType(rd_D, rd_D, rs2_d, 0x4, 0x00);
                } else if (funct8_s == 0b10001100) {
                    //C.SUB
                    rType(rd_D, rd_D, rs2_d, 0x0, 0x20);
                }
                break;
                case 2:
                    if (funct4 == 0b1000) {
                        if (rs2 == 0)
                            //C.JR
                            Pc = JalrType(rd_rs1, 0, 0, c);
                        else
                            //C.MV
                            rType(rd_rs1, 0, rs2, 0, 0x00);
                    } else if (funct4 == 0b1001) {
                        if (rs2 == 0)
                            //C.JALR
                            Pc = JalrType(rd_rs1, 1, 0, c);
                        else
                            //C.ADD
                            rType(rd_rs1, rd_rs1, rs2, 0, 0x00);
                    } else if (funct3 == 0b110) {
                        //C.SWSP
                        imm |= ((instHalf >> 9) & 0xF) << 2;
                        imm |= ((instHalf >> 7) & 0x3) << 6;

                        if ((imm >> 7) & 0x1)
                            imm |= 0xFF00;

                        sType(rs2, 2, 0b011, imm);
                    } else if (funct3 == 0) {
                        //C.SLLI
                        immU = ((instHalf >> 2) & 0x1F) | ((instHalf >> 6) & 0x20);

                        iType(rd_rs1, rd_rs1, 0x1, 0, 0, 0, immU, 0x13);
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
            compressPrint(instHalf, imm);
    }


}
int main(int argc, char *argv[]) {
    unsigned int instWord1 = 0;
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

        if (!iFile.read((char *) (memory + textAddr), fsize)) emitError("Cannot read from machine code file\n");
        cout<<"translate"<<endl;
        while (Pc < fsize || Pc < fsize) {
            if (Pc < fsize) {
                check=(unsigned char) memory[Pc] & 3;
                if(check == 0x3)
                {
                    instWord1 = (unsigned char) memory[Pc] | (((unsigned char) memory[Pc + 1]) << 8) | (((unsigned char) memory[Pc + 2]) << 16) | (((unsigned char) memory[Pc + 3]) << 24);
                    Pc += 4;
                    //instDecPrint(instWord1);
                }
                else
                {
                     instWord1 = (unsigned char) memory[Pc] | (((unsigned char) memory[Pc + 1]) << 8) ;
                   Pc += 2;
                    //compressPrint(instWord1);

                }

            }

        }

        Pc=0;
        cout<<"log "<<endl;
        iFile.seekg(0, iFile.beg);
        while (Pc < fsize)
        {
                check=(unsigned char) memory[Pc]&3;
                if(check==3)
                {
                    instWord1 = (unsigned char) memory[Pc] | (((unsigned char) memory[Pc + 1]) << 8) | (((unsigned char) memory[Pc + 2]) << 16) | (((unsigned char) memory[Pc + 3]) << 24);
                    Pc += 4;
                    instDecExe(instWord1);
                }
                else
                {


                    instHalf = (unsigned char) memory[Pc] | (((unsigned char) memory[Pc + 1]) << 8) ;
                    Pc += 2;
                    compressLog(instHalf);

                }
            }


    }
    else emitError("Cannot access input file\n");

    printRegContent();

    cout<<"\n==============================Console Output=============================="<<endl;
    for (int i =0; i<output.size(); i++)
        cout << output[i] << endl;


}