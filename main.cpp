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
    registers[2].setData(64*1024-1);
}

void printRegContent()
{
    for(int i = 0; i<NUM_REGISTERS; i++)
    {
        registers[i].printRegData();
    }
};
void emitError(string msg)
{
    cout<<msg;
    exit(0);
}


void printPrefix(unsigned int instA, unsigned int instW) {
    std::cout << "0x" << std::hex << std::setfill('0') << std::setw(8)
              << instA << "\t0x" << std::setw(8) << instW;
}

void instDecPrint(unsigned int instWord) {

    unsigned int opcode = instWord & 0x0000007F;
    unsigned int instPC = printPc - 4;
    bool s=true;
    int t;

    printPrefix(instPC, instWord);
    std::cout << std::dec; // Switch back to decimal for register identifiers

    if (opcode == 0x33) { // R Instructions
        rType(instWord,s);
    }
    else if(opcode == 0x13)
    {
        iType(instWord,s);
    }
    else if(opcode == 0x03)
    {
        Load(instWord,s);
    }
    else if(opcode == 0x23)
    {
        sType(instWord,s);
    }
    else if(opcode == 0x63)
    {
        bType(instWord,s);
    }
    else if(opcode == 0x6F)
    {
        jType(instWord,s);
    }
    else if(opcode == 0x37 || opcode == 0x17)
    {
        uType(instWord,s);
    }
    else if(opcode==0x73)
    {
        ecall(s);
    }
    else cout<<"\tUnknown Instruction \n";
}



void instDecExe(unsigned int instWord) {

    unsigned int opcode = instWord & 0x0000007F;
    unsigned int instPC = exPc - 4;
    bool s=false;


    if(!exitProgram)
    {
        if (opcode == 0x33) { // R Instructions
            rType(instWord,s);
        }
        else if(opcode == 0x13)
        {
            iType(instWord,s);
        }
        else if(opcode == 0x03)
            Load(instWord,s);
        else if(opcode == 0x23)
        {
            sType(instWord,s);
        }
        else if(opcode == 0x63)
        {
            exPc=bType(instWord,s);
        }
        else if(opcode == 0x6F)
        {
            exPc=jType(instWord,s);
        }
        else if(opcode == 0x37 || opcode == 0x17)
        {
            uType(instWord,s);
        }
        else if(opcode==0x73)
        {
            exitProgram = ecall(s);
        }
    }
}



int main(int argc, char *argv[]) {
    unsigned int instWord1 = 0;
    unsigned int instWord2 = 0; // Variable to store instruction word
    ifstream iFile;
    if (argc < 1) emitError("use: rvsim <machine_code_file_name> [data_section_file_name]\n");

    iFile.open(argv[1], ios::in | ios::binary | ios::ate);

    if (iFile.is_open())
    {
        initialiseRegs();
        int fsize = iFile.tellg();

        iFile.seekg(0, iFile.beg);

        if (!iFile.read((char *) memory, fsize)) emitError("Cannot read from input file\n");

        while (printPc < fsize || exPc < fsize) {
            if (printPc < fsize) {
                instWord1 = (unsigned char) memory[printPc] | (((unsigned char) memory[printPc + 1]) << 8) | (((unsigned char) memory[printPc + 2]) << 16) | (((unsigned char) memory[printPc + 3]) << 24);
                printPc += 4;
                instDecPrint(instWord1);
            }
            if (exPc < fsize) {
                instWord2 = (unsigned char) memory[exPc] | (((unsigned char) memory[exPc + 1]) << 8) | (((unsigned char) memory[exPc + 2]) << 16) | (((unsigned char) memory[exPc + 3]) << 24);
                exPc += 4;
                instDecExe(instWord2);
            }
        }


    }
    else emitError("Cannot access input file\n");

    printRegContent();

    cout<<"Console Output"<<endl;
   for(int i = 0; i<output.size(); i++)
   {
       cout<<output[i]<<endl;
   }

}