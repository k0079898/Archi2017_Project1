#include <stdio.h>
#include "memory.h"
#include "regfile.h"

FILE *snapshot, *error_dump;
void writeSnapshot(int cycles);

int main()
{
	unsigned int cycles;
	snapshot = fopen("snapshot.rpt", "w");
	error_dump = fopen("error_dump.rpt", "w");
	readBin();
	writeMem();
	cycles = 0;
	initREG();
	writeSnapshot(cycles);
	//Start the simulation
	return 0;
}

void writeSnapshot(int cycles)
{
  int i;
  fprintf(snapshot, "cycle %d\n", cycles);
  printf("cycle %d\n", cycles);
  if(cycles==0)  //Initial Print
  {
    for(i=0; i<REG_SIZE; i++)
    {
      fprintf(snapshot, "$%02d: ", i);
      fprintf(snapshot, "0x%08X\n", REG[i]);
      printf("$%02d: ", i);
      printf("0x%08X\n", REG[i]);
    }
    fprintf(snapshot, "$HI: 0x%08X\n", HI);
    printf("$HI: 0x%08X\n", HI);
    fprintf(snapshot, "$LO: 0x%08X\n", LO);
    printf("$LO: 0x%08X\n", LO);
    fprintf(snapshot, "PC: 0x%08X\n\n\n", PC);
    printf("PC: 0x%08X\n\n\n", PC);
  }else //Simulaing Print
  {
    for(i=0; i<REG_SIZE; i++)
    {
      if(L_REG[i] != REG[i])
      {
        fprintf(snapshot, "$%02d: ", i);
        fprintf(snapshot, "0x%08X\n", REG[i]);
        printf("$%02d: ", i);
        printf("0x%08X\n", REG[i]);
        L_REG[i] = REG[i];
      }
    }
    if(L_HI != HI)
    {
      fprintf(snapshot, "$HI: 0x%08X\n", HI);
      printf("$HI: 0x%08X\n", HI);
      L_HI = HI;
    }
    if(L_LO != LO)
    {
      fprintf(snapshot, "$LO: 0x%08X\n", LO);
      printf("$LO: 0x%08X\n", LO);
      L_LO = LO;
    }
    if(L_PC != PC)
    {
      fprintf(snapshot, "PC: 0x%08X\n", PC);
      printf("PC: 0x%08X\n", PC);
      L_PC = PC;
    }
  }
}
