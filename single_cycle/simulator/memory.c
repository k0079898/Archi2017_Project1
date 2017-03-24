#include "memory.h"

void readBin()  //Read iimage.bin & dimage.bin
{
  unsigned int iimageSize = 0, dimageSize = 0;
  //Open file
  iimage = fopen("iimage.bin","rb");
  dimage = fopen("dimage.bin","rb");
  //Get file size
  fseek(iimage, 0, SEEK_END);
  fseek(dimage, 0, SEEK_END);
  iimageSize = (unsigned int)ftell(iimage);
  dimageSize = (unsigned int)ftell(dimage);
  //Initial file ptr
  rewind(iimage);
  rewind(dimage);
  //Create Buffer
  iBuffer = calloc(iimageSize, sizeof(unsigned char));
  dBuffer = calloc(dimageSize, sizeof(unsigned char));
  //Read into buffer
  fread(iBuffer,iimageSize,1,iimage);
  fread(dBuffer,dimageSize,1,dimage);
  //Close file
  fclose(iimage);
  fclose(dimage);
}

void writeMem()  //Read into memory
{
  int m;
  unsigned int temp = 0, line = 0;
  //Handle with iMemory
  for(m=0; m<4; m++) temp = (temp<<8) + (unsigned char)iBuffer[m];
  PC = temp;
  initPC = temp;
  for(m=4; m<8; m++) line = (line<<8) + (unsigned char)iBuffer[m];
  for(m=8; m<8+line*4; m++) iMem[m-8] = iBuffer[m];
  //Handle with dMemory
  temp = 0;
  line = 0;
  for(m=0; m<4; m++) temp = (temp<<8) + (unsigned char)dBuffer[m];
  REG[29] = temp;
  initSP = temp;
  for(m=4; m<8; m++) line = (line<<8) + (unsigned char)dBuffer[m];
  for(m=8; m<8+line*4; m++) dMem[m-8] = dBuffer[m];
  free(iBuffer);
  free(dBuffer);
}

void memDebug()
{
  int i;
  printf("iMemmory:\n");
  for(i=0; i<MEM_SIZE; i++){
    if((i+1)%4==0) printf("%02X\n", iMem[i]);
    else printf("%02X", iMem[i]);
  }
  printf("dMemmory:\n");
  for(i=0; i<MEM_SIZE; i++){
    if((i+1)%4==0) printf("%02X\n", dMem[i]);
    else printf("%02X", dMem[i]);
  }
}

void initPrint()
{
  snapshot = fopen("snapshot.rpt", "w");
  error_dump = fopen("error_dump.rpt", "w");
  int i;
  cycles = 0;
  for(i=0; i<REG_SIZE; i++) L_REG[i] = REG[i];
  L_HI = HI;
  L_LO = LO;
  L_PC = PC;
  writeSnapshot();
}

void writeSnapshot()
{
  int i;
  fprintf(snapshot, "cycle %d\n", cycles);
  printf("cycle %d\n", cycles);
  if(cycles==0)  //initPrint
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
