//
// Created by Kareem Elnaghy on 6/29/24.
//

#ifndef RV32IC_SIMULATOR_INSTRUCTIONS_H
#define RV32IC_SIMULATOR_INSTRUCTIONS_H
#include "Register.h"
class Instructions
{
public:
    void rType(unsigned int instWord);
    void iType(unsigned int instWord, Register registers[32], unsigned int pc);
    void sType(unsigned int instWord);
    void bType(unsigned int instWord);
    void uType(unsigned int instWord, Register registers[32], unsigned int pc);
    void jType(unsigned int instWord);
    void Load(unsigned int instWord, Register registers[32], unsigned int pc);


};

#endif //RV32IC_SIMULATOR_INSTRUCTIONS_H
