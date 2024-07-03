//
// Created by Kareem Elnaghy on 6/29/24.
//

#include <iostream>
#include <bitset>
#include <cstdint>
#include <vector>
using namespace std;
//Global Variables
const int MEMORY_SIZE = 64*1024;
const int NUM_REGISTERS = 32;

signed int printPc;
signed int exPc;
unsigned char memory[MEMORY_SIZE];
Register registers[NUM_REGISTERS];
vector<string> output;
bool exitProgram = 0;


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
            cout << "\tUnknown R Instruction \n";
    }
}

int bType(unsigned int instWord, bool s) {

    unsigned int rs1, rs2, funct3;
    int16_t b_imm;
    signed int instPC1 = printPc - 4;
    signed int instPC2 = exPc - 4;
    int r;


    rs1 = (instWord >> 15) & 0x0000001F;
    rs2 = (instWord >> 20) & 0x0000001F;
    funct3 = (instWord >> 12) & 0x00000007;


    b_imm = ((instWord >> 31) & 0x1) << 12;
    b_imm |= ((instWord >> 7) & 0x1) << 11;
    b_imm |= ((instWord >> 25) & 0x3F) << 5;
    b_imm |= ((instWord >> 8) & 0xF) << 1;
    b_imm |= 0;


    int signedBit = (b_imm >> 12) & 1;
    if(signedBit == 1) {
        b_imm|= 0xE000;
    }



        switch (funct3)
        {
        case 0:
        if (s)
        {
        cout << "\tBEQ\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex<< setw(13) << b_imm + instPC1 << "\n";
        }
        else
        {
        if (registers[rs1].getData() == registers[rs2].getData())
        r = b_imm + instPC2;
        else
        r = exPc;
        }
        break;

        case 1:
        if (s)
        {
        cout << "\tBNE\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex<< setw(13)<< b_imm + instPC1 << "\n";
        }
        else
        {
        if (registers[rs1].getData() != registers[rs2].getData())
        r = b_imm + instPC2;
        else
        r = exPc;
        }
        break;

        case 4:
        if (s)
        {
        cout << "\tBLT\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex<< setw(13) << b_imm + instPC1 << "\n";
        }
        else
        {
        if (registers[rs1].getData() < registers[rs2].getData())
        r = b_imm + instPC2;
        else
        r = exPc;
        }
        break;

        case 5:
        if (s)
        {
        cout << "\tBGE\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex<< setw(13) << b_imm + instPC1 << "\n";
        }
        else
        {
        if (registers[rs1].getData() >= registers[rs2].getData())
        r = b_imm + instPC2;
        else
        r = exPc;
        }
        break;

        case 6:
        if (s)
        {
        cout << "\tBLTU\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex<< setw(13) << b_imm + instPC1 << "\n";
        }
        else
        {
        if (registers[rs1].getData() < registers[rs2].getData())
        r = b_imm + instPC2;
        else
        r = exPc;
        }
        break;

        case 7:
        if (s)
        {
        cout << "\tBGEU\t" << registers[rs1].getABI() << ", " << registers[rs2].getABI() << ", " << "0x" << hex<< setw(13) << b_imm + instPC1 << "\n";
        }
        else
        {
        if (registers[rs1].getData() >= registers[rs2].getData())
        r = b_imm + instPC2;
        else
        r = exPc ;
        }
        break;

        default:
        cout << "\tUnknown B Instruction \n";
        }

        return r;


        }


int jType(unsigned int instWord, bool s)
{
    unsigned int rd;
    int16_t j_imm;
    signed int instPC1 = printPc - 4;
    signed int instPC2 = exPc - 4;
     int r;

    rd = (instWord >> 7) & 0x0000001F;


    j_imm = ((instWord >> 31) & 0x1) << 20;
    j_imm |= ((instWord >> 12) & 0xFF) << 12;
    j_imm |= ((instWord >> 20) & 0x1) << 11;
    j_imm |= ((instWord >> 21) & 0x3FF) << 1;
    j_imm |= 0;



    int signedBit = (j_imm >> 12) & 1;
    if(signedBit == 1) {
        j_imm|= 0xE000;
    }


    if(s) {
       //cout << endl << "j_imm:" << j_imm << "   " << "instPC1:" << instPC1 << endl;
        cout << "\tJAL\t" << registers[rd].getABI() << ", " << "0x" << hex<< setw(13)<< j_imm + instPC1 << endl;
    }
    else {
        registers[rd].setData(exPc);
        r = j_imm + instPC2;
    }

    return r;
}

int JalrType(unsigned int instWord, bool s)
{
    signed int instPC2 = exPc - 4;
    unsigned int rd, rs1, funct3, J_immU;
    int16_t J_imm;
    signed int temp;
    unsigned int tempU;
    rd = (instWord >> 7) & 0x0000001F;
    funct3 = (instWord >> 12) & 0x00000007;
    rs1 = (instWord >> 15) & 0x0000001F;

    int r;
    J_imm = ((instWord >> 20) & 0xFFF);
   // J_immU = ((instWord >> 20) & 0xFFF);


    int signedBit = (J_imm >> 11) & 1;
    if(signedBit == 1) {
        J_imm|= 0xF000;
    }

    if(s) {
        //cout << endl << "j_imm:" << j_imm << "   " << "instPC1:" << instPC1 << endl;
        cout << "\tJALR\t" << registers[rd].getABI() << ", " << "0x" << hex<< setw(12)<< J_imm + registers[rs1].getData() << endl;
    }
    else {
        //registers[rd].setData(instPC2);
        r = J_imm + registers[rs1].getData();
    }

    return r;
}

