#ifndef memory_h
#define memory_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MEM_SIZE 1024
#define REG_SIZE 32

FILE *iimage, *dimage, *snapshot, *error_dump;
unsigned int cycles;
unsigned char *iBuffer, *dBuffer;
unsigned char initPC, initSP;
unsigned int L_REG[REG_SIZE], L_PC, L_HI, L_LO;

//Memory
unsigned char iMem[MEM_SIZE];
unsigned char dMem[MEM_SIZE];
unsigned int REG[REG_SIZE], PC, HI, LO;

void readBin();
void writeMem();
void memDebug(); //Memory debug function
void initPrint();
void writeSnapshot();

#endif
