#ifndef regfile_h
#define regfile_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "memory.h"

#define REG_SIZE 32

unsigned char initPC, initSP;
unsigned int L_REG[REG_SIZE], L_PC, L_HI, L_LO;

//Register
unsigned int REG[REG_SIZE], PC, HI, LO;

void initREG(); //Initial the register

#endif
