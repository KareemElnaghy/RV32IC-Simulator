//
// Created by Kareem Elnaghy on 6/29/24.
//

#include "Register.h"
#include <iostream>
#include <string>
using namespace std;

Register::Register()
{
   data= 0;
}
Register::Register(int x)
{
name = "x" + to_string(x);
    switch (x) {
        case 0:  ABI = "zero"; break;
        case 1:  ABI = "ra"; break;
        case 2:  ABI = "sp"; break;
        case 3:  ABI = "gp"; break;
        case 4:  ABI = "tp"; break;
        case 5:  ABI = "t0"; break;
        case 6:  ABI = "t1"; break;
        case 7:  ABI = "t2"; break;
        case 8:  ABI = "s0"; break;
        case 9:  ABI = "s1"; break;
        case 10: ABI = "a0"; break;
        case 11: ABI = "a1"; break;
        case 12: ABI = "a2"; break;
        case 13: ABI = "a3"; break;
        case 14: ABI = "a4"; break;
        case 15: ABI = "a5"; break;
        case 16: ABI = "a6"; break;
        case 17: ABI = "a7"; break;
        case 18: ABI = "s2"; break;
        case 19: ABI = "s3"; break;
        case 20: ABI = "s4"; break;
        case 21: ABI = "s5"; break;
        case 22: ABI = "s6"; break;
        case 23: ABI = "s7"; break;
        case 24: ABI = "s8"; break;
        case 25: ABI = "s9"; break;
        case 26: ABI = "s10"; break;
        case 27: ABI = "s11"; break;
        case 28: ABI = "t3"; break;
        case 29: ABI = "t4"; break;
        case 30: ABI = "t5"; break;
        case 31: ABI = "t6"; break;
        default: ABI = "Invalid";
    }
}
void Register::setData(uint32_t x)
{
    data = x;
}
string Register::getName()
{
    return name;
}
string Register::getABI()
{
    return ABI;
}
uint32_t Register::getData()
{
    return data;
}