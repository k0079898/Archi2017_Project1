#include "instruction.h"

int doInstruction()
{
  int i, isError = 0;
  int add = PC - initPC;
  for(i=0; i<4; i++) instruction = (instruction<<8) + (unsigned char)iMem[add+i];
  opcode = instruction >> 26;  //31~26
  printf("%08X ", instruction);
  if(instruction==0x00000000)
  {
    PC = PC + 4;
  }else if(opcode==0x3F) return 1;
  else return decode();
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
    default: printf("illegal instruction found at 0x%08X\n", PC); return 1;
  }
}

int rType(char *command)  //Deal with R-Type instruction
{
  rs = instruction << 6 >> 27;
  rt = instruction << 11 >> 27;
  rd = instruction << 16 >> 27;
  shamt = instruction << 21 >> 27;
  printf("R-Type\n");
  if(strcmp(command, "add")==0)
  {
    printf("0x%08X: add $%u, $%u, $%u\n", PC, rd, rs, rt);
    if(rd==0) writeToRegZero = 1;
    else{
      t_rs = (int32_t)REG[rs];
      t_rt = (int32_t)REG[rt];
      REG[rd] = (int32_t)REG[rs] + (int32_t)REG[rt];
      printf("%d %d %d\n", t_rs, t_rt, (uint32_t)REG[rd]);
      NumberOverflowDetection("add", REG[rs], REG[rt], REG[rd]);
    }
  }else if(strcmp(command, "addu")==0)
  {
    printf("0x%08X: addu $%u, $%u, $%u\n", PC, rd, rs, rt);
    if(rd==0) writeToRegZero = 1;
    else REG[rd] = REG[rs] + REG[rt];
  }else if(strcmp(command, "sub")==0)
  {
    printf("0x%08X: sub $%u, $%u, $%u\n", PC, rd, rs, rt);
    if(rd==0) writeToRegZero = 1;
    else{
      REG[rd] = (int32_t)REG[rs] - (int32_t)REG[rt];
      NumberOverflowDetection("sub", REG[rs], REG[rt], REG[rd]);
    }
  }else if(strcmp(command, "and")==0)
  {
    printf("0x%08X: and $%u, $%u, $%u\n", PC, rd, rs, rt);
    if(rd==0) writeToRegZero = 1;
    else REG[rd] = REG[rs] & REG[rt];
  }else if(strcmp(command, "or")==0)
  {
    printf("0x%08X: or $%u, $%u, $%u\n", PC, rd, rs, rt);
    if(rd==0) writeToRegZero = 1;
    else REG[rd] = REG[rs] | REG[rt];
  }else if(strcmp(command, "xor")==0)
  {
    printf("0x%08X: xor $%u, $%u, $%u\n", PC, rd, rs, rt);
    if(rd==0) writeToRegZero = 1;
    else REG[rd] = REG[rs] ^ REG[rt];
  }else if(strcmp(command, "nor")==0)
  {
    printf("0x%08X: nor $%u, $%u, $%u\n", PC, rd, rs, rt);
    if(rd==0) writeToRegZero = 1;
    else REG[rd] = ~(REG[rs] | REG[rt]);
  }else if(strcmp(command, "nand")==0)
  {
    printf("0x%08X: nand $%u, $%u, $%u\n", PC, rd, rs, rt);
    if(rd==0) writeToRegZero = 1;
    else REG[rd] = ~(REG[rs] & REG[rt]);
  }else if(strcmp(command, "slt")==0)
  {
    printf("0x%08X: slt $%u, $%u, $%u\n", PC, rd, rs, rt);
    if(rd==0) writeToRegZero = 1;
    else REG[rd] = ((int32_t)REG[rs] < (int32_t)REG[rt]) ? 1:0;
  }else if(strcmp(command, "sll")==0)
  {
    printf("0x%08X: sll $%u, $%u, $%u\n", PC, rd, rt, shamt);
    if(rd==0) writeToRegZero = 1;
    else REG[rd] = REG[rt] << shamt;
  }else if(strcmp(command, "srl")==0)
  {
    printf("0x%08X: srl $%u, $%u, $%u\n", PC, rd, rt, shamt);
    if(rd==0) writeToRegZero = 1;
    else REG[rd] = REG[rt] >> shamt;
  }else if(strcmp(command, "sra")==0)
  {
    printf("0x%08X: sra $%u, $%u, $%u\n", PC, rd, rt, shamt);
    if(rd==0) writeToRegZero = 1;
    else REG[rd] = (int32_t)REG[rt] >> shamt;
  }else if(strcmp(command, "jr")==0)
  {
    printf("0x%08X: jr $%u\n", PC, rs);
    PC = REG[rs];
    return 0;  //Witout PC = PC + 4;
  }else if(strcmp(command, "mult")==0)
  {
    if(need_mfHILO==1) overwriteHILO = 1;
    printf("0x%08X: mult $%u, $%u\n", PC, rs, rt);
    int64_t result = (int32_t)REG[rs] * (int32_t)REG[rt];
    HI = result >> 32;
    LO = result << 32 >> 32;
    need_mfHILO = 1;
  }else if(strcmp(command, "multu")==0)
  {
    if(need_mfHILO==1) overwriteHILO = 1;
    printf("0x%08X: multu $%u, $%u\n", PC, rs, rt);
    int64_t result = (uint64_t)REG[rs] * (uint64_t)REG[rt];
    HI = result >> 32;
    LO = result << 32 >> 32;
    need_mfHILO = 1;
  }else if(strcmp(command, "mfhi")==0)
  {
    printf("0x%08X: mfhi $%u\n", PC, rd);
    if(rd==0) writeToRegZero = 1;
    else REG[rd] = HI;
    need_mfHILO = 0;
  }else if(strcmp(command, "mflo")==0)
  {
    printf("0x%08X: mflo $%u\n", PC, rd);
    if(rd==0) writeToRegZero = 1;
    else REG[rd] = LO;
    need_mfHILO = 0;
  }else return 1;
  PC = PC + 4;
  return 0;
}
int iType(char *command)  //Deal with I-Type instruction
{
  rs = instruction << 6 >> 27;
  rt = instruction << 11 >> 27;
  printf("I-Type\n");
  immediate = (short int)instruction << 16 >> 16;  //Immediate is not unsigned!!!!
  if(strcmp(command, "addi")==0)
  {
    printf("0x%08X: addi $%u, $%u, %d\n", PC, rt, rs, immediate);
    if(rt==0) writeToRegZero = 1;
    else
    {
      REG[rt] = (int32_t)(REG[rs] + immediate);
      NumberOverflowDetection("add", REG[rs], immediate, REG[rt]);
    }
  }else if(strcmp(command, "addiu")==0)
  {
    printf("0x%08X: addiu $%u, $%u, %d\n", PC, rs, rt, immediate);
    if(rt==0) writeToRegZero = 1;
    else REG[rt] = REG[rs] + immediate;
  }else if(strcmp(command, "lw")==0)
  {
    printf("0x%08X: lw $%u, %04X($%u)\n", PC, rt, immediate, rs);
    unsigned int addr = REG[rs] + immediate;
    if(rt==0) writeToRegZero = 1;
    NumberOverflowDetection("add", REG[rs], immediate, addr);
    MemAddOverflowDetection(addr, 3);
    DataMisalignedDetection(addr, 4);
    if(memAddOverflow==1 || dataMisaligned==1) return 1;
    if(writeToRegZero!=1) REG[rt] = (int32_t)(dMem[addr] << 24 | dMem[addr+1] << 16 | dMem[addr+2] << 8 | dMem[addr+3]);
    NumberOverflowDetection("add", REG[rs], immediate, addr);
  }else if(strcmp(command, "lh")==0)
  {
    printf("0x%08X: lh $%u, %04X($%u)\n", PC, rt, immediate, rs);
    unsigned int addr = REG[rs] + immediate;
    if(rt==0) writeToRegZero = 1;
    NumberOverflowDetection("add", REG[rs], immediate, addr);
    MemAddOverflowDetection(addr, 1);
    DataMisalignedDetection(addr, 2);
    if(memAddOverflow==1 || dataMisaligned==1) return 1;
    if(writeToRegZero!=1) REG[rt] = (int16_t)(dMem[addr] << 8 | dMem[addr+1]);
  }else if(strcmp(command, "lhu")==0)
  {
    printf("0x%08X: lhu $%u, %04X($%u)\n", PC, rt, immediate, rs);
    unsigned int addr = REG[rs] + immediate;
    if(rt==0) writeToRegZero = 1;
    NumberOverflowDetection("add", REG[rs], immediate, addr);
    MemAddOverflowDetection(addr, 1);
    DataMisalignedDetection(addr, 2);
    if(memAddOverflow==1 || dataMisaligned==1) return 1;
    if(writeToRegZero!=1) REG[rt] = (uint16_t)(dMem[addr] << 8 | dMem[addr+1]);
  }else if(strcmp(command, "lb")==0)
  {
    printf("0x%08X: lb $%u, %04X($%u)\n", PC, rt, immediate, rs);
    unsigned int addr = REG[rs] + immediate;
    if(rt==0) writeToRegZero = 1;
    NumberOverflowDetection("add", REG[rs], immediate, addr);
    MemAddOverflowDetection(addr, 0);
    DataMisalignedDetection(addr, 1);
    if(memAddOverflow==1 || dataMisaligned==1) return 1;
    if(writeToRegZero!=1) REG[rt] = (int8_t)dMem[addr];
  }else if(strcmp(command, "lbu")==0)
  {
    printf("0x%08X: lbu $%u, %04X($%u)\n", PC, rt, immediate, rs);
    unsigned int addr = REG[rs] + immediate;
    if(rt==0) writeToRegZero = 1;
    NumberOverflowDetection("add", REG[rs], immediate, addr);
    MemAddOverflowDetection(addr, 0);
    DataMisalignedDetection(addr, 1);
    if(memAddOverflow==1 || dataMisaligned==1) return 1;
    if(writeToRegZero!=1) REG[rt] = (uint8_t)dMem[addr];
    NumberOverflowDetection("add", REG[rs], immediate, addr);
  }else if(strcmp(command, "sw")==0)
  {
    printf("0x%08X: sw $%u, %04X($%u)\n", PC, rt, immediate, rs);
    unsigned int addr = REG[rs] + immediate;
    NumberOverflowDetection("add", REG[rs], immediate, addr);
    MemAddOverflowDetection(addr, 3);
    DataMisalignedDetection(addr, 4);
    if(memAddOverflow==1 || dataMisaligned==1) return 1;
    dMem[addr] = REG[rt] >> 24;
    dMem[addr+1] = REG[rt] >> 16;
    dMem[addr+2] = REG[rt] >> 8;
    dMem[addr+3] = REG[rt];
  }else if(strcmp(command, "sh")==0)
  {
    printf("0x%08X: sh $%u, %04X($%u)\n", PC, rt, immediate, rs);
    unsigned int addr = REG[rs] + immediate;
    NumberOverflowDetection("add", REG[rs], immediate, addr);
    MemAddOverflowDetection(addr, 1);
    DataMisalignedDetection(addr, 2);
    if(memAddOverflow==1 || dataMisaligned==1) return 1;
    dMem[addr] = (REG[rt] >> 8) & 0xFF;
    dMem[addr+1] = REG[rt] & 0xFF;
  }else if(strcmp(command, "sb")==0)
  {
    printf("0x%08X: sb $%u, %04X($%u)\n", PC, rt, immediate, rs);
    unsigned int addr = REG[rs] + immediate;
    NumberOverflowDetection("add", REG[rs], immediate, addr);
    MemAddOverflowDetection(addr, 0);
    DataMisalignedDetection(addr, 1);
    if(memAddOverflow==1 || dataMisaligned==1) return 1;
    dMem[addr] = REG[rt] & 0xFF;
  }else if(strcmp(command, "lui")==0)
  {
    printf("0x%08X: lui $%u, $%u, %04X\n", PC, rt, immediate);
    if(rt==0) writeToRegZero = 1;
    else REG[rt] = immediate << 16;
  }else if(strcmp(command, "andi")==0)
  {
    printf("0x%08X: andi $%u, $%u, %04X\n", PC, rt, rs, immediate);
    if(rt==0) writeToRegZero = 1;
    else REG[rt] = REG[rs] & (uint16_t)immediate;
  }else if(strcmp(command, "ori")==0)
  {
    printf("0x%08X: ori $%u, $%u, %04X\n", PC, rt, rs, immediate);
    if(rt==0) writeToRegZero = 1;
    else REG[rt] = REG[rs] | (uint16_t)immediate;
  }else if(strcmp(command, "nori")==0)
  {
    printf("0x%08X: nori $%u, $%u, %04X\n", PC, rt, rs, immediate);
    if(rt==0) writeToRegZero = 1;
    else REG[rt] = ~(REG[rs] | (uint16_t)immediate);
  }else if(strcmp(command, "slti")==0)
  {
    printf("0x%08X: slti $%u, $%u, %04X\n", PC, rt, rs, immediate);
    if(rt==0) writeToRegZero = 1;
    else REG[rt] = ((int32_t)REG[rs] < (int32_t)immediate) ? 1:0;
  }else if(strcmp(command, "beq")==0)
  {
    printf("0x%08X: beq $%u, $%u, %04X\n", PC, rs, rt, immediate);
    if(REG[rs]==REG[rt])
    {
      PC = (PC + 4) + (4 * immediate);
      return 0;    //Witout PC = PC + 4;
    }
  }else if(strcmp(command, "bne")==0)
  {
    printf("0x%08X: bne $%u, $%u, %04X\n", PC, rs, rt, immediate);
    if(REG[rs]!=REG[rt])
    {
      PC = (PC + 4) + (4 * immediate);
      return 0;    //Witout PC = PC + 4;
    }
  }else if(strcmp(command, "bgtz")==0)
  {
    printf("0x%08X: bgtz $%u, %04X\n", PC, rs, immediate);
    if((int32_t)REG[rs]>0)
    {
      PC = (PC + 4) + (4 * immediate);
      return 0;    //Witout PC = PC + 4;
    }
  }else return 1;
  PC = PC + 4;
  return 0;
}

