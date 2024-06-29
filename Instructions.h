//
// Created by Kareem Elnaghy on 6/29/24.
//

#ifndef RV32IC_SIMULATOR_INSTRUCTIONS_H
#define RV32IC_SIMULATOR_INSTRUCTIONS_H

class Instructions
{
public:
    void rType(unsigned int instWord);
    void iType(unsigned int instWord);
    void sType(unsigned int instWord);
    void bType(unsigned int instWord);
    void uType(unsigned int instWord);
    void jType(unsigned int instWord);

};

#endif //RV32IC_SIMULATOR_INSTRUCTIONS_H
