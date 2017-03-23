#ifndef memory_h
#define memory_h

#include <stdio.h>
#include <string.h>

#define SIZE 1024

FILE *iimage,*dimage;
char *iBuffer, *dBuffer;

//Memory
unsigned char iMem[SIZE];
unsigned char dMem[SIZE];
unsigned int PC, HI, LO;

void readBin();
void writeMem();

#endif