int jType(char *command)  //Deal with J-type instruction
{
  address = instruction << 6 >> 6;
  printf("J-Type\n");
  if(strcmp(command, "j")==0)
  {
    printf("0x%08X: j %08X\n", PC, address);
    PC = ((PC+4) >> 28 << 28) | (4*address);
  }else if(strcmp(command, "jal")==0)
  {
    printf("0x%08X: jal %08X\n", PC, address);
    REG[31] = PC + 4;
    PC = ((PC+4) >> 28 << 28) | (4*address);
  }else return 1;
}

void NumberOverflowDetection(char *command, int in1, int in2, int out)
{
  if(strcmp(command, "add")==0)
  {
    if((in1>=0 && in2>=0 && out<0) || (in1<0 && in2<0 && out>=0)) numberOverflow = 1;
  }else if(strcmp(command, "sub")==0)
  {
    if((in1>=0 && in2<0 && out<0) || (in1<0 && in2>=0 && out>=0)) numberOverflow = 1;
  }
}

void MemAddOverflowDetection(int addr, int size)
{
  if(addr >= MEM_SIZE || addr+size >= MEM_SIZE) memAddOverflow = 1;
}

void DataMisalignedDetection(int words, int size)
{
  if(words%size!=0) dataMisaligned = 1;
}
