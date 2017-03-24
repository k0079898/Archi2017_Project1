#include "instruction.h"

doInstruction()
{
  int i;
  int add = PC - initPC;
  for(i=0; i<4; i++) instruction = (instruction<<8) + (unsigned char)iMem[add+i];
  opcode = instruction >> 26;  //31~26
  if(opcode==0x3F) return 1;
  else decode();
  return 0;
}

void decode()  //Decode the instruction
{
  switch (opcode) {
    case 0x00: //R-Type
        funct = instruction << 26 >> 26;  //5~0
        switch (funct) {
          case 0x20: rType("add"); break;
          case 0x21: rType("addu"); break;
          case 0x22: rType("sub"); break;
          case 0x24: rType("and"); break;
          case 0x25: rType("or"); break;
          case 0x26: rType("xor"); break;
          case 0x27: rType("nor"); break;
          case 0x28: rType("nand"); break;
          case 0x2A: rType("slt"); break;
          case 0x00: rType("sll"); break;
          case 0x02: rType("srl"); break;
          case 0x03: rType("sra"); break;
          case 0x08: rType("jr"); break;
          case 0x18: rType("mult"); break;
          case 0x19: rType("multu"); break;
          case 0x10: rType("mfhi"); break;
          case 0x12: rType("mflo"); break;
        }
    //I-Type
    case 0x08: iType("addi"); break;
    case 0x09: iType("addiu"); break;
    case 0x23: iType("lw"); break;
    case 0x21: iType("lh"); break;
    case 0x25: iType("lhu"); break;
    case 0x20: iType("lb"); break;
    case 0x24: iType("lbu"); break;
    case 0x2B: iType("sw"); break;
    case 0x29: iType("sh"); break;
    case 0x28: iType("sb"); break;
    case 0x0F: iType("lui"); break;
    case 0x0C: iType("andi"); break;
    case 0x0D: iType("ori"); break;
    case 0x0E: iType("nori"); break;
    case 0x0A: iType("slti"); break;
    case 0x04: iType("beq"); break;
    case 0x05: iType("bne"); break;
    case 0x07: iType("bgtz"); break;
    //J-Type
    case 0x02: jType("j"); break;
    case 0x03: jType("jal"); break;
  }
}

void rType(char *command)  //Deal with R-Type instruction
{
  rs = instruction << 6 >> 27;
  rt = instruction << 11 >> 27;
  rd = instruction << 16 >> 27;
  shamt = instruction << 21 >> 27;
  printf("%02X %02X %02X %02X %02X %02X\n", opcode, rs, rt, rd, shamt, funct);
}
void iType(char *command)  //Deal with I-Type instruction
{
  rs = instruction << 6 >> 27;
  rt = instruction << 11 >> 27;
  immediate = instruction << 16 >> 16;
  printf("%02X %02X %02X %04X\n", opcode, rs, rt, immediate);
}
void jType(char *command)  //Deal with J-type instruction
{
  address = instruction << 6 >> 6;
  printf("%02X %07X\n", opcode, address);
}
