#include "firstcheck.h"

struct Decode {
    int ic;
    char opcode [5];
    char sourceType[4];
    char destinationType[4];
    char ARE[3];
    int binaryNumber[13];
    struct Decode* next;
}

char* opcodeToBinary(char *ptr);