void iType(unsigned int instWord, bool s)
{
    unsigned int rd, rs1, funct3, funct7,shamt, I_immU;
    int16_t I_imm;
    signed int temp;
    unsigned int tempU;
    rd = (instWord >> 7) & 0x0000001F;
    funct3 = (instWord >> 12) & 0x00000007;
    rs1 = (instWord >> 15) & 0x0000001F;
    funct7 = (instWord >> 25) & 0x0000007F;
    shamt= (instWord >> 20) & 0x0000001F;
    I_imm = ((instWord >> 20) & 0xFFF);
    I_immU = ((instWord >> 20) & 0xFFF);


    int signedBit = (I_imm >> 11) & 1;
    if(signedBit == 1) {
        I_imm|= 0xF000;
    }

    switch (funct3) {
        case 0:
            if(s)
            cout << "\tADDI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << "0x" << hex << setw(3) << (I_imm& 0x00000FFF) << "\n";
           else {
                temp = registers[rs1].getData() + I_imm;
                registers[rd].setData(temp);
            }
            break;
        case 2:
            if(s)
            cout << "\tSLTI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << "0x" << hex << setw(3)<< (I_imm& 0x00000FFF) << "\n";
           else
            {temp= (registers[rs1].getData() < I_imm)? 1 : 0;
            registers[rd].setData(temp);}
            break;
        case 3:
            if(s)
            cout << "\tSLTIU\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << "0x" << hex<< setw(3)<< (I_immU& 0x00000FFF) << "\n";
           else{ temp= (registers[rs1].getData() < I_immU)? 1 : 0;
            registers[rd].setData(temp);}
            break;
        case 4:
            if(s)
            cout << "\tXORI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << "0x" << hex<< setw(3)<< (I_imm& 0x00000FFF) << "\n";
           else{ temp = registers[rs1].getData() ^ I_imm;
            registers[rd].setData(temp);}
            break;
        case 6:
            if(s)
            cout << "\tORI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << "0x" << hex<< setw(3)<< (I_imm& 0x00000FFF) << "\n";

           else{ temp = registers[rs1].getData() | I_imm;
            registers[rd].setData(temp);}
            break;
        case 7:
           if(s) cout << "\tANDI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << "0x" << hex<< setw(3)<< (I_imm& 0x00000FFF) << "\n";
            else
           {temp = registers[rs1].getData() & I_imm;
            registers[rd].setData(temp);}
            break;
        case 1:
            if(s)
            cout << "\tSLLI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << "0x" << hex<< setw(2)<< shamt << "\n";
            else{temp = registers[rs1].getData() << shamt;
            registers[rd].setData(temp);}
            break;
        case 5:
            if(funct7==0) {
               if(s)
                   cout << "\tSRLI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << "0x" << hex<< setw(2)<< shamt << "\n";
                else{tempU = registers[rs1].getData() >> shamt;
                registers[rd].setData(tempU);}
            }
            else {
               if(s)
                cout << "\tSRAI\t" << registers[rd].getABI() <<", " << registers[rs1].getABI() <<", " << "0x" << hex<< setw(2)<< shamt << "\n";
              else
               {temp = registers[rs1].getData() >> shamt;
                registers[rd].setData(temp);}
            }
            break;

        default:
            cout << "\tUnknown I Instruction \n";
    }
}


void sType(unsigned int instWord, bool s)
{
    unsigned int rs1, rs2, funct3;
    int32_t I_imm, address, temp;

    funct3 = (instWord >> 12) & 0x00000007;
    rs1 = (instWord >> 15) & 0x0000001F;
    rs2 = (instWord >> 20) & 0x0000001F;
    I_imm = (instWord >> 7) & 0x0000001F;
    I_imm |= (instWord>>13) & 0x0007F000;

    int signedBit = (I_imm >> 11) & 1;
    if(signedBit == 1) {
        I_imm|= 0xF000;
    }

    switch (funct3) {
        case 0:
            if(s)
            cout << "\tSB\t" << registers[rs2].getABI() <<", " << I_imm<< "(" << registers[rs1].getABI() << ")"<<"\n";
            else {
                address = I_imm + registers[rs1].getDataU();
                memory[address] = registers[rs2].getData() & 0xFF;
            }
            break;
        case 1:
            if(s)
            cout << "\tSH\t" << registers[rs2].getABI() <<", " << I_imm<< "(" << registers[rs1].getABI() << ")"<<"\n";
            else {
                address = I_imm + registers[rs1].getDataU();
                memory[address] = registers[rs2].getData() & 0xFF;
                memory[address + 1] = registers[rs2].getData() & 0xFF00;
            }
            break;
        case 2:
            if(s)
            cout << "\tSW\t" << registers[rs2].getABI() <<", " << I_imm<< "(" << registers[rs1].getABI() << ")"<<"\n";
            else {
                address = I_imm + registers[rs1].getDataU();
                for (int i = 0; i < 4; i++) {
                    memory[address + i] = (registers[rs2].getData() >> i * 8) & 0xFF;
                }
            }
            break;

        default:
            cout << "\tUnknown Load Instruction \n";

    }
}



