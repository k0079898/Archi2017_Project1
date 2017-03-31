#include "memory.h"

void readBin()  //Read iimage.bin & dimage.bin into buffer
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


void writeMem()  //Write data into memory & free the buffer
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
  for(m=4; m<8; m++) line = (line<<8) + (unsigned char)dBuffer[m];
  for(m=8; m<8+line*4; m++) dMem[m-8] = dBuffer[m];
  //Free the buffer
  free(iBuffer);
  free(dBuffer);
}

void memDebug() //Memory debug function
{
  int i;
  printf("iMemmory:\n");
  for(i=0; i<MEM_SIZE; i++){
    if((i+1)%4==0) printf("0x%04X: %02X\n", i, iMem[i]);
    else printf("0x%04X: %02X ", i, iMem[i]);
  }
  printf("dMemmory:\n");
  for(i=0; i<MEM_SIZE; i++){
    if((i+1)%4==0) printf("0x%04X: %02X\n", i, dMem[i]);
    else printf("0x%04X: %02X ", i, dMem[i]);
  }
}
