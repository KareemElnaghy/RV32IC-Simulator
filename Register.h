//
// Created by Kareem Elnaghy on 6/29/24.
//

#ifndef RV32IC_SIMULATOR_REGISTER_H
#define RV32IC_SIMULATOR_REGISTER_H
#include <iostream>
using namespace std;

class Register
{
    string name;
    string ABI;
    uint32_t data;

public:
    Register();
    Register(int x);
    void setData(uint32_t x);
    string getName();
    string getABI();
    uint32_t getData();

};


#endif //RV32IC_SIMULATOR_REGISTER_H
