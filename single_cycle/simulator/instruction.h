#ifndef instruction_h
#define instruction_h

#include <stdio.h>
#include <string.h>
#include "memory.h"
#include "regfile.h"

unsigned int instruction, opcode, rs, rt, rd, shamt, funct, immediate, address;

int doInstruction();
void decode();  //Decode the instruction
void rType(char *command);  //Deal with R-Type instruction
void iType(char *command);  //Deal with I-Type instruction
void jType(char *command);  //Deal with J-type instruction

#endif
