#include <iostream>
#include <fstream>
#include <iomanip>
#include "Register.h"
#include "Instructions.h"
using namespace std;

// Global Variables
unsigned int pc = 0;
unsigned char memory[64*(1024)] ;
Register registers[32];


void initialiseRegs()
{
    for(unsigned int i = 0; i<32; i++)
    {
        registers[i] = Register(i);
    }
}
void emitError(string msg)
{
    cout<<msg;
    exit(0);
}


void printPrefix(unsigned int instA, unsigned int instW) {
    std::cout << "0x" << std::hex << std::setfill('0') << std::setw(8)
              << instA << "\t0x" << std::setw(8) << instW;
}

void instDecExe(unsigned int instWord) {
    unsigned int instPC = pc - 4;
    unsigned int opcode = instWord & 0x0000007F;
Instructions inst;
    printPrefix(instPC, instWord);
    std::cout << std::dec; // Switch back to decimal for register identifiers

    // if (opcode == 0x33) { // R Instructions
    //     switch (funct3) {
    //         case 0:
    //             if (funct7 == 32) {
    //                 std::cout << "\tSUB\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
    //             } else {
    //                 std::cout << "\tADD\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
    //             }
    //             break;
    //         default:
    //             std::cout << "\tUnknown R Instruction \n";
    //     }
     if (opcode == 0x13) { // I instructions
        inst.iType(instWord, registers, pc);
    } else {
        std::cout << "\tUnknown Instruction \n";
    }
}


int main(int argc, char *argv[]) {
    initialiseRegs();
    unsigned int instWord = 0;  // Variable to store instruction word
    ifstream iFile;
    if (argc < 1) emitError("use: rvsim <machine_code_file_name> [data_section_file_name]\n");

    iFile.open(argv[1], ios::in | ios::binary | ios::ate);

    if (iFile.is_open())
    {
        int fsize = iFile.tellg();

        iFile.seekg(0, iFile.beg);

        if (!iFile.read((char *) memory, fsize)) emitError("Cannot read from input file\n");

        while (pc<32)  // Stops when PC reaches 32
        {
            instWord = (unsigned char) memory[pc] | (((unsigned char) memory[pc + 1]) << 8) |(((unsigned char) memory[pc + 2]) << 16) |(((unsigned char) memory[pc + 3]) << 24);
            pc += 4;
            instDecExe(instWord);
        }

    }
    else emitError("Cannot access input file\n");

}