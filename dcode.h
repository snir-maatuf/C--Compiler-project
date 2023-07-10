#include "firstcheck.h"

struct Decode {
    char *name;
    char opcode [5];
    char sourceType[4];
    char destinationType[4];
    char ARE[3];
    int value;
    struct Decode* next;
}

char* opcodeToBinary(char *ptr);
