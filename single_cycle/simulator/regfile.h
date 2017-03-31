#ifndef regfile_h
#define regfile_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "memory.h"

#define REG_SIZE 32

unsigned int initPC;  //Save the initial PC address
unsigned int L_REG[REG_SIZE], L_PC, L_HI, L_LO;  //Save the last changed value

//Register
unsigned int REG[REG_SIZE], PC, HI, LO;

void initREG();  //Initial all the register

#endif
