#include "regfile.h"

void initREG() //Initial the register
{
  int i;
  for(i=0; i<REG_SIZE; i++) L_REG[i] = REG[i];
  L_HI = HI;
  L_LO = LO;
  L_PC = PC;
}
