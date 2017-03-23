#include "memory.h"

void readBin()  //Read iimage.bin & dimage.bin
{
  unsigned int iimageSize, dimageSize;
  //Open file
  iimage = fopen("iimage.bin","rb");
  dimage = fopen("dimage.bin","rb");
  //Get file size
  fseek(iimage, 0, SEEK_END);
  fseek(dimage, 0, SEEK_END);
  iimageSize = ftell(iimage);
  dimageSize = ftell(dimage);
  //Initial file ptr
  rewind(iimage);
  rewind(dimage);
  //Create Buffer
  iBuffer = (char*) malloc(iimageSize*sizeof(char));
  dBuffer = (char*) malloc(dimageSize*sizeof(char));
  //Read into buffer
  fread(iBuffer,sizeof(iBuffer),1,iimage);
  fread(dBuffer,sizeof(dBuffer),1,dimage);
  //Close file
  fclose(iimage);
  fclose(dimage);
}

void writeMem()  //Read into memory
{
  int m;
  unsigned int temp = 0, line = 0;
  //Handle iMemory
  for(m=0; m<4; m++) temp = (temp<<8) + (unsigned char)iBuffer[m];
  PC = temp;
  printf("PC: 0x%08X\n", PC);
  for(m=4; m<8; m++) line = (line<<8) + (unsigned char)iBuffer[m];
  printf("iimage line: 0x%08X\n", line);
  for(m=8; m<8+line*4; m++){
    iMem[temp] = iBuffer[m];
    if((m+1)%4==0) printf("%c\n", iBuffer[m]);
    else printf("%c", iBuffer[m]);
    temp = temp + 1;
  }
  //Handle dMemory

}
