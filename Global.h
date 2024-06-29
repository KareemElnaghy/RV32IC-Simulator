//
// Created by mazin on 29/06/2024.
//

#ifndef GLOBAL_H
#define GLOBAL_H
#include <iostream>
#include "Register.h"
using namespace std;
// Global Variables
unsigned int pc = 0;
unsigned char inline memory[64*(1024)] ;
Register inline registers[32];

#endif //GLOBAL_H