void uType(unsigned int instWord, bool s) {
    unsigned int rd, opcode;
    int I_imm;
    unsigned int tempU;

    opcode = instWord & 0x0000007F;
    rd = (instWord >> 7) & 0x0000001F;
    I_imm = ((instWord >> 12) & 0x000FFFFF);

    int signedBit = (I_imm >> 19) & 1;
    if(signedBit == 1) {
        I_imm|= 0xFFF000;
    }

    if(opcode == 0x37) {
        if(s) cout << "\tLUI\t" << registers[rd].getABI() <<", "<< "0x" << hex<< setw(5) << (I_imm & 0x000FFFFF)<<endl;
        else
        {tempU = I_imm << 12;
            registers[rd].setDataU(tempU);}
    }

    else if(opcode == 0x17) {
        if(s)
            cout << "\tAUIPC\t" << registers[rd].getABI() <<", "<< "0x" << hex<< setw(5) << (I_imm & 0x000FFFFF)<<endl;
        else{
                tempU = exPc + (I_imm << 12);

            registers[rd].setDataU(tempU);

        }
    }
    else
        cout << "\tUnknown U Instruction \n";
}



void Load(unsigned int instWord, bool s)
{
    unsigned int rd, rs1, funct3, opcode;
    signed int I_imm, address;
    int32_t temp;
    int signedTempBit;

    rd = (instWord >> 7) & 0x0000001F;
    funct3 = (instWord >> 12) & 0x00000007;
    rs1 = (instWord >> 15) & 0x0000001F;
    I_imm = ((instWord >> 20) & 0xFFF);

    int signedBit = (I_imm >> 11) & 1;
    if(signedBit == 1) {
        I_imm|= 0xF000;
    }

    switch (funct3) {
        case 0:
        if(s)
            cout << "\tLB\t" << registers[rd].getABI() <<", " << "0x" << hex << setw(3) << (I_imm& 0x00000FFF)<< "(" << registers[rs1].getABI() << ")"<<"\n";
        else {
            address = I_imm + registers[rs1].getData();
            temp = memory[address];
            signedTempBit = (temp >> 7) & 1;
            if(signedTempBit == 1) {
                temp|= 0xFFFFFF00;
            }
            registers[rd].setData(temp);
        }
            break;
        case 1:
            if(s)
            cout << "\tLH\t" << registers[rd].getABI() <<", " << "0x" << hex << setw(3) << (I_imm& 0x00000FFF)<< "(" << registers[rs1].getABI() << ")"<<"\n";
        else {
            address = I_imm + registers[rs1].getData();
            temp = memory[address] | (memory[address+1] << 8);
            signedTempBit = (temp >> 15) & 1;
            if(signedTempBit == 1) {
                temp|= 0xFFFF0000;
            }
            registers[rd].setData(temp);
        }
        break;
        case 2:
        if(s)
            cout << "\tLW\t" << registers[rd].getABI() <<", " << "0x" << hex << setw(3) << (I_imm& 0x00000FFF)<< "(" << registers[rs1].getABI() << ")"<<"\n";
        else {
            address = I_imm + registers[rs1].getData();
            temp = memory[address] | (memory[address+1] << 8 ) | (memory[address+2] << 16 ) | (memory[address+3] << 24 );
            registers[rd].setData(temp);
        }
        break;
        case 3:
        if(s)
            cout << "\tLBU\t" << registers[rd].getABI() <<", " << "0x" << hex << setw(3) << (I_imm& 0x00000FFF)<< "(" << registers[rs1].getABI() << ")"<<"\n";
        else {
            address = I_imm + registers[rs1].getData();
            temp = memory[address];
            registers[rd].setData(temp);
        }
        break;
        case 4:
        if(s)
            cout << "\tLHU\t" << registers[rd].getABI() <<", " << "0x" << hex << setw(3) << (I_imm& 0x00000FFF)<< "(" << registers[rs1].getABI() << ")"<<"\n";
        else {
            address = I_imm + registers[rs1].getData();
            temp = memory[address] | (memory[address+1] << 8);
            registers[rd].setData(temp);
        }
        break;
        default:
            cout << "\tUnknown Load Instruction \n";

    }
}

bool ecall(bool s)
{
    if(s)
    {
        cout<<"\tECALL\t"<<endl;
        return false;
    }
    else
    {
        if(registers[17].getDataU() == 10)
        {
            s = true;
            return false;
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
            while(memory[address+i] != '\0')
            {
                str += memory[address+i];
                i++;
            }


            output.push_back(str);
            return true;
        }
        else
        {
            cout<<"\tUnknown Call Number \n";
            return false;
        }
    }

}