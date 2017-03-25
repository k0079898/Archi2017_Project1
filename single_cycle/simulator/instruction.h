#ifndef instruction_h
#define instruction_h

#include <stdio.h>
#include <string.h>
#include "memory.h"
#include "regfile.h"

unsigned int instruction, opcode, rs, rt, rd, shamt, funct, immediate, address;
int writeToRegZero, numberOverflow, overwriteHILO, memAddOverflow, dataMisaligned;

int doInstruction();
int decode();  //Decode the instruction
int rType(char *command);  //Deal with R-Type instruction
int iType(char *command);  //Deal with I-Type instruction
int jType(char *command);  //Deal with J-type instruction
void NumberOverflowDetection(int in1, int in2, int out);
void OverwriteHILODetection();
void MemAddOverflowDetection(int add, int size);
void DataMisalignedDetection(int words, int size);

#endif
