#include "instruction.h"

int doInstruction()
{
  int i, isError = 0;
  int add = PC - initPC;
  for(i=0; i<4; i++) instruction = (instruction<<8) + (unsigned char)iMem[add+i];
  opcode = instruction >> 26;  //31~26
  if(opcode==0x3F) return 1;
  else
  {
    isError = decode();
  }
  return isError;
}

int decode()  //Decode the instruction
{
  switch (opcode) {
    case 0x00: //R-Type
        funct = instruction << 26 >> 26;  //5~0
        switch (funct) {
          case 0x20: return rType("add");
          case 0x21: return rType("addu");
          case 0x22: return rType("sub");
          case 0x24: return rType("and");
          case 0x25: return rType("or");
          case 0x26: return rType("xor");
          case 0x27: return rType("nor");
          case 0x28: return rType("nand");
          case 0x2A: return rType("slt");
          case 0x00: return rType("sll");
          case 0x02: return rType("srl");
          case 0x03: return rType("sra");
          case 0x08: return rType("jr");
          case 0x18: return rType("mult");
          case 0x19: return rType("multu");
          case 0x10: return rType("mfhi");
          case 0x12: return rType("mflo");
        }
    //I-Type
    case 0x08: return iType("addi");
    case 0x09: return iType("addiu");
    case 0x23: return iType("lw");
    case 0x21: return iType("lh");
    case 0x25: return iType("lhu");
    case 0x20: return iType("lb");
    case 0x24: return iType("lbu");
    case 0x2B: return iType("sw");
    case 0x29: return iType("sh");
    case 0x28: return iType("sb");
    case 0x0F: return iType("lui");
    case 0x0C: return iType("andi");
    case 0x0D: return iType("ori");
    case 0x0E: return iType("nori");
    case 0x0A: return iType("slti");
    case 0x04: return iType("beq");
    case 0x05: return iType("bne");
    case 0x07: return iType("bgtz");
    //J-Type
    case 0x02: return jType("j");
    case 0x03: return jType("jal");
    case 0x3F: return 1;
    default: return 1;
  }
}

int rType(char *command)  //Deal with R-Type instruction
{
  rs = instruction << 6 >> 27;
  rt = instruction << 11 >> 27;
  rd = instruction << 16 >> 27;
  shamt = instruction << 21 >> 27;
  if(strcmp(command, "add")==0)
  {
    printf("%#08x: add $%u, $%u,$%u\n", PC, rd, rs, rt);
    if(rd==0) writeToRegZero = 1;
    else{
      REG[rd] = REG[rs] + REG[rt];
      NumberOverflowDetection(REG[rs], REG[rt], REG[rd]);
    }
  }else if(strcmp(command, "addu")==0)
  {

  }else if(strcmp(command, "sub")==0)
  {

  }else if(strcmp(command, "and")==0)
  {

  }else if(strcmp(command, "or")==0)
  {

  }else if(strcmp(command, "xor")==0)
  {

  }else if(strcmp(command, "nor")==0)
  {

  }else if(strcmp(command, "nand")==0)
  {

  }else if(strcmp(command, "slt")==0)
  {

  }else if(strcmp(command, "sll")==0)
  {

  }else if(strcmp(command, "srl")==0)
  {

  }else if(strcmp(command, "sra")==0)
  {

  }else if(strcmp(command, "jr")==0)
  {
    printf("%#08x: jr $%u\n", PC, rs);
    PC = REG[rs];
    return 0 ;
  }else if(strcmp(command, "mult")==0)
  {

  }else if(strcmp(command, "multu")==0)
  {

  }else if(strcmp(command, "mfhi")==0)
  {

  }else if(strcmp(command, "mflo")==0)
  {

  }else return 1;
  PC = PC + 4;
  return 0;
}
int iType(char *command)  //Deal with I-Type instruction
{
  rs = instruction << 6 >> 27;
  rt = instruction << 11 >> 27;
  immediate = instruction << 16 >> 16;
  if(strcmp(command, "addi")==0)
  {
    printf("%#08X: addi $%u, $%u, %d\n", PC, rs, rt, (short int)immediate);
    if(rt==0) writeToRegZero = 1;
    else
    {
      REG[rt] = REG[rs] + (short int)immediate;
      NumberOverflowDetection(REG[rs], (short int)immediate, REG[rt]);
    }
  }else if(strcmp(command, "addiu")==0)
  {

  }else if(strcmp(command, "lw")==0)
  {
    printf("0x%08x: lw $%u, %04X($%u)\n", PC, rt, immediate, rs);
    unsigned int add = REG[rs] + immediate;
    MemAddOverflowDetection(add, 3);
    DataMisalignedDetection(immediate, 4);
    if(memAddOverflow==1 || dataMisaligned==1) return 1;
    REG[rt] = dMem[add] << 24 | dMem[add+1] << 16 | dMem[add+2] << 8 | dMem[add+3];
    NumberOverflowDetection(REG[rs], (short int)immediate, add);
  }else if(strcmp(command, "lh")==0)
  {

  }else if(strcmp(command, "lhu")==0)
  {

  }else if(strcmp(command, "lb")==0)
  {

  }else if(strcmp(command, "lbu")==0)
  {

  }else if(strcmp(command, "sw")==0)
  {
    printf("0x%08x: sw $%u, %04X($%u)\n", PC, rt, immediate, rs);
    unsigned int add = REG[rs] + immediate;
    MemAddOverflowDetection(add, 3);
    DataMisalignedDetection(immediate, 4);
    if(memAddOverflow==1 || dataMisaligned==1) return 1;
    dMem[add] = REG[rt] >> 24;
    dMem[add+1] = REG[rt] >> 16;
    dMem[add+2] = REG[rt] >> 8;
    dMem[add+3] = REG[rt];
    NumberOverflowDetection(REG[rs], (short int)immediate, add);
  }else if(strcmp(command, "sh")==0)

  {
  }else if(strcmp(command, "sb")==0)
  {

  }else if(strcmp(command, "lui")==0)
  {

  }else if(strcmp(command, "andi")==0)
  {

  }else if(strcmp(command, "ori")==0)
  {

  }else if(strcmp(command, "nori")==0)
  {

  }else if(strcmp(command, "slti")==0)
  {

  }else if(strcmp(command, "beq")==0)
  {

  }else if(strcmp(command, "bne")==0)
  {

  }else if(strcmp(command, "bgtz")==0)
  {

  }else return 1;
  PC = PC + 4;
  return 0;
}

int jType(char *command)  //Deal with J-type instruction
{
  address = instruction << 6 >> 6;
  printf("%02X %07X\n", opcode, address);
  if(strcmp(command, "j")==0)
  {
    printf("0x%08x: j %08X\n", PC, address);
    PC = ((PC+4) >> 28 << 28) | address*4;
  }else if(strcmp(command, "jal")==0)
  {
    printf("0x%08x: jal %08X\n", PC, address);
    REG[31] = PC + 4;
    PC = ((PC+4) >> 28 << 28) | address*4;
  }else return 1;
}

void NumberOverflowDetection(int in1, int in2, int out)
{
  if(in1 > 0 && in2 > 0 && out < 0) numberOverflow = 1;
  else if(in1 < 0 && in2 < 0 && out > 0) numberOverflow = 1;
}

void OverwriteHILODetection()
{

}
void MemAddOverflowDetection(int add, int size)
{
  if(add >= MEM_SIZE || add+size >= MEM_SIZE) memAddOverflow = 1;
}
void DataMisalignedDetection(int words, int size)
{
  if(words%size!=0) dataMisaligned = 1;
}
