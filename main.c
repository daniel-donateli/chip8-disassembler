#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void disassembleOp(uint8_t *buffer, int pc) {
  uint8_t *code = &buffer[pc];
  uint8_t firstnib = (code[0] >> 4);

  printf("%04X %02X %02X ", pc, code[0], code[1]);
  switch(firstnib) {
    case 0x00:
      {
        switch(firstnib >> 4) {
          case 0xe0:
            printf("%-10s ", "CLS");
            break;
          case 0xee:
            printf("%-10s ", "RTS");
            break;
          default:
            printf("UNKNOWN 0.");
            break;
        }
      }
      break;    
    case 0x01:
      {
        printf("%-10s $%03X", "JUMP", ((code[0] & 0xf) << 8) | code[1]);
      }
      break;    
    case 0x02:
      {
        printf("%-10s $%03X", "CALL", ((code[0] & 0xf) << 8) | code[1]);
      }
      break;    
    case 0x03:
      {
        uint8_t reg = code[0] & 0x0f;
        printf("%-10s V%01X, #$%02X", "SKIP.EQ", reg, code[1]);
      }
      break;    
    case 0x04:
      {
        uint8_t reg = code[0] & 0x0f;
        printf("%-10s V%01X, #$%02X", "SKIP.NE", reg, code[1]);
      }
      break;    
    case 0x05:
      {
        uint8_t reg1 = code[0] & 0x0f;
        uint8_t reg2 = code[1] >> 4;
        printf("%-10s V%01X, V%01X", "SKIP.EQ", reg1, reg2);
      }
      break;    
    case 0x06:    
    {    
      uint8_t reg = code[0] & 0x0f;    
      printf("%-10s V%01X, #$%02X", "MVI", reg, code[1]);    
    }    
    break;    
    case 0x07:
      {
        uint8_t reg = code[0] & 0x0f;    
        printf("%-10s V%01X, %02X", "ADD", reg, code[1]);;
      }
      break;    
    case 0x08:
      {
        uint8_t reg1 = code[0] & 0x0f;
        uint8_t reg2 = code[1] >> 4;
        uint8_t op = code[1] & 0xf;
        switch(op) {
          case 0x00:
            {
              printf("%-10s V%01X, V%01X", "MOV", reg1, reg2);
            }
            break;
          case 0x01:
            {
              printf("%-10s V%01X, V%01X", "OR", reg1, reg2);
            }
            break;
          case 0x02:
            {
              printf("%-10s V%01X, V%01X", "AND", reg1, reg2);
            }
            break;
          case 0x03:
            {
              printf("%-10s V%01X, V%01X", "XOR", reg1, reg2);
            }
            break;
          case 0x04:
            {
              printf("%-10s V%01X, V%01X", "ADD.", reg1, reg2);
            }
            break;
          case 0x05:
            {
              printf("%-10s V%01X, V%01X", "SUB.", reg1, reg2);
            }
            break;
          case 0x06:
            {
              printf("%-10s V%01X", "SHR.", reg1);
            }
            break;
          case 0x07:
            {
              printf("%-10s V%01X, V%01X", "SUBB.", reg1, reg2);
            }
            break;
          case 0x0e:
            {
              printf("%-10s V%01X", "SHL.", reg1);
            }
            break;
          default:
            printf("UNKNOWN 8");
            break;
        }
      }
      break;    
    case 0x09:
      {
        uint8_t reg1 = code[0] & 0x0f;
        uint8_t reg2 = code[1] >> 4;
        printf("%-10s V%01X, V%01X", "SKIP.NE", reg1, reg2);
      }
      break;    
    case 0x0a:    
    {    
      uint8_t addresshi = code[0] & 0x0f;    
      printf("%-10s I, #$%01X%02X", "MVI", addresshi, code[1]);    
    }    
    break;    
    case 0x0b:
      {
        printf("%-10s $%03X(V0)", "JUMP", ((code[0] & 0xf) << 8) | code[1]);
      }
      break;    
    case 0x0c:
      {
        uint8_t reg = code[0] & 0x0f;    
        printf("%-10s V%01X, %02X", "RAND", reg, code[1]);;
      }
      break;    
    case 0x0d:
      {
        uint8_t reg1 = code[0] & 0x0f;
        uint8_t reg2 = code[1] >> 4;
        uint8_t addr = code[1] & 0x0f;
        printf("%-10s V%01X, V%01X, #$%01X", "SPRITE", reg1, reg2, addr);
      }
      break;    
    case 0x0e:
      {
        uint8_t reg = code[0] & 0x0f;
        switch(code[1]) {
          case 0x9e:
            printf("%-10s V%01X", "SKIP.KEY", reg);
            break;
          case 0xa1:
            printf("%-10s V%01X", "SKIP.NOKEY", reg);
            break;
          default:
            printf("UNKNOWN E.");
            break;
        }
      }
      break;    
    case 0x0f:
      {
        uint8_t reg = code[0] & 0x0f;
        switch(code[1]) {
          case 0x07:
            printf("%-10s V%01X, DELAY", "MOV", reg);
            break;
          case 0x0a:
            printf("%-10s V%01X", "WAITKEY", reg);
            break;
          case 0x15:
            printf("%-10s DELAY, V%01X", "MOV", reg);
            break;
          case 0x18:
            printf("%-10s SOUND, V%01X", "MOV", reg);
            break;
          case 0x1e:
            printf("%-10s I, V%01X", "ADD", reg);
            break;
          case 0x29:
            printf("%-10s V%01X", "SPRITECHAR", reg);
            break;
          case 0x33:
            printf("%-10s V%01X", "MOVBCD", reg);
            break;
          case 0x55:
            printf("%-10s (I), V0-V%01X", "MOVM", reg);
            break;
          case 0x65:
            printf("%-10s V0-V%01X, (I)", "MOVM", reg);
            break;
          default:
            printf("UNKNOWN F.");
            break;
        }
      }
      break;    
  }
}

int main(int argc, char **argv) {
  FILE *fp = fopen("./roms/Fishie.ch8", "rb");
  //FILE *fp = fopen("./roms/test_opcode.ch8", "rb");
  if(!fp) {
    printf("error: Couldn't open file");
    exit(1);
  }
  fseek(fp, 0L, SEEK_END);
  int fsize = ftell(fp);
  fseek(fp, 0L, SEEK_SET);

  uint8_t *buffer = malloc(0x200 + fsize);
  fread(buffer + 0x200, fsize, 1, fp);
  fclose(fp);

  int pc = 0x200;
  printf(" PC  INSTRUCTION\n");
  printf("---- -----------\n");
  while(pc < (fsize + 0x200)) {
    disassembleOp(buffer, pc);
    pc += 2;
    printf("\n");
  }
  return 0;
}