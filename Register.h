//
// Created by Kareem Elnaghy on 6/29/24.
//

#ifndef RV32IC_SIMULATOR_REGISTER_H
#define RV32IC_SIMULATOR_REGISTER_H
#include <string>
using namespace std;

class Register
{
    string name;
    string ABI;
    unsigned int data;

public:
    Register();
    Register(int x);
    void setDataU(unsigned int x);
    void setData(int x);
    string getName();
    string getABI();
    unsigned int getDataU();
    int getData();
    void  printRegData();
};

#endif //RV32IC_SIMULATOR_REGISTER_H
