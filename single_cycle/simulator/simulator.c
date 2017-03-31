#include <stdio.h>
#include "memory.h"
#include "regfile.h"
#include "instruction.h"

FILE *snapshot, *error_dump;
void writeSnapshot(unsigned int cycles);
void writeError(unsigned int cycles);

int main()
{
	//Initial the simlator
	unsigned int cycles, halt, instruction;
	snapshot = fopen("snapshot.rpt", "w");
	error_dump = fopen("error_dump.rpt", "w");
	readBin();
	writeMem();
	cycles = 0;
	halt = 0;
	initREG();
	writeSnapshot(cycles);
	//Start the simulation
	while(halt!=1)
	{
		cycles ++;
		writeToRegZero = 0;
		numberOverflow = 0;
		overwriteHILO = 0;
		memAddOverflow = 0;
		dataMisaligned = 0;
		halt = doInstruction();
		if(halt!=1) writeSnapshot(cycles);
		writeError(cycles);
	}
	fclose(snapshot);
	fclose(error_dump);
	return 0;
}

void writeSnapshot(unsigned int cycles)
{
  int i;
  fprintf(snapshot, "cycle %d\n", cycles);
  //printf("cycle %d\n", cycles);
  if(cycles==0)  //Initial Print
  {
    for(i=0; i<REG_SIZE; i++)
    {
      fprintf(snapshot, "$%02d: ", i);
      fprintf(snapshot, "0x%08X\n", REG[i]);
      //printf("$%02d: ", i);
      //printf("0x%08X\n", REG[i]);
    }
    fprintf(snapshot, "$HI: 0x%08X\n", HI);
    //printf("$HI: 0x%08X\n", HI);
    fprintf(snapshot, "$LO: 0x%08X\n", LO);
    //printf("$LO: 0x%08X\n", LO);
    fprintf(snapshot, "PC: 0x%08X\n\n\n", PC);
    //printf("PC: 0x%08X\n\n\n", PC);
  }else //Simulaing Print
  {
    for(i=0; i<REG_SIZE; i++)
    {
      if(L_REG[i] != REG[i])
      {
        fprintf(snapshot, "$%02d: ", i);
        fprintf(snapshot, "0x%08X\n", REG[i]);
        //printf("$%02d: ", i);
        //printf("0x%08X\n", REG[i]);
        L_REG[i] = REG[i];
      }
    }
    if(L_HI != HI)
    {
      fprintf(snapshot, "$HI: 0x%08X\n", HI);
      //printf("$HI: 0x%08X\n", HI);
      L_HI = HI;
    }
    if(L_LO != LO)
    {
      fprintf(snapshot, "$LO: 0x%08X\n", LO);
      //printf("$LO: 0x%08X\n", LO);
      L_LO = LO;
    }
    if(L_PC != PC)
    {
      fprintf(snapshot, "PC: 0x%08X\n\n\n", PC);
      //printf("PC: 0x%08X\n\n\n", PC);
      L_PC = PC;
    }
  }
}


void writeError(unsigned int cycles)
{
	if(writeToRegZero==1)
	{
		fprintf(error_dump, "In cycle %d: Write $0 Error\n", cycles);
		//printf("In cycle %d: Write $0 Error\n", cycles);
	}
	if(numberOverflow==1)
	{
		fprintf(error_dump, "In cycle %d: Number Overflow\n", cycles);
		//printf("In cycle %d: Number Overflow\n", cycles);
	}
	if(overwriteHILO==1)
	{
		fprintf(error_dump, "In cycle %d: Overwrite HI-LO registers\n", cycles);
		//printf("In cycle %d: Overwrite HI-LO registers\n", cycles);
	}
	if(memAddOverflow==1)
	{
		fprintf(error_dump, "In cycle %d: Address Overflow\n", cycles);
		//printf("In cycle %d: Address Overflow\n", cycles);
	}
	if(dataMisaligned==1)
	{
		fprintf(error_dump, "In cycle %d: Misalignment Error\n", cycles);
		//printf("In cycle %d: Misalignment Error\n", cycles);
	}
}
