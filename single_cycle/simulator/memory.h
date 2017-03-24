#ifndef memory_h
#define memory_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "regfile.h"

#define MEM_SIZE 1024

FILE *iimage, *dimage;
unsigned char *iBuffer, *dBuffer;

//Memory
unsigned char iMem[MEM_SIZE];
unsigned char dMem[MEM_SIZE];

void readBin();  //Read iimage.bin & dimage.bin
void writeMem();  //Read into memory
void memDebug(); //Memory debug function

#endif
